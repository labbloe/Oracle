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
    cout<<std::fixed<<std::setprecision(2);
    for(int i=0; i<numComponents; i++)
    {
        getline(myFile,line,',');
        //strcpy(comp[i].name,line.c_str());
        comp[i].name = line;
        getline(myFile,line,',');
        //strcpy(comp[i].desc,line.c_str());
        comp[i].desc = line;
        getline(myFile,line,',');
        //strcpy(comp[i].area,line.c_str());
        comp[i].area = line;
        getline(myFile,line,',');
        comp[i].val = (((float) stoi(line))/100);
        getline(myFile,line,',');
        comp[i].qty = stoi(line);
        getline(myFile,line,'\n');
    }
    myFile.close();

    if(userInput == "print")
    {
        cout<<setw(20)<<left<<"\nNAME"<<setw(49)<<left<<"DESCRIPTION"
            <<setw(19)<<left<<"AREA"<<setw(7)<<left<<"VALUE"
            <<setw(4)<<left<<"QTY"<<"\n";
        for(int j=0; j<101; j++)
            cout<<"=";
        cout<<'\n';

        for(int i=0; i<numComponents; i++)
        {
            comp[i].inventoryPrint(i);
            cout<<'\n';
        }
        cout<<endl<<endl;
    }
    if(userInput == "add");
        //inventoryAdd(filePath);
    
    delete[] comp;
}

void component::inventoryPrint(int curComponent)
{
    cout<<setw(19)<<left<<name<<setw(49)<<left<<desc
        <<setw(19)<<left<<area<<"$"<<setw(6)<<left<<val
        <<setw(4)<<left<<qty;
}

void inventoryAdd(string filePath,int numComponents)
{

}