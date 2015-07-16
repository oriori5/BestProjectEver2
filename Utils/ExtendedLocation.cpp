/*
 * ExtendedLocation.cpp
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#include "ExtendedLocation.h"

ExtendedLocation::ExtendedLocation():Location()
{
	Yaw = 0;
}

ExtendedLocation::ExtendedLocation(float yaw):Location()
{
	Yaw = yaw;
}

ExtendedLocation::ExtendedLocation(int x, int y, float yaw):Location(x, y)
{
	//SetLocation(x, y);
	Yaw = yaw;
}

Location ExtendedLocation::GetLocation()
{
	Location loc(getX(),getY());

	return loc;
}

void ExtendedLocation::SetLocation(int x, int y)
{
	Location(x, y);
}

float ExtendedLocation::getYaw()
{
	return Yaw;
}

void ExtendedLocation::setYaw(float yaw)
{
	Yaw = yaw;
}
