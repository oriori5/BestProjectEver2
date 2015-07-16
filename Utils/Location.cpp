/*
 * Location.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "Location.h"

Location::Location() {
	// TODO Auto-generated constructor stub

}

Location::~Location() {
	// TODO Auto-generated destructor stub
}

Location Location::getRelativePosition(Directions direction)
{
	Location relative;
	switch(direction)
	{
	case Up:
		relative = Location(getX(), getY() - 1);
		break;
	case Up_Right:
		relative = Location(getX() + 1, getY() - 1);
		break;
	case Right:
		relative = Location(getX() + 1, getY());
		break;
	case Down_Right:
		relative = Location(getX() + 1, getY() + 1);
		break;
	case Down:
		relative = Location(getX(), getY() + 1);
		break;
	case Down_Left:
		relative = Location(getX() - 1 , getY() + 1);
		break;
	case Left:
		relative = Location(getX() - 1, getY());
		break;
	case Up_Left:
		relative = Location(getX() - 1, getY() - 1);
		break;
	}

	return relative;
}

