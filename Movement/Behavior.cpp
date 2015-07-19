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

/*
 * Checking if the front of the area is clear
 */
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
	_vecOptionalNextBehaviors.push_back(next);
}

// Select next behavior
Behavior* Behavior::selectNext()
{
	// Run over the next optional behaviors and choose the better behavior to use
	for (int i=0; i < _vecOptionalNextBehaviors.size(); i++)
	{
		if (_vecOptionalNextBehaviors[i]->startCond())
		{
			return _vecOptionalNextBehaviors[i];
		}
	}

	return this;
}

// Dtor
Behavior::~Behavior()
{

}


