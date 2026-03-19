#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

#include "Server.h"

//using namespace std;

Server* Server::m_Server = nullptr;

std::mutex Server::mtx_ListenSocket;


int __cdecl main(void)
{
    
    char sendbuf[DEFAULT_BUFLEN];
    char sendstr[DEFAULT_BUFLEN];
    Server* server = Server::GetInstance();
    //shared_ptr<Server> server = make_shared<Server>();

    //server->setUpListenSocket();

    std::atomic<bool> isrunning{ true };
    char *token;
    int clientIndex = 0;
    std::thread AcceptNewClientConn(&Server::AcceptNewConnectionThread, server);
    printf("\n Waiting for connections ");
    
    std::thread Recv(&Server::ReceiveMainThread, server);
    do
    {
            strcpy(sendbuf, "");
            printf(" \n Enter Data in the following format \n C <Client-ID> Message to send to client  \n (0 to terminate) : \n");
            std::cin.getline(sendbuf, DEFAULT_BUFLEN);

            if (sendbuf[0] == '0')
            {
                printf("\n Server terminating ... Bye..");
                break;
            }
            else if (sendbuf[0] == 'C')
            {
                token = strtok(sendbuf + 2, " ");
                clientIndex = atoi(token);
                strcpy(sendstr, sendbuf + 3 + strlen(token));
                server->SendToClient(sendstr, clientIndex-1);
            }
    
    } while (sendbuf[0] != '0');
   
    isrunning = false;
    
    server->Stop();
    AcceptNewClientConn.join();
    Recv.join();
    
    
    server->Cleanup();
    

    return 0;
}