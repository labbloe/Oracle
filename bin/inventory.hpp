/*
Contains data handling functions regarding the
component inventory.
*/


void inventory_com(string fileadd)
{
    //INITIALIZATIONS
    string userInput;
    string filePath = fileadd + "/data/storage/inventory.DAT";
    printFile(fileadd + "/data/storage/invMsg.DAT");
    cout<<"Inventory:> ";
    getline(cin,userInput,'\n');

    //GET INVENTORY DATA INFO
    fstream(myFile);
    string line;
    myFile.open(fileadd + "/data/storage/inv_info.DAT");
    getline(myFile,line,',');
    int numComponents = stoi(line);
    getline(myFile,line,',');
    int numTypes = stoi(line);
    myFile.close();
    component *comp = new component[numComponents];

    //STORE INVENTORY DATA INFO
    fill_component_list(filePath,*&comp,numComponents);

    //INVENTORY MENU OPERATION

    while(userInput != "exit")
    {
        if(userInput == "print")
        {
            printHeader();
            float value = 0;
            //PRINT ENTIRE INVENTORY 
            for(int i=0; i<numComponents; i++)
            {
                comp[i].inventoryPrint();
                value += (comp[i].qty * comp[i].val);
                cout<<'\n';
            }
            printFooter(numComponents,value);
            cout<<endl;
            cout<<"Inventory:> ";
            getline(cin,userInput,'\n');
        }
        else if (userInput == "add")
        {
            inventoryAdd(fileadd,numComponents,comp,numTypes);
            cout<<"Inventory:> ";
            getline(cin,userInput,'\n');
        }
        else if (userInput == "remove")
        {
            inventoryRemove(fileadd,numComponents,comp,numTypes);
            cout<<"Inventory:> ";
            getline(cin,userInput,'\n');
        }
        else if(userInput == "edit")
        {
            inventoryEdit(fileadd,comp,numComponents,numTypes);
            cout<<"Inventory:> ";
            getline(cin,userInput,'\n');
        }
        else if(userInput == "search")
        {
            inventorySearch(fileadd,comp,numComponents,numTypes);
            cout<<"Inventory:> ";
            getline(cin,userInput,'\n');
        }
        else if(userInput == "export")
        {
            //int BufferSize = 32767;
            //DWORD bufCharCount = BufferSize;
            //TCHAR infoBufNm[BufferSize];
            //GetUserName(infoBufNm,&bufCharCount);
            //string temp = infoBufNm;
            std::ofstream inv("home/desktop");
            for(int i=0; i<numComponents; i++)
            {
                inv<<comp[i].name<<","<<comp[i].type<<","
                   <<comp[i].desc<<","<<comp[i].area<<","
                   <<comp[i].val<<","<<comp[i].qty<<"\n";
            }
            inv.close();
            cout<<"Inventory:> ";
            getline(cin,userInput,'\n');
        }
        
        else
        {
            cout<<"'"<<userInput<<"' is an unrecognized command\nInventory:> ";
            getline(cin,userInput,'\n');
        }
    }
    
    delete[] comp;
}

void printHeader()
{
    cout<<setw(22)<<left<<"\nNAME"<<setw(10)<<left<<"TYPE"<<setw(49)<<left<<"DESCRIPTION"
        <<setw(19)<<left<<"LOCATION"<<setw(8)<<left<<"VALUE"
        <<setw(4)<<left<<"QTY"<<"\n";
    for(int j=0; j<111; j++)
        cout<<"=";
    cout<<'\n';
}

void printFooter(int numComponents,float value)
{
    for(int i=0; i<111; i++)
        cout<<".";

    cout<<"\nNumber of Components: "<<numComponents
        <<"   Inventory Value: $"<<value<<"\n";

    for(int i=0; i<111; i++)
        cout<<".";
    cout<<"\n";
}

void component::inventoryPrint()
{
    cout<<setw(21)<<left<<name<<setw(10)<<left<<type<<setw(49)<<left<<desc
        <<setw(19)<<left<<area<<"$"<<setw(7)<<left<<val
        <<setw(4)<<left<<qty;
}

void inventoryAdd(string fileadd,int &numComponents,component comp[], int &numTypes)
{
    cout<<"Add new component(s) by using the following format\n"
        <<"NAME,TYPE,DESCRIPTION,LOCATION,VALUE,QTY,\n"
        <<"WRITE VALUE WITHOUT DECIMAL. EX: 0.10 -> 010\n"
        <<"Type 'print' to create an Excel accessible .csv spreadsheet to the desktop\n"
        <<"Type 'exit' to leave.\n\nInventory:add> ";

    string input;
    int commaCnt = 0;
    
    while(1)
    {
        getline(cin,input,'\n');
        if(input == "exit")
            return;
        
        //ADD NEW COMPONENT TO SHEET AND DYNAMIC ARRAY
        if(addCheck(input) == true)
        {
            string temp;
            fstream(myFile);
            myFile.open(fileadd + "/data/storage/inventory.DAT");
            for(int i=0; i<numComponents; i++)
            {
                myFile<<comp[i].name<<","
                      <<comp[i].type<<","
                      <<comp[i].desc<<","
                      <<comp[i].area<<","
                      <<(comp[i].val*100)<<","
                      <<comp[i].qty<<",\n";
            }
            myFile << input;
            myFile.close();
            
            numComponents++;
            delete[] comp;
            comp = new component[numComponents];
            fill_component_list(fileadd + "/data/storage/inventory.DAT",comp,numComponents);
            std::ofstream ofs(fileadd + "/data/storage/inv_info.DAT",std::ofstream::trunc);
            ofs<<numComponents<<","<<numTypes<<",\n"<<"num_of_components,num_of_types,";
            ofs.close();
        }
    }
    cout<<"\n";
}

bool addCheck(string input)
{
    int commaCnt = 0;
    for(int i=0; i<input.length(); i++)
    {
        if(input[i] == ',')
            commaCnt++;
    }
    if(commaCnt != 6)
    {
        cout<<"ERROR: Incorrect input format\n";
        cout<<"Inventory:add> ";
        return false;
    }
    else
    {
        cout<<"Inventory:add> ";
        return true;
    }
    

    return false;
}

void fill_component_list(string filePath,component comp[],int numComponents)
{
    string line;
    fstream(myFile);
    myFile.open(filePath);
    cout<<std::fixed<<std::setprecision(2);
    for(int i=0; i < numComponents; i++)
    {
        getline(myFile,line,','); 
        comp[i].name = line;
        getline(myFile,line,',');
        comp[i].type = line;
        getline(myFile,line,',');
        comp[i].desc = line;
        getline(myFile,line,',');
        comp[i].area = line;
        getline(myFile,line,',');
        comp[i].val = (((float) stoi(line))/100);
        getline(myFile,line,',');
        comp[i].qty = stoi(line);
        getline(myFile,line,'\n');
    }
    myFile.close();
}

void fill_inventory_file(string fileadd, component comp[],int numComponents)
{
    string filePath = fileadd + "/data/storage/inventory.DAT";
    std::ofstream ofs(fileadd + "/data/storage/inventory.DAT",std::ofstream::trunc);
    for(int i=0; i<numComponents; i++)
    {
        ofs<<comp[i].name<<","<<comp[i].type<<","<<comp[i].desc<<","
            <<comp[i].area<<","<<(comp[i].val * 100)<<","
            <<comp[i].qty<<",\n";

    }
    ofs.close();
}

bool searchCheck(string input,component comp[],int numComponents, int &comMatch)
{
    int inLength = input.length();
    int temp = 0;
    int cnt = 0;
    string comName;
    for(int i=0; i<input.length(); i++)
    {
        if(input[i] == ',')
            cnt++;
        if(cnt == 0)
            comName += input[i];
        else
            break;
    }
    if(cnt == 1)
    {
        for(int i=0; i<numComponents; i++)
        {
            if(comName == comp[i].name)
            {   
                comMatch = i;
                return true;
            }
        }
    }
    return false;
}

void inventoryRemove(string fileadd, int &numComponents, component comp[],int &numTypes)
{
    cout<<"\nType 'exit' to leave menu\n"
        <<"Use the following format: name_of_item,qty_to_remove\n"
        <<"Inventory:remove> ";
    string input;
    string comName;
    string tmpQty;
    int comMatch;
    int cnt = 0;
    bool match = false;
    while((match == false) && (input != "exit"))
    {
        getline(cin,input,'\n');
        if(searchCheck(input,comp,numComponents,comMatch) == false)
        {
            if(input != "exit")
                cout<<"ERROR: NAME NOT FOUND\nInventory:remove> ";
        }
        else if(input != "exit");
        {
            match = true;
            for(int i=0; i<input.length(); i++)
            {
                if(input[i] == ',')
                {
                    cnt++;
                    i++;
                }
                if(cnt == 0)
                    comName += input[i];
                else
                    tmpQty += input[i];
            }
        }
    }
    if((match == true)&&(input != "exit"))
    {
        comp[comMatch].qty -= stoi(tmpQty);
        fill_inventory_file(fileadd,comp,numComponents);
        if(comp[comMatch].qty <= 0)
        {
            cout<<"\nThis component has a QTY of Zero. Would\n"
                <<"you like to remove it? [y/n] ";
            string tempin;
            getline(cin,tempin,'\n');
            if(tempin[0] == 'y')
                remove_from_list(fileadd,comp,comMatch,numComponents,numTypes);
        }
    }
}

void remove_from_list(string fileadd,component comp[],int comMatch, int &numComponents,int &numTypes)
{
    string filePath = fileadd + "/data/storage/inventory.DAT";
    std::ofstream ofs(fileadd + "/data/storage/inventory.DAT",std::ofstream::trunc);
    for(int i=0; i<numComponents; i++)
    {
        if(i != comMatch)
        {
            ofs<<comp[i].name<<","<<comp[i].type<<","<<comp[i].desc<<","
               <<comp[i].area<<","<<(comp[i].val * 100)<<","
               <<comp[i].qty<<",\n";
        }
    }
    ofs.close();
    numComponents--;
    delete[] comp;
    comp = new component[numComponents];
    std::ofstream info(fileadd + "/data/storage/inv_info.DAT",std::ofstream::trunc);
    info<<numComponents<<","<<numTypes<<",\n"<<"num_of_components,num_of_types,";
    info.close();

    fill_component_list(filePath,*&comp,numComponents);
    
}

void inventoryEdit(string fileadd,component comp[],int numComponents,int &numTypes)
{
    cout<<"\n"
        <<"Type 'exit' to leave menu\n"
        <<"Format: name_of_component\n\n"
        <<"Inventory:search> ";
    string input;
    string comValue;
    string comChange;
    bool firstVal = false;
    int comMatch;
    getline(cin,input,'\n');
    input += ',';

    while(input != "exit")
    {
        if(searchCheck(input,comp,numComponents,comMatch) == false)
        {
            if(input == "exit")
                return;
            cout<<"\nError: Components '"<<input<<"' Not Found\n"
                <<"Inventory:search> ";
            getline(cin,input,'\n');
            input += ',';
        }
        else
        {
            cout<<"\nFormat: value to edit,new value"
                <<"\nPossible values(name,type,description,location,value,qty)"
                <<"\nInventory:edit> ";
            getline(cin,input,'\n');

            while(1)
            {
                if(input == "exit")
                    return;
                firstVal = false;
                for(int i=0; i<input.length(); i++)
                {
                    if(input[i] == ',')
                    {
                        i++;
                        firstVal = true;
                    }
                    if(firstVal == false)
                        comValue += input[i];
                    else
                        comChange += input[i];
                }
                if(comValue == "name")
                {
                    comp[comMatch].name = comChange;
                    break;
                }
                if(comValue == "type")
                {
                    comp[comMatch].type = comChange;
                    break;
                }
                else if(comValue == "description")
                {
                    comp[comMatch].desc = comChange;
                    break;
                }
                else if(comValue == "location")
                {
                    comp[comMatch].area = comChange;
                    break;
                }
                else if(comValue == "value")
                {
                    comp[comMatch].val = ((float)stoi(comChange)/100);
                    break;
                }
                else if(comValue == "qty")
                {
                    comp[comMatch].qty = stoi(comChange);
                    break;
                }
                else
                {
                    cout<<"\nError: Incorrect format\nInventory:edit> ";
                    getline(cin,input,'\n');
                }
            }
            std::ofstream ofs(fileadd + "/data/storage/inventory.DAT",std::ofstream::trunc);
            for(int i=0; i<numComponents; i++)
            {
                ofs<<comp[i].name<<","<<comp[i].type<<","<<comp[i].desc<<","
                   <<comp[i].area<<","<<(comp[i].val * 100)<<","
                   <<comp[i].qty<<",\n";
            }
            ofs.close();

            string line;
            fstream(myFile);
            myFile.open(fileadd + "/data/storage/inventory.DAT");       //issue with calling fill_component_list()
            cout<<std::fixed<<std::setprecision(2);                     //this is a seperate slightly different verison
            for(int i=0; i < numComponents; i++)                        //Try at some point to fix issue, for now this
            {                                                           //works as expected.
                getline(myFile,line,',');
                comp[i].name = line;
                getline(myFile,line,',');
                comp[i].type = line;
                getline(myFile,line,',');
                comp[i].desc = line;
                getline(myFile,line,',');
                comp[i].area = line;
                getline(myFile,line,',');
                comp[i].val = (((float) stoi(line))/100);
                getline(myFile,line,',');
                comp[i].qty = stoi(line);
                getline(myFile,line,'\n');
            }
            myFile.close();
            return;
        }   


    }
    return;
}

void inventorySearch(string fileadd,component comp[],int numComponents,int numTypes)
{
    cout<<"==============================================================================\n"
        <<"Filter Inventory by the Following Search Criteria 'type','location', or 'name'\n"
        <<"Type 'exit' to Leave Search Menu\n"
        <<"FORMAT: SEARCH_CRITERIA,SEARCH_VALUE\n"
        <<"==============================================================================\n\n"
        <<"Component Types: ";
        fstream(myFile);
        myFile.open(fileadd + "/data/storage/typeLog.DAT");
        string type;
        for(int i=0; i<numTypes; i++)
        {
            getline(myFile,type,'\n');
            cout<<type<<"  ";
            if((i%6 == 0)&&(i != 0))
                cout<<setw(18)<<left<<"\n";
        }
        cout<<"\nInventory:search> ";
    
    string input;

    while(1)
    {
        string searchCriteria;
        string searchValue;
        bool secVal = false;
        getline(cin,input,'\n');
        if(input == "exit")
            return;
        
        for(int i=0; i<input.length(); i++)
        {
            if(input[i] == ',')
            {
                i++;
                secVal = true;
            }
            if(secVal == false)
                searchCriteria += input[i];
            else
                searchValue += input[i];
        }
        cout<<"criteria: "<<searchCriteria<<" val: "<<searchValue<<endl;
        if(searchCriteria == "type")
        {
            printHeader();
            int matchCnt = 0;
            float value = 0;
            for(int i=0; i<numComponents; i++)
            {
                if(comp[i].type == searchValue)
                {
                    comp[i].inventoryPrint();
                    matchCnt++;
                    value += (comp[i].qty * comp[i].val);
                    cout<<"\n";
                }
            }
            printFooter(matchCnt,value);
            cout<<"\n";
        }
        else if(searchCriteria == "location")
        {
            printHeader();
            int matchCnt = 0;
            float value = 0;
            for(int i=0; i<numComponents; i++)
            {
                if(comp[i].area == searchValue)
                {
                    comp[i].inventoryPrint();
                    matchCnt++;
                    value += (comp[i].qty * comp[i].val);
                    cout<<"\n";
                }
            }
            printFooter(matchCnt,value);
            cout<<"\n";
        }
        else if(searchCriteria == "name")
        {   
            float value = 0;
            int cnt = 0;
            printHeader();
            for(int i=0; i<numComponents; i++)
            {
                int matchCnt = 0;
                for(int j=0; j<searchValue.length(); j++)
                {
                    if(comp[i].name[j] == searchValue[j])
                    {
                        matchCnt++;
                        value += (comp[i].qty * comp[i].val);
                    }
                }
                if(matchCnt == searchValue.length())
                {
                    comp[i].inventoryPrint();
                    cnt++;
                    cout<<"\n";
                }
            }
            printFooter(cnt,value);
            cout<<"\n";
        }
        else
            cout<<"ERROR: Incorrect Input Format\n";

        cout<<"Inventory:search> ";
    }

    return;
}