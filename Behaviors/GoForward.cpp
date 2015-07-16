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
		return true;
	return false;
}

ActionResult GoForward::action()
{
	float speed = 0.5;

	_robot->setSpeed(speed,0.0);

	ActionResult result(0, 0);

	return result;
}

bool GoForward::stopCond()
{
	if(!isFree(Resources::forwardStartIndex,Resources::forwardEndIndex,0.42))
		return true;
	return false;
}

GoForward::~GoForward()
{

}
