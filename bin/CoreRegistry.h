/*
The following header file contains all relevant callings
for core.cpp. 
*/

#ifndef COREREGISTRY_H
#define COREREGISTRY_H

#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::fstream;

const string version = "0.0.5";
const string versionDate = "August, 16 2020";

class userInfo
{
    public:
    string FirstName;
    string LastName;
    string email;
    string phone;

    void startup();
};

class serverInfo
{
    public:
    int defaultPort;
    string networkName;
    string networkPass;
    string hostIP;

    void infoSetup(string fileadd);
};

#include "Messages.hpp"
#include "status.hpp"
#include "data.h"
#include "userControl.h"
#include "server/OracleTCP.hpp"


#endif