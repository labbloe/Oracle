/*
    core.cpp is the main for all Oracle related operations.
    version 0.0.1
*/

#include "CoreRegistry.h"

int main()
{
    string UserInput;
    string exit;
    int commandCnt = 1;
    printFile("../bin/MessageLogs/startingMessage.txt");
    UserGreeting();
    while(UserInput != "exit")
    {
        exit = "temp";
        cout<<"Oracle:"<<commandCnt<<"> ";
        getline(cin,UserInput,'\n');
        InputSelection("../bin/",UserInput);
        commandCnt++;
        if(UserInput == "exit")
        {
            cout<<"Are you sure you want to exit? [y/n] ";
            while((exit[0] != 'y') && (exit[0] != 'n'))
            {
                getline(cin,exit,'\n');
                if((exit[0] != 'y') && (exit[0] != 'n'))
                    cout<<"Please select [y/n] ";
            }
            if(exit[0] == 'n')
                UserInput = "none";
        }
    }

    return 0;
}