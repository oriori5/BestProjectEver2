/*
 * GoForward.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "GoForward.h"

// Ctor
GoForward::GoForward(Robot* robot):Behavior(robot)
{
}

// Start Condition
bool GoForward::startCond()
{
	// If the index is free
	if(isFree(FORWARD_START_INDEX,FORWARD_END_INDEX,0.43))
	{
		return true;
	}

	return false;
}

// Action!
void GoForward::action()
{
	_robot->setSpeed(0.2f,0.0f);
}

// Stop Condition
bool GoForward::stopCond()
{
	// Get the target location of the robot
	Location loc = _robot->getTargetLocation();

	// Debug prints
	cout << "Forward, current yaw = " << _robot->GetCurentYaw() << endl;
	cout << "Forward, get yaw = " << _robot->getYaw() << endl;
	cout << "Forward, current loc = (" << _robot->getCurrentLocation().getX() << "," << _robot->getCurrentLocation().getY() << ") / (" << (_robot->getCurrentLocation().getX() / 2.5) << "," << (_robot->getCurrentLocation().getY() / 2.5) << ")" << endl;
	cout << "Forward, target loc = (" << loc.getX() << "," << loc.getY() << ") / (" << (loc.getX() / 2.5) << "," << (loc.getY() / 2.5) << ")" << endl;
	cout << "Forward, distance from target: " << _robot->getCurrentLocation().Distance(loc) << endl;

	// If the distance is less then 30..
	if (_robot->getCurrentLocation().Distance(loc) < 30.0f)
	{
		cout << "Forward, becuade distance" << endl;

		return (true);

	}

	// If the index not free..
	if(!isFree(FORWARD_START_INDEX,FORWARD_END_INDEX,0.40))
	{
		cout << "Forward, becuade is not free" << endl;

		return (true);
	}

	return false;
}

// Dtor
GoForward::~GoForward()
{

}
