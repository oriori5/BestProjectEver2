/*
 * MapHandler.cpp
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#include "MapHandler.h"

MapHandler::MapHandler()
{
}

Map MapHandler::RunMapProcessing(ConfigurationParametersStruct ParametersStruct)
{
	// Set the robot size to be the max number between the its measurements
	double robot_size = std::max(ParametersStruct.robot_size_x, ParametersStruct.robot_size_y);

	// Save the map and grid resolutions
	Map::map_resolution_in_cm = ParametersStruct.map_res_in_cm;
	Map::grid_resolution_in_cm = ParametersStruct.grid_res_in_cm;

	// Create the map object
	Map mapObj;

	// Read the map from png file and put it in the map matrix
	Map::ReadMapFromPngToMatrix(ParametersStruct.map_path.c_str(), mapObj._map._matrix, mapObj._map._height, mapObj._map._width);

	// Calculate how much cells (pixels) we need to blow around each obstacle in the map
	int blowing_factor = ((robot_size / 2) / Map::map_resolution_in_cm) +
						 (fmod(robot_size / 2, Map::map_resolution_in_cm) == 0 ? 0 : 1);

	//Map::WriteMapMatrixToPng(mapObj._map_matrix, mapObj._map_height, mapObj._map_width, "before_blow.png");

	// Blow the map
	Map::BlowMap(mapObj._map._matrix, mapObj._map._height, mapObj._map._width, blowing_factor);

	//Map::WriteMapMatrixToPng(mapObj._map_matrix, mapObj._map_height, mapObj._map_width, "after_blow.png");

	// Convert the map to grid (according to the map and grid resolutions)
	mapObj.ConvertMapToGrid();

	// Return the map object
	return mapObj;
}

MapHandler::~MapHandler()
{
}

