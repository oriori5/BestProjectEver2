/*
 * CofigurationManager.cpp
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#include "CofigurationManager.h"


CofigurationManager::CofigurationManager()
{
	// TODO Auto-generated constructor stub

}

ConfigurationParametersStruct CofigurationManager::ReadFromFile()
{
	// Open the parameters file
		ifstream file("parameters.txt");
		ConfigurationParametersStruct ParametersStruct;

		// Checking if the file wasn't opened (for any reason)
		if (!file.is_open())
		{
			// Print error and exit the program
			cout << "Error while reading the parameters file!";

		}
		// The file was opened successfully
		else
		{

			string line1, line2, line3, line4, line5, line6;

			// Read the first 6 lines in the file (this is the required params)
			getline(file, line1);
			getline(file, line2);
			getline(file, line3);
			getline(file, line4);
			getline(file, line5);
			getline(file, line6);

			std::vector<std::string> arr;

			// Get the map path (line 1)
			arr = Utils::split(line1, " ");
			string map_path = arr[1].c_str();
			ParametersStruct.map_path = map_path.substr(0, map_path.length() - 1); // Remove last character because it is new line

			// Get the robot location (line 2)
			arr = Utils::split(line2, " ");
			ParametersStruct.robot_location_x = atoi(arr[1].c_str());
			ParametersStruct.robot_location_y = atoi(arr[2].c_str());
			ParametersStruct.robot_location_yaw = atoi(arr[3].c_str());

			// Get the destination point (line 3)
			arr = Utils::split(line3, " ");
			ParametersStruct.dest_x = atoi(arr[1].c_str());
			ParametersStruct.dest_y = atoi(arr[2].c_str());

			// Get the robot size (line 4)
			arr = Utils::split(line4, " ");
			ParametersStruct.robot_size_x = atoi(arr[1].c_str());
			ParametersStruct.robot_size_y = atoi(arr[2].c_str());

			// Get the map resolution (line 5)
			arr = Utils::split(line5, " ");
			ParametersStruct.map_res_in_cm = atof(arr[1].c_str());

			// Get the grid resolution (line 6)
			arr = Utils::split(line6, " ");
			ParametersStruct.grid_res_in_cm = atof(arr[1].c_str());

			// Print the details (we don't really need to print it... just printing to check if we read
			// successfully all the details)
			cout << "the params that was read are:" << endl;
			cout << "map path = " << map_path << endl;
			cout << "robot location (x,y,yaw) = " << ParametersStruct.robot_location_x << "," << ParametersStruct.robot_location_y << "," << ParametersStruct.robot_location_yaw << endl;
			cout << "destination point (x,y) = " << ParametersStruct.dest_x << "," << ParametersStruct.dest_y << endl;
			cout << "robot size = " << ParametersStruct.robot_size_x << " x " << ParametersStruct.robot_size_y << " CM" << endl;
			cout << "map resolution = " << ParametersStruct.map_res_in_cm << endl;
			cout << "grid resolution = " << ParametersStruct.grid_res_in_cm << endl;

		}

		return ParametersStruct;

}

CofigurationManager::~CofigurationManager()
{
	// TODO Auto-generated destructor stub
}

