/*
 * WayPointsManager.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#include "WayPointManager.h"

WayPointManager::WayPointManager(vector<Location> path, Map map, ConfigurationParametersStruct ParametersStruct)
{
	this->_originalMap = map;

	// Chose grid position way points
	this->initializePositionsArray(path, ParametersStruct);

	// Make the locations vector from the
	initializeWayPointsWrray();

	this->_currentWayPoint = 0;
}

