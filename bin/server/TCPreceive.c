/* TCP Oracle server 
   Based on Linux TCP server from https://www.thegeekstuff.com/2011/12/c-socket-programming/
*/

#include "../CoreRegistry.h"

//socket and address info headers
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
//#include <time.h>

#define BUFFER 1025
#define MAX_CLIENTS 10

int main(int argc, char *argv[])
{
    serverInfo mainServer;
    mainServer.infoSetup("../");

    cout<<"Initializing Oracle Server\n"
        <<"==========================\n";

    if(argc != 1) 
    {
        std::cerr << "ERROR: *argv[] should point to singular argument (argc != 1)\n"
                  << "USAGE: ./a.out\n";
        return -1;
    }

    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;

    char buff[BUFFER] = {0};
    cout<<"Buffer Size: "<<BUFFER<<endl;

    listenfd = socket(AF_INET,SOCK_STREAM,0); //AF_INET IPv4, SOCK_STREAM TCP
    memset(&serv_addr,'0',sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
    listen(listenfd,MAX_CLIENTS);
    cout<<"IP Default: 127.0.0.1\n";
    cout<<"Max Clients: "<<MAX_CLIENTS<<endl;
    cout<<"listening and awaiting connection from client...\n";

    while(1)
    {
        connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
        cout<<"Client Connection Established\nconnfd: "<<connfd<<endl;
        snprintf(buff,BUFFER,"test");
        write(connfd,buff,strlen(buff));

        close(connfd);
        sleep(1);
    }

    return 0;    
}
