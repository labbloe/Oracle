/*
Messages includes function calls for detail only
or otherwise non-response based messages to the
user
*/

#include "CoreRegistry.h"


void printFile(string filePath)
{
    string line;
    fstream(myFile);
    myFile.open(filePath);
    if(myFile.is_open())
    {
        while(getline (myFile,line))
            cout<< line << endl;
        myFile.close();
    }
    else cout<< "Unable to open file: "<<filePath<<endl;
}

void UserGreeting()
{
    int BufferSize = 32767;
    TCHAR infoBuf[BufferSize];
    DWORD bufCharCount = BufferSize;
    TCHAR infoBufNm[BufferSize];
    GetUserName(infoBufNm,&bufCharCount);
    cout<<"Welcome "<<infoBufNm<<endl<<endl;
}