/*
 * TurnInPlace.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "TurnInPlace.h"

TurnInPlace::TurnInPlace(Robot* robot):Behavior(robot)
{

}

double orginYaw = 0;

bool TurnInPlace::startCond()
{
	orginYaw = 0;
	return true;
}

ActionResult TurnInPlace::action()
{
	//cout<<"TurnInPlace Action"<<endl;

	_robot->setSpeed(0.0,-1.0);
}

bool TurnInPlace::stopCond()
{
	double yawOffset = _robot->GetCurentYaw() - orginYaw;

	//Offset is 180 degrees
	if(abs(yawOffset) >= 1.75)
	{
		//cout<<"stop turn in place, yawoffset: "<<yawOffset<<endl;
		return true;
	}
	return false;
}

TurnInPlace::~TurnInPlace()
{

}
