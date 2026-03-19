#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS


#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory>
#include "Client.h"
#include <thread>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

using namespace std;

std::mutex Client::mtx;

int __cdecl main(int argc, char** argv)
{
    

    char buf[DEFAULT_BUFLEN];

    // Validate the parameters
   if (argc != 3) {
       printf("usage: %s server-name client-name\n", argv[0]);
       return 1;
   }

    auto myClient = std::make_shared<Client>(argv[1], argv[2]);
    printf("\n Trying to connect to server ...");
    /*if (!(myClient->connectToServer(argv[1])))
    {
        cout << " Terminating !";
        return -1;
    }*/

    //printf(" Connected to server as %s !\n", argv[2]);

    std::thread RecvFromServer(&Client::RecvDataFromServer, myClient.get());
   
    sprintf(buf, "ConnectAs %s", argv[2]);
    myClient->SendDataToServer(buf);

    
    Sleep(2000);

    while (myClient->isConnectedStatus())
    {
        strcpy(buf, "");
        cout << "Enter some text to send to server : \n"
             <<" Format : To send to server send as it is \n"
             <<" For another client: CI <client-id> <message> or CN <client-name> <message>\n";
        cin.getline(buf, DEFAULT_BUFLEN);

        if (buf[0] == '0')
           break;
        
        myClient->SendDataToServer(buf);

    }
    
    myClient->Stop();
    RecvFromServer.join();
    myClient->Cleanup();
    
    

    return 0;
}