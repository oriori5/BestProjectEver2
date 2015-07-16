/*
 * Manager.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, Plan* pln)
{
	_robot = robot;
	_curr = pln->getStartPoint();
}

void Manager::run()
{
	_robot->read();
	if(!(_curr->startCond()))
		return;
	_curr->action();
	while(_curr !=NULL)
	{
		while(_curr->stopCond() == false)
		{
			_curr->action();
			_robot->read();
		}
		_curr = _curr->selectNext();
		_robot->read();
	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}
