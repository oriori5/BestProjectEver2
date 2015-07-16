/*
 * Location.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef LOCATION_H_
#define LOCATION_H_

#include "../Consts.h"

class Location
{
private:
	int _x;
	int _y;

public:
	Location(int x, int y)
	{
		_x = x;
		_y = y;
	};
	Location();
	virtual ~Location();
	Location getRelativePosition(Directions direction);

	int getX()
	{
		return (_x);
	}

	int getY()
	{
		return (_y);
	}

};

#endif /* LOCATION_H_ */
