/*
    Server/Client and core.cpp mixed header
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../CoreRegistry.h"

using std::cout;
using std::endl;
using std::string;
using std::stoi;

void serverInfo::infoSetup()
{
    string portTemp;
    fstream(STASSID);
    STASSID.open("../bin/server/STASSID.DAT");
    if(STASSID.is_open())
    {
        getline(STASSID,portTemp,',');
        defaultPort = stoi(portTemp);
        getline(STASSID,networkName,',');
        getline(STASSID,networkPass,',');
        getline(STASSID,hostIP,',');
    }
    else
    {
        STASSID.close();
        cout<<"Server Information\nDefault Port: "; 
        cin >> defaultPort;
        cout<<"Network Name: ";
        cin >> networkName;
        cout<<"Network Password: ";
        cin >> networkPass;
        cout<<"IPv4 Address: ";
        cin >> hostIP;

        std::ofstream STASSID("../bin/server/STASSID.DAT");
        STASSID<<defaultPort<<",port\n"<<networkName<<",netName\n"
               <<networkPass<<",netPass\n"<<hostIP<<",IPv4\n";
        
        STASSID.close();
        cout<<"\nServer Information Saved\n\n";
    }
    

}

const int BufferSize = 128;
char serverBuffer[BufferSize];