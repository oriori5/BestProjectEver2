/*
 * WayPoint.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef UTILS_WAYPOINT_H_
#define UTILS_WAYPOINT_H_

#include "Location.h"

class WayPoint
{
private:

	Location _location;
	unsigned _number;

public:
	WayPoint(Location location, unsigned number)
	{
		_location = location;
		_number = number;
	}

	Location& getLocation()
	{
		return _location;
	}

	unsigned getNumber()
	{
		return _number;
	}
};

#endif /* UTILS_WAYPOINT_H_ */
