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
            cout<<setw(20)<<left<<"\nNAME"<<setw(49)<<left<<"DESCRIPTION"
                <<setw(19)<<left<<"LOCATION"<<setw(8)<<left<<"VALUE"
                <<setw(4)<<left<<"QTY"<<"\n";
            for(int j=0; j<101; j++)
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
    cout<<setw(19)<<left<<name<<setw(49)<<left<<desc
        <<setw(19)<<left<<area<<"$"<<setw(7)<<left<<val
        <<setw(4)<<left<<qty;
}

void inventoryAdd(string fileadd,int &numComponents,component comp[])
{
    cout<<"Add new component(s) by using the following format\n"
        <<"NAME,DESCRIPTION,LOCATION,VALUE,QTY,\n"
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
                      <<comp[i].desc<<","
                      <<comp[i].area<<","
                      <<comp[i].val<<","
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
    if(commaCnt != 5)
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