#define _CRT_SECURE_NO_WARNINGS
#include "Server.h"

bool ClientData::isClientName(const char clientName[])
{
    return(!strcmp(clientName, ClientName));
}


Server::Server()
{
   
    
        ListenSocket = INVALID_SOCKET;

        result = NULL;

        // Initialize Winsock
        iResult_LS = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (iResult_LS != 0) {
            printf("WSAStartup failed with error: %d\n", iResult_LS);
            return;
        }

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        // Resolve the server address and port
        iResult_LS = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
        if (iResult_LS != 0) {
            printf("getaddrinfo failed with error: %d\n", iResult_LS);
            WSACleanup();
            return;
        }


        // Create a SOCKET for connecting to server
        ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

        if (ListenSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            freeaddrinfo(result);
            WSACleanup();
            return;
        }

        DWORD timeout = SOCKET_READ_TIMEOUT_SEC * 1000;
        setsockopt(ListenSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

        // Setup the TCP listening socket
        iResult_LS = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        if (iResult_LS == SOCKET_ERROR) {
            printf("bind failed with error: %d\n", WSAGetLastError());
            freeaddrinfo(result);
            closesocket(ListenSocket);
            WSACleanup();
            return;
        }

        freeaddrinfo(result);

        iResult_LS = listen(ListenSocket, SOMAXCONN);
        if (iResult_LS == SOCKET_ERROR) {
            printf("listen failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return;
        }

        isRunning = true;

        //setsockopt(ListenSocket, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, (char*)&isRunning, sizeof(isRunning));

}

bool Server::isReceiveClientThreadRunning(const int& index)
{
    return (clientData[index].ClientThread!=nullptr);
}

Server* Server::GetInstance()
{
    if (m_Server == NULL)
    {
        m_Server = new Server();
    }
    return m_Server;
}

bool Server::getClientConnectedStatus(const int& index)
{
    return clientData[index].getClientConnectedStatus();
}

bool ClientData::getClientConnectedStatus()
{
    return ClientConnected;
}

void Server::AcceptNewConnectionThread()
{
    char sendbuf[DEFAULT_BUFLEN];
    bool AcceptStatus;
    // Accept a client socket
    do
    {
        std::unique_lock<std::mutex> uLock(mtx_ListenSocket);
        SOCKET cs;
        uLock.unlock();
        AcceptStatus = false;
        cs = accept(ListenSocket, NULL, NULL);
        uLock.lock();
        if (cs == INVALID_SOCKET && isRunning) {
            printf("\n accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return;
        }
        else if (!isRunning)
        {
            printf("\n Closing Listen Socket ...");
            
            return;
        }
        for (int i = 0; i < MAX_CLIENTS; ++i)
        {
            if (!getClientConnectedStatus(i))
            {   
                std::unique_lock<std::mutex> uLockC(clientData[i].mtx_ClientSocket);
                clientData[i].ClientSocket = cs;
                clientData[i].ClientConnected = true;
                       
                
                DWORD timeout = SOCKET_READ_TIMEOUT_SEC * 1000;
                setsockopt(clientData[i].ClientSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

                uLockC.unlock();
                AcceptStatus = true;
                break;
            }
        }

        if (!AcceptStatus)
        {
            sprintf(sendbuf, " Error: Unable to connect, Max Clients limit reached!... Unable to connect to new Client\n");
            iSendResult = send(cs, sendbuf, strlen(sendbuf), 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(cs);
                WSACleanup();
                return;
            }
            printf("Bytes sent: %d\n", iSendResult);


            continue;
        }

        

    } while (isRunning);
}

void Server::ReceiveFromClient(const int& index)
{
    std::unique_lock<std::mutex> uLock(clientData[index].mtx_ClientSocket);
    char* token;
    char sendbuf[DEFAULT_BUFLEN], buf[DEFAULT_BUFLEN], *ClientName, fromClientName[CLIENT_NAME_LEN], toClientName[CLIENT_NAME_LEN];
    int ClientIndex = 0, toClientIndex = 0;
    bool anyOtherClients = false;
    do
    {
        
        strcpy(clientData[index].recvbuf, "");
        uLock.unlock();

        clientData[index].iResult = recv(clientData[index].ClientSocket, clientData[index].recvbuf, recvbuflen, 0);
        
        uLock.lock();
        if (clientData[index].iResult > 0)
        {
            clientData[index].recvbuf[clientData[index].iResult] = '\0';
            strcpy(buf, clientData[index].recvbuf);

            if (strstr(clientData[index].recvbuf,"CI"))
            {
                token = strtok(buf + 3, " ");
                toClientIndex = atoi(token)-1;

                if (!getClientConnectedStatus(toClientIndex))
                {
                    sprintf(sendbuf, " Error: Client does not exist!");
                    SendToClient(sendbuf, index);
                    continue;
                }

                getClientNameForClientIndex(toClientIndex, toClientName);

                printf(" Bytes received: %d from Client : %s for Client : %s \n", clientData[index].iResult, clientData[index].ClientName, toClientName);

                sprintf(sendbuf,"CN %s ", clientData[index].ClientName);
                strcat(sendbuf, clientData[index].recvbuf + 3 + strlen(token));
                SendToClient(sendbuf, toClientIndex);
                
                //printf(" Received buffer: %s \n", recvbuf);
                //printf(" Outgoing buffer: %s \n", sendbuf);

            }
            else if (strstr(clientData[index].recvbuf, "CN"))
            {
                ClientName = strtok(buf + 3, " ");
                if (!getClientIndexForClientName(ClientName, toClientIndex))
                {
                    sprintf(sendbuf, " Error, Client does not exist!");
                    SendToClient(sendbuf, index);
                    continue;
                }

                printf(" Bytes received: %d from Client : %s for Client : %s \n", clientData[index].iResult, clientData[index].ClientName, ClientName);    

                sprintf(sendbuf, "CN %s ",clientData[index].ClientName);
                strcat(sendbuf, clientData[index].recvbuf + 3 + strlen(ClientName));
                
                SendToClient(sendbuf, toClientIndex);

            }
            else if (strstr(clientData[index].recvbuf, "ConnectAs"))
            {
                if (getClientIndexForClientName(buf + 10, ClientIndex))
                {
                    sprintf(sendbuf, " Error: Client name already exists!, connect with different client name");
                    SendToClient(sendbuf, index);

                    clientData[index].ClientConnected = false;
                    
                    break;
                }

                strcpy(clientData[index].ClientName, buf + 10);

                sprintf(sendbuf, "Success: Connected!, you are Client Name: %s and index : %d \n", clientData[index].ClientName, index + 1);
                
                SendToClient(sendbuf, index);

                sprintf(sendbuf, "New Client connected with Client Name : %s, Client index : %d \n", clientData[index].ClientName, index + 1);
                
                printf("%s", sendbuf);

                //Inform about the newly connected Client to already connected ClientClientIndexs
                for (int j = 0; j < MAX_CLIENTS; ++j)
                {
                    if (j != index && clientData[j].getClientConnectedStatus())
                    {
                        SendToClient(sendbuf, j);

                        //Inform about existing client connections to the newly connected client
                        if (getClientNameForClientIndex(j, toClientName))
                        {
                            if (!anyOtherClients)
                            {
                                sprintf(buf, "Information about existing clients :\n");
                                SendToClient(buf, index);
                                anyOtherClients = true;
                            }
                            sprintf(buf, "Client index : %d, name : %s\n", j + 1, toClientName);
                            SendToClient(buf, index);
                        }
                    }

                }

                //Inform the newly connected client about existing clients
                
            }
            else
            {
                printf(" Bytes received: %d from Client index :  %d \n", clientData[index].iResult, index + 1);
                printf(" Received buffer: %s \n", recvbuf);
            }
        }
        else if (clientData[index].iResult == 0 || WSAGetLastError() == 10054)
        {
            getClientNameForClientIndex(index, fromClientName);
            sprintf(sendbuf, "Connection closed by Client name : %s, index : %d \n", fromClientName, index+1);
            printf("%s", sendbuf);
            
            //Inform other clients about the client getting disconnected
            for (int j = 0; j < MAX_CLIENTS; ++j)
            {
                if (j != index && clientData[j].getClientConnectedStatus())
                {
                    SendToClient(sendbuf, j);
                }
            }

            clientData[index].ClientConnected = false;
            strcpy(clientData[index].ClientName,"");
            
            break;
        }
        else if(WSAGetLastError()!=10060)
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
            clientData[index].ClientConnected = false;
            strcpy(clientData[index].ClientName, "");
            closesocket(clientData[index].ClientSocket);
            WSACleanup();
            break;
        }
    } while (isRunning);

}

void Server::ReceiveMainThread()
{
    do
    {
        for (int i = 0; i < MAX_CLIENTS; ++i)
        {

            std::unique_lock<std::mutex> uLock(clientData[i].mtx_ClientSocket);
            if (clientData[i].getClientConnectedStatus() && (!isReceiveClientThreadRunning(i)))
            {
                clientData[i].ClientThread = std::make_unique<std::thread>(&Server::ReceiveFromClient, this, i);
            }
            else if ((!clientData[i].getClientConnectedStatus()) && isReceiveClientThreadRunning(i))
            {
                
                closesocket(clientData[i].ClientSocket);
                clientData[i].ClientSocket = INVALID_SOCKET;
                /*WSACleanup();*/
                clientData[i].ClientThread->join();
                clientData[i].ClientThread.release();
                clientData[i].ClientThread = nullptr;
            }

            uLock.unlock();
        }
    } while (isRunning);

    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        if (isReceiveClientThreadRunning(i))
        {
                      
            clientData[i].ClientThread->join();
            clientData[i].ClientThread.release();
            clientData[i].ClientThread = nullptr;
            
            clientData[i].ClientConnected = false;
            strcpy(clientData[i].ClientName, "");
            //iResult[i] = shutdown(ClientSocket[i], SD_BOTH);
            //if (iResult[i] == SOCKET_ERROR) {
            //    printf("shutdown failed with error: %d\n", WSAGetLastError());
            ////    closesocket(ClientSocket[i]);
            ////    break;
            //}
            closesocket(clientData[i].ClientSocket);
            
        }
    }
   

}


void Server::SendToClient(char sendbuf[], const int& index)
{
    clientData[index].SendToClient(sendbuf);
}

void ClientData::SendToClient(const char sendbuf[])
{
    int iSendResult;
    //std::unique_lock<std::mutex> uLock(mtx_ClientSocket);

    if (!getClientConnectedStatus())
    {
        std::cout << "\n Client not connected, unable to send !!\n";
        return;
    }

    iSendResult = send(ClientSocket, sendbuf, strlen(sendbuf), 0);
    if (iSendResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return;
    }
    printf("Bytes sent: %d\n", iSendResult);
}




//void Server::setUpListenSocket()
//{
//    // Create a SOCKET for connecting to server
//    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//    if (ListenSocket == INVALID_SOCKET) {
//        printf("socket failed with error: %ld\n", WSAGetLastError());
//        freeaddrinfo(result);
//        WSACleanup();
//        return;
//    }
//
//    // Setup the TCP listening socket
//    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
//    if (iResult == SOCKET_ERROR) {
//        printf("bind failed with error: %d\n", WSAGetLastError());
//        freeaddrinfo(result);
//        closesocket(ListenSocket);
//        WSACleanup();
//        return;
//    }
//
//    freeaddrinfo(result);
//
//    iResult = listen(ListenSocket, SOMAXCONN);
//    if (iResult == SOCKET_ERROR) {
//        printf("listen failed with error: %d\n", WSAGetLastError());
//        closesocket(ListenSocket);
//        WSACleanup();
//        return;
//    }
//
//}

//void Server::sendDataToClient(char sendbuf[])
//{
//    // Echo the buffer back to the sender
//    //strcpy(sendbuf, " Connected to server!");
//    std::unique_lock<std::mutex> uLock(mtx_ClientSocket);
//
//    iSendResult = send(ClientSocket, sendbuf, strlen(sendbuf), 0);
//    if (iSendResult == SOCKET_ERROR) {
//        printf("send failed with error: %d\n", WSAGetLastError());
//        closesocket(ClientSocket);
//        WSACleanup();
//        return;
//    }
//    printf("Bytes Sent: %ld\n", iSendResult);
//
//}


bool Server::getClientIndexForClientName(const char clientName[], int& index)
{

    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        if (getClientConnectedStatus(i))
        {
            if (clientData[i].isClientName(clientName))
            {
                index = i;
                return true;
            }
        }
    }

    return false;
}

bool Server::getClientNameForClientIndex(const int& index, char* clientName)
{
    if (getClientConnectedStatus(index))
    {
        strcpy(clientName, clientData[index].ClientName);
        return true;
    }

    return false;
}
void Server::Cleanup()
{
    // shutdown the connection since we're done
    

       
    
    // No longer need server socket
    //closesocket(ListenSocket);

    WSACleanup();
}

void Server::Stop()
{
    isRunning = false;

    std::unique_lock<std::mutex> uLock(mtx_ListenSocket);
    //setsockopt(ListenSocket, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, (char*)&isRunning, sizeof(isRunning));
    closesocket(ListenSocket);
}


Server::~Server()
{

}

//void ClientData::ReceiveFromClient()
//{
//    int index, toClientIndex;
//    do
//    {
//        std::unique_lock<std::mutex> uLock(mtx_ClientSocket);
//        char* token;
//        char sendbuf[DEFAULT_BUFLEN];
//        int toClientIndex = 0;
//        strcpy(recvbuf, "");
//        uLock.unlock();
//
//        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
//
//        uLock.lock();
//        if (iResult > 0)
//        {
//            recvbuf[iResult] = '\0';
//
//            if (recvbuf[0] == 'C' && recvbuf[1] == ' ')
//            {
//                token = strtok(recvbuf + 2, " ");
//                toClientIndex = atoi(token);
//                sprintf(sendbuf, "C %d ", index);
//                strcat(sendbuf, recvbuf + 3 + strlen(token));
//                SendToClient(sendbuf, toClientIndex-1);
//                printf(" Bytes received: %d from Client index %d  for Client index %d \n", iResult[index], index + 1, toClientIndex);
//                //printf(" Received buffer: %s \n", recvbuf);
//                //printf(" Outgoing buffer: %s \n", sendbuf);
//
//            }
//            else if (strstr(recvbuf, "ConnectAs"))
//            {
//                token = strtok(recvbuf, " ");
//
//            }
//            else
//            {
//                printf(" Bytes received: %d from Client index :  %d \n", iResult[index], index + 1);
//                printf(" Received buffer: %s \n", recvbuf);
//            }
//        }
//        else if (iResult[index] == 0 || WSAGetLastError() == 10054)
//        {
//            printf("Connection closed by Client index : %d \n", index + 1);
//            ClientConnected[index] = false;
//            break;
//        }
//        else if (WSAGetLastError() != 10060)
//        {
//            printf("recv failed with error: %d\n", WSAGetLastError());
//            ClientConnected[index] = false;
//            closesocket(ClientSocket[index]);
//            WSACleanup();
//            break;
//        }
//    } while (isRunning);
//}

ClientData::ClientData()
{
    ClientSocket = INVALID_SOCKET;
    ClientConnected = false;
    iResult = 0;
    ClientThread = nullptr;
    strcpy(ClientName, "");

}

//void ClientData::SendToClient(char sendbuf[])
//{
//
//    int iSendResult;
//    std::unique_lock<std::mutex> uLock(mtx_ClientSocket);
//
//    if (!getClientConnectedStatus())
//    {
//        std::cout << "\n Client not connected, unable to send !!\n";
//        return;
//    }
//
//    iSendResult = send(ClientSocket, sendbuf, strlen(sendbuf), 0);
//    if (iSendResult == SOCKET_ERROR) {
//        printf("send failed with error: %d\n", WSAGetLastError());
//        closesocket(ClientSocket);
//        WSACleanup();
//        return;
//    }
//    printf("Bytes sent: %d\n", iSendResult);
//}


bool ClientData::isReceiveClientThreadRunning()
{
    return ClientThread != nullptr;
}