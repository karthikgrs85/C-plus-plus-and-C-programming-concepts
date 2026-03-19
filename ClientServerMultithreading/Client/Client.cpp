#define _CRT_SECURE_NO_WARNINGS

#include "Client.h"


Client::Client(const char serverName[], const char clientName[])
{
    ConnectSocket = INVALID_SOCKET;
    result = NULL;
    ptr = NULL;
    index = 0;
    recvbuflen = DEFAULT_BUFLEN;
    isConnected = false;
    isRunning = false;
    strcpy(sendbuf, "");
    strcpy(recvbuf, "");
    strcpy(this->clientName, clientName);
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;


    // Resolve the server address and port
    iResult = getaddrinfo(serverName, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        isConnected = true;
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return;
    }

    
    DWORD timeout = SOCKET_READ_TIMEOUT_SEC * 1000;
    setsockopt(ConnectSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

    isRunning = true;

}

void Client::Cleanup()
{
    //// shutdown the connection since no more data will be sent
    //iResult = shutdown(ConnectSocket, SD_SEND);
    //if (iResult == SOCKET_ERROR) {
    //    printf("shutdown failed with error: %d\n", WSAGetLastError());
    //    closesocket(ConnectSocket);
    //    WSACleanup();
    //    return;
    //}

    closesocket(ConnectSocket);
    WSACleanup();
}

bool Client::isConnectedStatus()
{
    return isConnected;
}

bool Client::SendDataToServer(char buf[])
{

    std::unique_lock<std::mutex> uLock(mtx);
    iResult = send(ConnectSocket, buf, strlen(buf), 0);
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        // closesocket(ConnectSocket);
        // WSACleanup();
        return false;
    }

    printf("Bytes Sent: %ld\n", iResult);
    return true;
}


void Client::RecvDataFromServer()
{

    char substr[10] = "Error";
    char* token;
    //int index;

    do
    {

        strcpy(recvbuf, "");
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);

        if (iResult > 0)
        {
            printf("Bytes received: %d\n", iResult);
            recvbuf[iResult] = '\0';

            if (strncmp(recvbuf, substr, 5) == 0)
            {
                printf(" Error connecting to Server! \n");
                printf(" Error message : %s \n", recvbuf);
                isConnected = false;
                break;
            }
            else if (strstr(recvbuf, "Error:"))
            {
                printf(" %s \n", recvbuf);
                printf(" Terminating ...\n");
                isConnected = false;
                break;
            }
            /*else if (strstr(recvbuf, "Success"))
            {
                char* pos = strrchr(recvbuf, ' ') + 1;
                index = atoi(pos);
                printf("\n You are connected as %s and index %d\n", clientName, index);
            }*/
            else if (strstr(recvbuf,"CI") || strstr(recvbuf, "CN"))
            {
                token = strtok(recvbuf + 3, " ");
                printf("\n Received Message from another Client ");// index:% d \n", atoi(token) + 1);
                printf("\n %s : %s \n", token, recvbuf + 4 + strlen(token));
            }
            else
            {
                printf("\n Received Message from Server ");
                printf("\n %s\n", recvbuf);
            }
        }
        else if (iResult == 0)
        {
            printf("Connection closed\n");
            isConnected = false;
            break;
        }
        else if (!isRunning)
        {
            printf(" Client program terminating.. \n");
            break;
        }
        else if(WSAGetLastError()!=10060)
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
            isConnected = false;
            break;
        }
        


    } while (isRunning);

}

void Client::Stop()
{
    isRunning = false;
}