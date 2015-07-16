/*
 * TurnRight.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "TurnRight.h"

TurnRight::TurnRight(Robot* robot):Behavior(robot)
{

}

bool TurnRight::startCond()
{
	//cout<<"Right startCond"<<endl;
	if(isFree(Resources::rightStartIndex,Resources::rightEndIndex,0.42))
		return true;
	return false;
}

ActionResult TurnRight::action()
{
	float angularSpeed = -0.5;
	double dYaw = 0;

	_robot->setSpeed(0.0,angularSpeed);

	ActionResult result(0,dYaw);

	return result;
}

bool TurnRight::stopCond()
{
	if(isFree(Resources::forwardStartIndex,Resources::forwardEndIndex,0.5))
		{
			//cout<<"Stopping right behavior"<<endl;
			return true;
		}
		return false;
}

TurnRight::~TurnRight()
{

}
