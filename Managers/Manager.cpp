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
	_curr = pln->getBehvaiorToBeginWith();
}

void Manager::run()
{
	// Read and update data from the robot
	_robot->read();
	_robot->Update();

	// As long as we have behavior to perform and we didn't reached the target
	while(_curr !=NULL && !WayPointManager::isTargetReached)
	{
		// Run the current behavior until it finish
		while(_curr->stopCond() == false)
		{
			_curr->action();
			_robot->read();
			_robot->Update();
		}

		// Go to the next behavior
		_curr = _curr->selectNext();
		_robot->read();
		_robot->Update();
	}
}

Manager::~Manager()
{
}
