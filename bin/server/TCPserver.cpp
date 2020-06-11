#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")

#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define PORT 2007
using std::cout;
using std::endl;

const char szHost[] = "test";

int main(const int argc, const char *argv[])
{
    //initialize WINSOCK
    WSAData wsaData;
    WORD DllVersion = MAKEWORD(2,1);
    if(WSAStartup(DllVersion,&wsaData) != 0)
    {
        ExitProcess(EXIT_FAILURE);
        cout<<"ERROR: WSAStartup Failed\n";
    }

    //Create Socket
    //AF_INET family (IPv4), SOCK_STREAM streams TCP
    SOCKET sock = socket(AF_INET, SOCK_STREAM,0);
    if(sock < 0)
    {
        ExitProcess(EXIT_FAILURE);
        cout<<"ERROR: Socket create failed\n";
    }

    //Get Server Info
    HOSTENT *host = gethostbyname(szHost);
    if(host == nullptr)
    {
        ExitProcess(EXIT_FAILURE);
        cout<<"ERROR: in gethostbyname(), *host == nullptr\n";
    }

    //Define Server Info
    SOCKADDR_IN  sin;
    ZeroMemory(&sin,sizeof(sin));
    sin.sin_port = htons(PORT); //htons converts to correct formating
    sin.sin_family = AF_INET;
    memcpy(&sin.sin_addr.S_un.S_addr, host -> h_addr_list[0], sizeof(sin.sin_addr.S_un.S_addr));

    //Connect to Server
    if(connect(sock,(const sockaddr *)&sin,sizeof(sin)) != 0)
    {
        ExitProcess(EXIT_FAILURE);
        cout<<"ERROR: Could not connec to server on port "<<PORT<<"\n";
    }

    const char Msg[] = "HEAD / HTTP/1.0\r\n\r\n";
    if(!send(sock,Msg,strlen(Msg),0))
    {
        ExitProcess(EXIT_FAILURE);
        cout<<"ERROR: could not send\n";
    }

    char Buffer[4096];
    char Temp[4096];
    while(recv(sock,Temp,4096,0))
        strcat(Buffer,Temp);
    
    printf("%s\n",Temp);

    closesocket(sock);
    getchar();

    ExitProcess(EXIT_SUCCESS);
}