/*
 * Location.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef LOCATION_H_
#define LOCATION_H_

#include "Consts.h"
#include <math.h>

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

	inline float Magnitude(Location& v)
	{
		return(sqrtf((v.getX() * v.getX()) + (v.getY() * v.getY())));

	}

	inline float Distance(Location& v)
	{
		int XxX = (v.getX() - getX()) * (v.getX() - getX());
		int YxY = (v.getY() - getY()) * (v.getY() - getY());
		return (sqrt(XxX + YxY));
		//return(sqrtf((v.getX() - getX()) * v.getX() - getX()) +( (v.getY() - getY()) * (v.getY() - getY())));
	}

	int getX()
	{
		return (_x);
	}

	int getY()
	{
		return (_y);
	}

	void setX(int x)
	{
		_x = x;
	}

	void setY(int y)
	{
		_y = y;
	}

	Location operator -(const Location& v) const
	{
	    return (Location(_x - v._x, _y - v._y));
	}

	Location operator /(float t) const
	{
		   return (Location(_x / t, _y / t));
	}

	Location& operator /=(float t)
	{
	    float f = 1.0F / t;
	    _x *= f;
	    _y *= f;
	    return (*this);
	}

	Location& Normalize(void)
	{
	    return (*this /= sqrtf(_x * _x + _y * _y));
	}

};

#endif /* LOCATION_H_ */
