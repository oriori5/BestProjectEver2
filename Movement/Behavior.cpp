/*
 * Behavior.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */
#include "Behavior.h"

// Ctor
Behavior::Behavior(Robot* robot)
{
	_robot = robot;
}

// Is the index is free?
bool Behavior::isFree(int startIndex, int endIndex, double distance)
{
	bool free = true;

	// All over the index
	for(int index = startIndex; index<=endIndex; index++)
	{
		// Get the distance
		float dist = _robot->getLaserDistance(index);

		if(dist < distance)
		{
			free = false;
			break;
		}
	}

	return free;
}

// Add behaviors
void Behavior::addNextBehavior(Behavior* next)
{
	_behaviorVector.push_back(next);
}

// Select next behavior
Behavior* Behavior::selectNext()
{
	//Run over vector and return first true condition
	for (int i=0; i < _behaviorVector.size(); i++)
	{
		if (_behaviorVector[i]->startCond())
		{
			return _behaviorVector[i];
		}
	}

	return this;
}

// Dtor
Behavior::~Behavior()
{

}


