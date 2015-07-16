/*
 * Behavior.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */
#include "Behavior.h"

Behavior::Behavior(Robot* robot)
{
	_next = NULL;
	_arrSize = 0;
	_robot = robot;
}

Behavior* Behavior::addNext(Behavior* beh)
{
	int i;
	Behavior** tmp = new Behavior*[_arrSize+1];
	if(!tmp)
		return NULL;
	for(i=0;i<_arrSize;i++)
		tmp[i] = _next[i];
	tmp[i] = beh;
	delete []_next;
	_next=tmp;
	_arrSize++;
	return this;
}

Behavior* Behavior::selectNext()
{
	int i;
	for(i=0;i<_arrSize;i++)
		if(_next[i]->startCond())
			return _next[i];

	return NULL;
}

bool Behavior::isFree(int startIndex, int endIndex, double distance)
{
	bool free = true;
	for(int index = startIndex; index<=endIndex; index++)
	{
		float dist = _robot->getLaserDistance(index);

		if(dist < distance)
		{
			free = false;
			break;
		}
	}
	return free;
}

Behavior::~Behavior()
{
	delete [] _next;
}


