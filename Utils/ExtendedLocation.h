/*
 * ExtendedLocation.h
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#ifndef EXTENDEDLOCATION_H_
#define EXTENDEDLOCATION_H_

#include "../Utils/Location.h"

class ExtendedLocation : public Location
{
private:
	float Yaw;
public:
	float getYaw();
	void setYaw(float yaw);
	ExtendedLocation();
	ExtendedLocation(float yaw);
	ExtendedLocation(int x, int y, float yaw);
	void SetLocation(int x, int y);
	Location GetLocation();



};

#endif /* EXTENDEDLOCATION_H_ */
