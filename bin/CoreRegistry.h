/*
The following header file contains all relevant callings
for core.cpp. 
*/

#ifndef COREREGISTRY_H
#define COREREGISTRY_H

#include <iostream>
#include <Windows.h>
#include <winbase.h>
#include <ShellApi.h>
#include <string>
#include <fstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::fstream;

const string version = "0.0.3";
const string versionDate = "June 30, 2020";

#include "Messages.hpp"
#include "status.hpp"
#include "data.h"
#include "userControl.h"


#endif