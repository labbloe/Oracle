/*
Contains data handling functions regarding the user
and component inventory.
*/


void inventory_com(string fileadd)
{
    string userInput;
    string filePath = fileadd + "/data/storage/inventory.csv";
    printFile(fileadd + "/data/storage/invMsg.txt");
    getline(cin,userInput,'\n');

    fstream(myFile);
    string line;
    myFile.open(fileadd + "/data/storage/inv_info.dat");
    getline(myFile,line,',');
    myFile.close();
    int numComponents = stoi(line);
    component *comp = new component[numComponents];

    //fill_component_list(filePath,*&comp);
    myFile.open(fileadd + "/data/storage/inventory.csv");
    for(int i=0; i<numComponents; i++)
    {
        getline(myFile,line,',');
        strcpy(comp[i].name,line.c_str());
        getline(myFile,line,',');
        strcpy(comp[i].desc,line.c_str());
        getline(myFile,line,',');
        strcpy(comp[i].area,line.c_str());
        getline(myFile,line,',');
        comp[i].val = stoi(line);
        getline(myFile,line,',');
        comp[i].qty = stoi(line);
    }

    if(userInput == "print")
    {
        cout<<"NAME      "
            <<"DESCRIPTION                                       "
            <<"AREA                "
            <<"VALUE"
            <<"  QTY\n";
        for(int i=0; i<numComponents; i++)
        {
            comp[i].inventoryPrint(filePath);
        }
        cout<<endl;
    }
        //inventoryPrint(filePath);
    if(userInput == "add");
        //inventoryAdd(filePath);
    
    delete[] comp;
}

void component::inventoryPrint(string filePath)
{
    for(int i=0; i<10; i++)
        cout<<name[i];
    for(int i=0; i<50; i++)
        cout<<desc[i];
    for(int i=0; i<20; i++)
        cout<<area[i];
    cout<<"$"<<val<<"  "<<qty;
}

void inventoryAdd(string filePath,int numComponents)
{

}

/*void inventoryPrint(string filePath)
{
    fstream(myFile);
    int width = 6;
    int height = 0;
    string line;
    myFile.open(filePath);
    while(myFile.eof())
    {
        getline(myFile,line,'\n');
        height++;
    }
    myFile.close();
    height = height - 6;
    string inv[width][height];

    inv[0][0] = "NAME";
    inv[1][0] = "DESCRIPTION";
    inv[2][0] = "AREA";
    inv[3][0] = "SUPPLIER";
    inv[4][0] = "UNIT VALUE";
    inv[5][0] = "QTY";

    myFile.open(filePath);
    if(myFile.is_open())
    {
        while(line != "Name,Description,Area,Supplier,Unit Value,Qty,")
            getline (myFile,line,'\n');

        int i = 0;
        int j = 1;
        while(myFile.eof())
        {
            getline(myFile,line,',');
            if(i > width)
            {
                i = 0;
                j++;
            }
            inv[i][j] = line;
        }
        myFile.close();

        for(int x=0; x<height; x++)
        {
            for(int z=0; z<width; z++)
            {
                cout<<inv[z][x];
                if(z = width)
                    cout<<endl;
            }
        }
    }
    else cout<< "Unable to open file: "<<filePath<<endl;
}*/