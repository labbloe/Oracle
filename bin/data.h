/*
Contains header information for data.hpp
*/

#ifndef DATA_H
#define DATA_H

#include "CoreRegistry.h"
using std::stoi;

class component
{
    public:
        float val = 0.00;
        int qty = 0;

        char name[10] = {'\0'};
        char desc[50] = {'\0'};
        char area[20] = {'\0'};

        //prints entire inventory list
        void inventoryPrint(string filePath);

        //add component to inventory list
        void inventoryAdd(string filePath,int numComponents);
};

//fills comp dynamic array with all components in inventory
void fill_component_list(string filePath, component *comp);

#include "data.hpp"
#endif