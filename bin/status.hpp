/*
Contains all functions related to modifying
or returning the staus of integrated 
modules or information pertaining to them
*/

#include "CoreRegistry.h"


class ipinfo
{
    public:
    string netName;
    string ipv4;
    string ipv6;

    void ipInfoFiller(string sectionName, string fileadd);
};

void userInfo::startup()
{
    fstream(userFile);
    userFile.open("../bin/data/user/info.DAT");
    if(userFile.is_open())
    {
        getline(userFile,FirstName,',');
        getline(userFile,LastName,',');
        getline(userFile,email,',');
        getline(userFile,phone,',');
    }
    else
    {
        userFile.close();
        std::ofstream userFile("../bin/data/user/info.DAT");
        cout << "User Registration\n\nFirst Name: ";
        cin >> FirstName;
        cout << "Last Name: ";
        cin >> LastName;
        cout << "Email (optional): ";
        cin >> email;
        cout << "Phone Number (optional, no dashes): ";
        cin >> phone;
        cout <<"\n\nThank you for providing your user information\nWelcome to Oracle\n\nGenerating necessary startup files...\n\n";

        userFile << FirstName + "," + LastName + "," + email + "," + phone;
        userFile.close();
        std::ofstream inv("../bin/data/storage/inventory.DAT");
        inv << "10,resistor,THT Resistor,SMALL_BIN_A,10,10,";
        std::ofstream invDat("../bin/data/storage/inv_info.DAT");
        invDat << "1,15,\nnum_of_components,num_of_types,";
    }
    
}

void integratedModuleReport(string fileadd)
{
    ipinfo ethernet;
    ipinfo pdanet;
    ipinfo wifi;
    
    cout<<endl
        <<"---------------------------"<<endl
        <<"Oracle Integration Report: "<<endl<<endl;

    cout<<"VERSION..............."<<version<<endl;

    //int BufferSize = 32767;
    //TCHAR infoBuf[BufferSize];
    //DWORD bufCharCount = BufferSize;
    //GetComputerName(infoBuf,&bufCharCount);
    //cout<<"COMPUTER ID..........."<<infoBuf<<endl;

    //TCHAR infoBufNm[BufferSize];
    //GetUserName(infoBufNm,&bufCharCount);
    //cout<<"USER ID..............."<<infoBufNm<<endl;

    ethernet.ipInfoFiller("Ethernet adapter Ethernet:",fileadd);
    cout<<"Ethernet NetName......"<<ethernet.netName<<endl;
    cout<<"Ethernet IPv4........."<<ethernet.ipv4<<endl;

    pdanet.ipInfoFiller("Ethernet adapter PdaNet Broadband Connection:",fileadd);
    cout<<"PdaNet NetName........"<<pdanet.netName<<endl;
    cout<<"PdaNet IPv4..........."<<pdanet.ipv4<<endl;

    wifi.ipInfoFiller("Wireless LAN adapter Wi-Fi 2:",fileadd);
    cout<<"WiFi NetName.........."<<wifi.netName<<endl;
    cout<<"WiFi IPv4............."<<wifi.ipv4<<endl;

    cout<<"---------------------------"<<endl<<endl;
}

void ipinfo::ipInfoFiller(string sectionName, string fileadd)
{
    string tempFile = "cd" + fileadd + "cmdLogs && ipconfig > iplog.txt | type iplog.txt > nul";
    const char* s = tempFile.c_str();
    system(s);
    string sectionCheck;
    string line;
    string DNS_Suffix = "NOT FOUND";
    string IPv6_Address = "NOT FOUND";
    string IPv4_Address = "NOT FOUND";

    netName = DNS_Suffix;
    ipv6 = IPv6_Address;
    ipv4 = IPv4_Address;

    string filePath = fileadd +"cmdLogs/iplog.txt";
    fstream(myFile);
    myFile.open(filePath);

    if(myFile.is_open())
    {
        //NETNAME 
        
        while(sectionCheck != sectionName)
            getline(myFile,sectionCheck);
        while((line[25] != 'S')&&(line[27] != 'S'))
            getline(myFile,line,'\n');
        if(line.length() > 39)
        {
            netName = "";
            for(int i=0; i<(line.length() - 39); i++)
                netName += line[i+39];
        }

        //IPV4
        int cnt = 0;
        while((line[3] != 'I')&&(line[6] != '4')&&(cnt < 2))
        {
            getline(myFile,line,'\n');
            cnt++;
        }
        if(line.length() > 39)
        {
            ipv4 = "";
            for(int i=0; i<(line.length() - 39); i++)
                ipv4 += line[i+39];
        }
        if((line[3] != 'I')&&(line[6] != '4'))
            ipv4 = "NOT FOUND";
    }
    else
    {
        cout<<"ERROR: iplog not generated. See ipInfoFiller() system() command."<<endl;
        netName = "NULL";
        ipv4 = "NULL";
        ipv6 = "NULL";
    }
    myFile.close();
    
}
