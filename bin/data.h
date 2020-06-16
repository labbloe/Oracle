/*
Contains header information for data.hpp
*/

#ifndef DATA_H
#define DATA_H

#include "CoreRegistry.h"
#include <iomanip>
using std::stoi;
using std::left;
using std::setw;

class component
{
    public:
        float val = 0.00;
        int qty = 0;

        string name;
        string desc;
        string area;

        //prints entire inventory list
        void inventoryPrint(int curComponent);
};

//add components to inventory list
void inventoryAdd(string filePath,int numComponents);

//ensures correct user input for adding component to list
bool addCheck(string input);

//fills comp dynamic array with all components in inventory
void fill_component_list(string filePath, component *comp);

#include "data.hpp"
#endif