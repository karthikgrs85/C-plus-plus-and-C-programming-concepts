

#pragma once
#define WIN32_LEAN_AND_MEAN



#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <atomic>
#include <mutex>
#include <string>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
#define CLIENT_NAME_LEN 20

#define SOCKET_READ_TIMEOUT_SEC 5

using namespace std;

class Client
{
    WSADATA wsaData;
    SOCKET ConnectSocket;
    struct addrinfo* result,
        * ptr,
        hints;
    char sendbuf[DEFAULT_BUFLEN];
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen;
    bool isConnected;
    static std::mutex mtx;
    char clientName[CLIENT_NAME_LEN];
    bool isRunning;
    int index;
    

public:
    Client(const char serverName[], const char clientName[]);

    void Cleanup();
    
    bool isConnectedStatus();

    bool SendDataToServer(char buf[]);

    void RecvDataFromServer();

    void Stop();

};