/*
 * WayPointManager.h
 *
 *  Created on: Jun 9, 2015
 *      Author: colman
 */

#ifndef WAYPOINTMANAGER_H_
#define WAYPOINTMANAGER_H_

#include <vector>

#include "WayPointManager.h"
#include "CofigurationManager.h"
#include "../Utils/LocationMatrix.h"
#include "../Utils/Location.h"
#include "../Utils/WayPoint.h"
#include "../Map/Map.h"
#include <cmath>
#include <iostream>

using namespace std;

class WayPointManager
{
public:
	// Indication if we reached the tareget location
	static bool isTargetReached;

private:
	Map _originalMap;
	vector<Location> _positions;
	vector<WayPoint> _wayPoints;
	unsigned _currentWayPoint;

public:
	// Ctor and Dtor
	WayPointManager(vector<Location> path, Map map, ConfigurationParametersStruct ParametersStruct);
	virtual ~WayPointManager();

	/*
	 * Continue to the next way point (and return the new way point)
	 */
	WayPoint continueToNextWayPoint();

	/*
	 * Get the current way point
	 */
	WayPoint getCurrnetWayPoint();

	/*
	 * Return indication if the current way point is the last one
	 */
	bool isCurrentWayPointLastOne();

private:
	/*
	 * Initialize the positions array with way points (that we will choose from the full path)
	 */
	void initializePositionsArray(vector<Location> fullPath, ConfigurationParametersStruct ParametersStruct);

	/*
	 * Convert the positions array to way points objects array
	 */
	void convertPositionsToWayPointsArray();
};

#endif /* WAYPOINTSMANAGER_H_ */
