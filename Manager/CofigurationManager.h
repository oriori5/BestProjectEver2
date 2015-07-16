/*
 * CofigurationManager.h

 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */


#ifndef COFIGURATIONMANAGER_H_
#define COFIGURATIONMANAGER_H_

#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "../Utils.h"

using namespace std;

 struct ConfigurationParametersStruct
{
	string map_path;
	int robot_location_x;
	int robot_location_y;
	int robot_location_yaw;
	int dest_x;
	int dest_y;
	int robot_size_x;
	int robot_size_y;
	double map_res_in_cm;
	double grid_res_in_cm;
};

class CofigurationManager
{
public:
	CofigurationManager();
	virtual ~CofigurationManager();
	ConfigurationParametersStruct ReadFromFile();
};

#endif /* COFIGURATIONMANAGER_H_ */
