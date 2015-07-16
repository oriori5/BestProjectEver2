/*
 * TurnLeft.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */
#include "TurnLeft.h"

TurnLeft::TurnLeft(Robot* robot):Behavior(robot)
{

}

bool TurnLeft::startCond()
{
	//cout<<"Left startCond"<<endl;
	if(isFree(Resources::leftStartIndex,Resources::leftEndIndex,0.5))
		return true;
	return false;
}

ActionResult TurnLeft::action()
{
	float angularSpeed = 0.5;

	//cout<<"Left Action"<<endl;
	_robot->setSpeed(0.0,angularSpeed);

	ActionResult result(0,7);

	return result;

}

bool TurnLeft::stopCond()
{
	if(isFree(Resources::forwardStartIndex,Resources::forwardEndIndex,0.5))
	{
		//cout<<"Stopping left behavior"<<endl;
		return true;
	}
	return false;
}

TurnLeft::~TurnLeft()
{

}
