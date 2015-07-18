/*
 * GoForward.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "GoForward.h"

GoForward::GoForward(Robot* robot):Behavior(robot)
{

}

bool GoForward::startCond()
{
	if(isFree(Resources::forwardStartIndex,Resources::forwardEndIndex,0.43))
	{
		return true;
	}

	return false;
}

void GoForward::action()
{
	_robot->setSpeed(0.3f,0.0f);
}

bool GoForward::stopCond()
{
	Location loc = _robot->getTargetLocation();
	cout << "Forward, current loc = (" << _robot->getCurrentLocation().getX() << "," << _robot->getCurrentLocation().getY() << ")" << endl;
	cout << "Forward, target loc = (" << loc.getX() << "," << loc.getY() << ")" << endl;
	cout << "Forward, distance from target: " << _robot->getCurrentLocation().Distance(loc) << endl;
	if (_robot->getCurrentLocation().Distance(loc) < 40.0f)
	{
		return (true);
	}

	if(!isFree(Resources::forwardStartIndex,Resources::forwardEndIndex,0.40))
	{
		return true;
	}

	return false;
}

GoForward::~GoForward()
{

}
