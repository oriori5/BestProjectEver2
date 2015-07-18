/*
 * Utils.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: colman
 */

#include "Utils.h"

std::vector<std::string> Utils::split(std::string str,std::string sep)
{
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

