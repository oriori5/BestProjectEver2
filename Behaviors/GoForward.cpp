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
	_robot->setSpeed(1.0f,0.0f);
}

bool GoForward::stopCond()
{
	if(!isFree(Resources::forwardStartIndex,Resources::forwardEndIndex,0.42))
	{
		return true;
	}

	return false;
}

GoForward::~GoForward()
{

}
