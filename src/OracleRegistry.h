/*
The following header file contains all relevant callings
for core.cpp. 
*/

#ifndef ORACLEREGISTRY_H
#define ORACLEREGISTRY_H

#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#include <winbase.h>
#include <ShellApi.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <thread>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::fstream;

#include "Messages.hpp"
#include "config.h"

void serverStartup();
bool bufferCheck(char* temp,char* buf);
void serverSend_CLA(char* buf);


#endif