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
    match = readCommand(fileadd + "MessageLogs/commandList.txt",input);
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

void help_com(string fileadd) {printFile(fileadd + "MessageLogs/helpList.txt");cout<<endl;}

void status_com(string fileadd) {integratedModuleReport(fileadd);}

void warranty_com(string fileadd) {printFile(fileadd + "MessageLogs/warranty.txt");cout<<endl;}

void version_com() {cout<<endl<<"Oracle Version "<<version<<endl<<"Updated as of "<<versionDate<<endl<<endl;}

void clear_com(string fileadd) {system("cls");printFile(fileadd + "MessageLogs/startingMessage.txt");}

void run_com(string fileadd)
{
    string input;
    cout<<"For list of programs type 'list'"<<endl
        <<"Enter Program: ";
    getline(cin,input,'\n');
    if(input == "list")
    {
        printFile(fileadd + "MessageLogs/programList.txt");
        cout<<endl;
        run_com(fileadd);
    }
    if(input == "kicad")
        ShellExecute(NULL,"open","A:\\Programs\\KiCad\\bin\\kicad.exe",NULL,"A",SW_SHOWNORMAL);
    if(input == "word")
        ShellExecute(NULL,"open","C:\\Program Files (x86)\\Microsoft Office\\root\\Office16\\WINWORD.exe",NULL,"C:",SW_SHOWNORMAL);
    if(input == "cmd")
        ShellExecute(NULL,"open","C:\\WINDOWS\\system32\\cmd.exe",NULL,"C:",SW_SHOWNORMAL);
    if(input == "powershell")
        ShellExecute(NULL,"open","C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe",NULL,"C:",SW_SHOWNORMAL);
    if(input == "chrome")
        ShellExecute(NULL,"open","C:\\Program Files (x86)\\Google\\Chrome\\Application\\chrome.exe",NULL,"C:",SW_SHOWNORMAL);
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