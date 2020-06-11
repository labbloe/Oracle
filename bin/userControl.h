/*
Header file for userControl.hpp
*/

#ifndef USERCONTROL_H
#define USERCONTROL_H

#include "CoreRegistry.h"

//compares userInput to all commands listed in the command text documents located at filePath. Returns input if match found.
string readCommand(string filePath,string userInput);

//takes user input and determines where (and if) a function should be called. 
void InputSelection(string filepath, string input);

//prints help.txt
void help_com(string fileadd);

//prints integratedModuleReport located in status.hpp
void status_com(string fileadd);

//prints warranty.txt
void warranty_com(string fileadd);

//prints Oracle version number
void version_com();

//clears console window
void clear_com(string fileadd);

//runs a specified program
void run_com(string fileadd);

//opens remote-server menu
void server_com();


#include "userControl.hpp"
#endif