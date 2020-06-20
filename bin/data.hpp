/*
Contains data handling functions regarding the user
and component inventory.
*/


void inventory_com(string fileadd)
{
    //INITIALIZATIONS
    string userInput;
    string filePath = fileadd + "/data/storage/inventory.csv";
    printFile(fileadd + "/data/storage/invMsg.txt");
    cout<<"Inventory:> ";
    getline(cin,userInput,'\n');

    //GET INVENTORY DATA INFO
    fstream(myFile);
    string line;
    myFile.open(fileadd + "/data/storage/inv_info.dat");
    getline(myFile,line,',');
    myFile.close();
    int numComponents = stoi(line);
    component *comp = new component[numComponents];

    //STORE INVENTORY DATA INFO
    fill_component_list(filePath,*&comp,numComponents);

    //INVENTORY MENU OPERATION

    while(userInput != "exit")
    {
        if(userInput == "print")
        {
            cout<<setw(22)<<left<<"\nNAME"<<setw(10)<<left<<"TYPE"<<setw(49)<<left<<"DESCRIPTION"
                <<setw(19)<<left<<"LOCATION"<<setw(8)<<left<<"VALUE"
                <<setw(4)<<left<<"QTY"<<"\n";
            for(int j=0; j<111; j++)
                cout<<"=";
            cout<<'\n';

            //PRINT ENTIRE INVENTORY 
            for(int i=0; i<numComponents; i++)
            {
                comp[i].inventoryPrint();
                cout<<'\n';
            }
            cout<<endl;
            cout<<"Inventory:> ";
            getline(cin,userInput,'\n');
        }
        else if (userInput == "add")
        {
            inventoryAdd(fileadd,numComponents,comp);
            cout<<"Inventory:> ";
            getline(cin,userInput,'\n');
        }
        else if (userInput == "remove")
        {
            inventoryRemove(fileadd,numComponents,comp);
            cout<<"Inventory:> ";
            getline(cin,userInput,'\n');
        }
        else if(userInput == "edit")
        {
            inventoryEdit(fileadd,comp,numComponents);
            cout<<"Inventory:> ";
            getline(cin,userInput,'\n');
        }
        else if(userInput == "search")
        {
            inventorySearch(fileadd,comp,numComponents);
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

void component::inventoryPrint()
{
    cout<<setw(21)<<left<<name<<setw(10)<<left<<type<<setw(49)<<left<<desc
        <<setw(19)<<left<<area<<"$"<<setw(7)<<left<<val
        <<setw(4)<<left<<qty;
}

void inventoryAdd(string fileadd,int &numComponents,component comp[])
{
    cout<<"Add new component(s) by using the following format\n"
        <<"NAME,TYPE,DESCRIPTION,LOCATION,VALUE,QTY,\n"
        <<"WRITE VALUE WITHOUT DECIMAL. EX: 0.10 -> 010\n"
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
            myFile.open(fileadd + "/data/storage/inventory.csv");
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
            fill_component_list(fileadd + "/data/storage/inventory.csv",comp,numComponents);
            std::ofstream ofs(fileadd + "/data/storage/inv_info.dat",std::ofstream::trunc);
            ofs<<numComponents<<",\nnum_of_components,";
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

void inventoryRemove(string fileadd, int &numComponents, component comp[])
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
        if(comp[comMatch].qty <= 0)
        {
            cout<<"\nThis component has a QTY of Zero. Would\n"
                <<"you like to remove it? [y/n] ";
            string tempin;
            getline(cin,tempin,'\n');
            if(tempin[0] == 'y')
                remove_from_list(fileadd,comp,comMatch,numComponents);
        }
    }
}

void remove_from_list(string fileadd,component comp[],int comMatch, int &numComponents)
{
    string filePath = fileadd + "/data/storage/invetory.csv";
    std::ofstream ofs(fileadd + "/data/storage/inventory.csv",std::ofstream::trunc);
    for(int i=0; i<numComponents; i++)
    {
        if(i != comMatch)
        {
            ofs<<comp[i].name<<","<<comp[i].desc<<","
               <<comp[i].area<<","<<(comp[i].val * 100)<<","
               <<comp[i].qty<<",\n";
        }
    }
    ofs.close();
    numComponents--;
    delete[] comp;
    comp = new component[numComponents];
    std::ofstream info(fileadd + "/data/storage/inv_info.dat",std::ofstream::trunc);
    info<<numComponents<<",\nnum_of_components,";
    info.close();

    fill_component_list(filePath,*&comp,numComponents);
    
}

void inventoryEdit(string fileadd,component comp[],int numComponents)
{
    cout<<"\n"
        <<"Type 'exit' to leave menu\n"
        <<"Format: name_of_component,\n\n"
        <<"Inventory:search> ";
    string input;
    string comValue;
    string comChange;
    bool firstVal = false;
    int comMatch;
    getline(cin,input,'\n');

    while(input != "exit")
    {
        if(searchCheck(input,comp,numComponents,comMatch) == false)
        {
            if(input == "exit")
                return;
            cout<<"\nError: Components '"<<input<<"' Not Found\n"
                <<"Inventory:search> ";
            getline(cin,input,'\n');
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
            std::ofstream ofs(fileadd + "/data/storage/inventory.csv",std::ofstream::trunc);
            for(int i=0; i<numComponents; i++)
            {
                ofs<<comp[i].name<<","<<comp[i].type<<","<<comp[i].desc<<","
                   <<comp[i].area<<","<<(comp[i].val * 100)<<","
                   <<comp[i].qty<<",\n";
            }
            ofs.close();

            string line;
            fstream(myFile);
            myFile.open(fileadd + "/data/storage/inventory.csv");       //issue with calling fill_component_inventory()
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

void inventorySearch(string fileadd,component comp[],int numComponents)
{
    return;
}