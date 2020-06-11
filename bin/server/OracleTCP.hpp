/*
    Server/Client and core.cpp mixed header
*/

#include <iostream>
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../CoreRegistry.h"

using std::cout;
using std::endl;
using std::string;

const int BufferSize = 128;
char serverBuffer[BufferSize];