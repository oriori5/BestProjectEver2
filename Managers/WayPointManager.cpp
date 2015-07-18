/*
 * WayPointsManager.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#include "WayPointManager.h"

// Initialize the target reached flag as FALSE
bool WayPointManager::isTargetReached = false;

WayPointManager::WayPointManager(vector<Location> path, Map map, ConfigurationParametersStruct ParametersStruct)
{
	this->_originalMap = map;

	// Chose grid position way points
	this->initializePositionsArray(path, ParametersStruct);

	// Make the locations vector from the
	this->convertPositionsToWayPointsArray();

	this->_currentWayPoint = 0;
}

WayPoint WayPointManager::continueToNextWayPoint()
{
	this->_currentWayPoint++;
	return (getCurrnetWayPoint());
}

WayPoint WayPointManager::getCurrnetWayPoint()
{
	return (_wayPoints[_currentWayPoint]);
}

bool WayPointManager::isCurrentWayPointLastOne()
{
	return (_currentWayPoint == (_wayPoints.size() - 1));
}

void WayPointManager::initializePositionsArray(vector<Location> fullPath, ConfigurationParametersStruct ParametersStruct)
{
	int robotSize = fmax(ParametersStruct.robot_size_x, ParametersStruct.robot_size_y);
	int robotsInPixel = robotSize / ParametersStruct.map_res_in_cm;

	// We will take way points for each two times of the robot's size
	int wayPointsInterval = robotsInPixel * 2;

	// Setting the way points locations in the positions array (taking each two robot's size)
	for (unsigned i=0; i < fullPath.size(); i += wayPointsInterval)
	{
		this->_positions.push_back(fullPath[i]);
	}

	// If we didn't take the last position (the target) we add it now
	if ((fullPath.size() % wayPointsInterval) != 0)
	{
		this->_positions.push_back(fullPath[fullPath.size() - 1]);
	}

	// Delete the first position (because it is the start point and we already here)
	_positions.erase(_positions.begin());

	// Add the way points to the map
	for (int i = 0; i < _positions.size(); i++)
	{
		Location location = _positions[i];
		_originalMap._map._matrix[location.getY()][location.getX()] = 5;
	}

	// Printing the map with the way points to PNG file
	Map::WriteMapMatrixToPng(_originalMap._map._matrix, _originalMap._map._height, _originalMap._map._width , "WayPointsOnMap.png");
}

void WayPointManager::convertPositionsToWayPointsArray()
{
	// Running over all the way points positions and convert it to a waypoint objects
	for (unsigned i = 0; i < _positions.size() ; i++)
	{
		Location loc((_positions[i].getX() + 1) * Map::map_resolution_in_cm,
					 (_positions[i].getY() + 1) * Map::map_resolution_in_cm);

		this->_wayPoints.push_back(WayPoint(loc,i));
		cout << "way point number " << i << " is (" << loc.getX() << ", " << loc.getY() << ")" << endl;
	}
}

WayPointManager::~WayPointManager()
{
}

