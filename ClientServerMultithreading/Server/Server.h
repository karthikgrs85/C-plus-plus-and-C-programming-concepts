#ifndef __SERVER_H
#define __SERVER_H

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <future>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>
#include <iostream>


#define WIN32_LEAN_AND_MEAN

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define MAX_CLIENTS 5
#define SOCKET_READ_TIMEOUT_SEC 5
#define CLIENT_NAME_LEN 20

class Server;

class ClientData
{
    int iResult;
    SOCKET ClientSocket;
    bool ClientConnected;
    std::mutex mtx_ClientSocket;
    std::unique_ptr<std::thread> ClientThread;
    char ClientName[CLIENT_NAME_LEN];

    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    friend class Server;


public:

    ClientData();
    void SendToClient(const char sendbuf[]);
    bool getClientConnectedStatus();
    bool isReceiveClientThreadRunning();
    bool isClientName(const char clientName[]);

};

class Server
{
    WSADATA wsaData;
   //iResult for the Listen Socket
    int iResult_LS;

    ClientData clientData[MAX_CLIENTS];

    SOCKET ListenSocket;
    

    

    struct addrinfo* result;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    static Server* m_Server;
       
    //std::thread RecvFromClient[MAX_CLIENTS];

    static std::mutex mtx_ListenSocket;

    bool isRunning;

    
protected:

    //Singleton class, therefore the constructor is protected
    Server();

public:

    /*static void init()
    {
       for (int i = 0; i < MAX_CLIENTS; ++i)
            {
                std::mutex ClientData::mtx_ClientSocket;
            }
            std::mutex Server::mtx_ListenSocket;
    }*/

    bool isReceiveClientThreadRunning(const int& index);

    static Server* GetInstance();
    
    bool getClientIndexForClientName(const char clientName[], int& index);

    bool getClientNameForClientIndex(const int& index, char* clientName);

    bool getClientConnectedStatus(const int& index);

    void AcceptNewConnectionThread();

    /*void AcceptNewConnections(std::atomic<bool>& isRunning)
    {
        std::cout << "\n Waiting for incoming connections ...\n";
        
         std::thread AcceptNewConn(&Server::AcceptNewConnectionThread, this);
         AcceptNewConn.join();
                
        std::cout << " \n Terminating Accept New Connections Thread !\n";

    }*/

    void ReceiveMainThread();

    void ReceiveFromClient(const int& index);


    //void ReceiveFromClientThread(std::atomic<bool> isRunning)
    //{
    //    
    //    do
    //    {
    //        if (ClientConnected && !ReceiveClientThreadRunning)
    //        {
    //            std::thread t(&Server::ReceiveFromClient,this);
    //        }
    //        //Client is disconnected but the thread for recvfromclient is still running
    //        //In this case shutdown the client socket, and join the thread.
    //        else if(!ClientConnected && ReceiveClientThreadRunning)
    //        {
    //            iResult = shutdown(ClientSocket, SD_SEND);
    //            if (iResult == SOCKET_ERROR) {
    //                printf("shutdown failed with error: %d\n", WSAGetLastError());
    //                closesocket(ClientSocket);
    //                WSACleanup();
    //                    
    //                    
    //            }
    //            else
    //            {
    //                // cleanup
    //                closesocket(ClientSocket);
    //                WSACleanup();
    //            }
    //                
    //            ReceiveClientThreadRunning = false;
    //        }

    //    } while (isRunning);

    //    for (int i = 0; i < MAX_CLIENTS; i++)
    //    {
    //        if (ReceiveClientThreadRunning)
    //        {
    //            iResult= shutdown(ClientSocket[i], SD_SEND);
    //            if (iResult == SOCKET_ERROR) {
    //                printf("shutdown failed with error: %d\n", WSAGetLastError());
    //                closesocket(ClientSocket);
    //                WSACleanup();


    //            }
    //            else
    //            {
    //                // cleanup
    //                closesocket(ClientSocket[i]);
    //                WSACleanup();
    //            }

    //            RecvFromClient.join();
    //            ReceiveClientThreadRunning = false;
    //        }
    //    }


    //}


    void SendToClient(char sendbuf[], const int& index);

   // void setUpListenSocket();

    //void sendDataToClient(char sendbuf[]);

    void Stop();

    void Cleanup();


    ~Server();

   };

   
#endif