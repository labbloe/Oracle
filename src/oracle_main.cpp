/*
    Oracle
    Windows Build
    Jared Allen
*/

#include "OracleRegistry.h"
#include <ws2tcpip.h>
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "2007"

bool exitProg = false;

int main()
{
    string input;
    int inputCnt = 0;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, BLUE);
    printFile("progRef/SPLASH.DAT");
    SetConsoleTextAttribute(hConsole, WHITE);
    cout << "Version: " <<  VERSION << "\nBuild: " << BUILD << "\n"
         << "Build Date: "<< BUILD_DATE << "\n\n";
    UserGreeting();

    std::thread server(serverStartup);
    Sleep(10);
    while(input != "exit")
    {
        SetConsoleTextAttribute(hConsole, AQUA);
        cout << "ORACLE:" << inputCnt << "> ";
        SetConsoleTextAttribute(hConsole, WHITE);
        getline(cin,input,'\n');
        inputCnt++;
    }
    exitProg = true;

    server.join();

    return 0;
}

void serverStartup() 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, RED);
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("SERVER:> WSAStartup failed with error: %d\n", iResult);
    }
    printf("SERVER:> WSAStarup Successful\n");

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("SERVER:> getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
    }
    printf("SERVER:> getaddrinfo Successful\n");
    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("SERVER:> socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
    }
    printf("SERVER:> Socket Successful\n");
    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("SERVER:> bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
    }
    printf("SERVER:> Bind Successful\n");
    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("SERVER:> listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
    }
    printf("SERVER:> Oracle Currently Listening for Clients\n");
    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    SetConsoleTextAttribute(hConsole, RED);
    cout << "\nSERVER:> accept successful for client: " << ClientSocket <<"\n";
    if (ClientSocket == INVALID_SOCKET) {
        printf("SERVER:> accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
    }
    SetConsoleTextAttribute(hConsole, AQUA);
    cout << "ORACLE:RETURN> ";
    SetConsoleTextAttribute(hConsole, WHITE);
    // No longer need server socket
    closesocket(ListenSocket);

    //Timeout for receiver before socket shutdown
    struct timeval tv;
    tv.tv_sec = 10;
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(ClientSocket, &rfds);

    // Receive until the peer shuts down the connection or timeout
        do{
        SetConsoleTextAttribute(hConsole, RED);
        int recvValue = select(1, &rfds,NULL,NULL,&tv);
        switch(recvValue)
        {
            case(0):
            {
                //Timeout
                printf("\nSERVER:> client timeout\n");
                WSACleanup();
                break;
            }

            case(SOCKET_ERROR):
            {
                printf("\nSERVER:> socket error received with error: %d\n",WSAGetLastError());
                break;
            }
            
            default:
            {
                iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
                break;
            }
        }

        if (iResult > 0) {
            printf("\nSERVER:> Bytes received: %d\n", iResult);
            cout<<"SERVER:> "<<recvbuf<<"\n";
        // Echo the buffer back to the sender
            iSendResult = send( ClientSocket, recvbuf, iResult, 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("SERVER:> send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                iResult = 0;
            }
            printf("SERVER:> Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("SERVER:> Connection closing...\n");
        else  {
            printf("\nSERVER:> recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();

        }
        if(iResult > 0)
        {
            SetConsoleTextAttribute(hConsole, AQUA);
            cout << "ORACLE:RETURN> ";
            SetConsoleTextAttribute(hConsole, WHITE);
        }
    } while (exitProg == false && iResult > 0);

    // shutdown the connection since we're done
    SetConsoleTextAttribute(hConsole, RED);
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("SERVER:> shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
    }
    SetConsoleTextAttribute(hConsole, AQUA);
    cout << "ORACLE:RETURN> ";
    SetConsoleTextAttribute(hConsole, WHITE);

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

}