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
        void inventoryPrint();
};

//add components to inventory list
void inventoryAdd(string fileadd,int &numComponents,component comp[]);

//removes component qty from inventory list
void inventoryRemove(string fileadd, int &numComponents, component comp[]);

//ensures correct user input for adding component to list
bool addCheck(string input);

//fills comp dynamic array with all components in inventory
void fill_component_list(string filePath, component comp[],int numComponents);

//checks inventory list against a given "input" for a match
bool searchCheck(string input,component comp[],int numComponents,int &comMatch);

//removes a singular component from the inventory list
void remove_from_list(string fileadd,component comp[],int comMatch,int &numComponents);

#include "data.hpp"
#endif