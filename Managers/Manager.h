/*
 * Manager.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include "../Movement/Behavior.h"
#include "../Robot/Robot.h"
#include "../Movement/Plan.h"
#include "WayPointManager.h"

class Manager
{
private:
	Behavior* _curr;
	Robot* _robot;

public:
	// Ctor and Dtor
	Manager(Robot* robot, Plan* pln);
	virtual ~Manager();

	/*
	 * The main function that run the manager
	 */
	void run();
};

#endif /* MANAGER_H_ */
