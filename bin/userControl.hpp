/*
All functions related to User controls
*/


string readCommand(string filePath,string userInput)
{
    string line;
    bool match = false;
    fstream(myFile);
    myFile.open(filePath);
    if(myFile.is_open())
    {
        while(getline(myFile,line))
        {
            if(line == userInput)
            {
                match = true;
                return line;
            }
        }
        if((match == false) && (userInput != ""))
            cout<<"'"<<userInput<<"' is not a recognized command. Type 'help' for list of commands."<<endl;
        
    }
    else
        cout<<"ERROR: Command File Not Found"<<endl;
    
    return "none";
    
}

void InputSelection(string fileadd, string input)
{
    string match;
    match = readCommand(fileadd + "MessageLogs/comRef.DAT",input);
    if(match != "none")
    {
        if(match == "help")
            help_com(fileadd);
        if(match == "status")
            status_com(fileadd);
        if(match == "warranty")
            warranty_com(fileadd);
        if(match == "version")
            version_com();
        if(match == "clear")
            clear_com(fileadd);
        if(match == "run")
            run_com(fileadd);
        if(match == "server")
            server_com();
        if(match == "inventory")
            inventory_com(fileadd);
    }

}

void help_com(string fileadd) {printFile(fileadd + "MessageLogs/hlpdisp.DAT");cout<<endl;}

void status_com(string fileadd) {integratedModuleReport(fileadd);}

void warranty_com(string fileadd) {printFile(fileadd + "MessageLogs/warranty.DAT");cout<<endl;}

void version_com() {cout<<endl<<"Oracle Version "<<version<<endl<<"Updated as of "<<versionDate<<endl<<endl;}

void clear_com(string fileadd) {system("cls");printFile(fileadd + "MessageLogs/StrtMsg.DAT");}

void run_com(string fileadd)
{
    string input;
    cout<<"For list of programs type 'list'"<<endl
        <<"Enter Program: ";
    getline(cin,input,'\n');
    if(input == "list")
    {
        printFile(fileadd + "MessageLogs/progRef.DAT");
        cout<<endl;
        run_com(fileadd);
    }

}

void server_com()
{
    string exit = "temp";
    string UserInput;
    cout<<"\nWARNING: Server operation removes user control at local station"<<endl  
        <<"         press ctrl+c to exit server and Oracle application."<<endl<<endl;
    cout<<"Start remote-server? [y/n] ";
    while((exit[0] != 'y') && (exit[0] != 'n'))
    {
        getline(cin,exit,'\n');
        if((exit[0] != 'y') && (exit[0] != 'n'))
            cout<<"Please select [y/n] ";
    }
    if(exit[0] == 'n')
        UserInput = "none";
    if(exit[0] == 'y')
    {
        cout<<endl;
        system("cd ../bin/server && a.exe");
    }
}