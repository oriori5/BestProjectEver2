/*
 * PlanGoToTarget.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "PlanGoToTarget.h"

PlanGoToTarget::PlanGoToTarget(Robot* robot, WayPointManager* wpManager) : PlanGoToTarget(robot)
{
    ((GoToWayPoint*)_behaviorsTree[0])->setWaypointManager(wpManager);
}

PlanGoToTarget::PlanGoToTarget(Robot* robot) : Plan(robot)
{
	// Create the nodes of ALL the behaviors
	_behaviorsTree[0] = new GoToWayPoint(robot);
	_behaviorsTree[1] = new GoRotate(robot);
	_behaviorsTree[2] = new GoForward(robot);
	_behaviorsTree[3] = new GoObstacle(robot);

	// Add the nodes of GoToWayPoint behavior (like a state machine)
	_behaviorsTree[0]->addNextBehavior(_behaviorsTree[1]);

	// Add the nodes of GoRotate behavior (like a state machine)
	_behaviorsTree[1]->addNextBehavior(_behaviorsTree[2]);
	_behaviorsTree[1]->addNextBehavior(_behaviorsTree[3]);

	// Add the nodes of GoForward behavior (like a state machine)
	_behaviorsTree[2]->addNextBehavior(_behaviorsTree[0]);
	_behaviorsTree[2]->addNextBehavior(_behaviorsTree[1]);
	_behaviorsTree[2]->addNextBehavior(_behaviorsTree[3]);

	// Add the nodes of GoObstacle behavior (like a state machine)
	_behaviorsTree[3]->addNextBehavior(_behaviorsTree[0]);
	_behaviorsTree[3]->addNextBehavior(_behaviorsTree[1]);

	// Set the first behavior to begin with
	_behaviorToBeginWith = _behaviorsTree[0];
}

PlanGoToTarget::~PlanGoToTarget()
{
	/*for(int i=0;i<3;i++)
	{
		delete _behaviorsTree[i];
	}*/
}
Behavior* PlanGoToTarget::getBehvaiorToBeginWith()
{
	return this->_behaviorToBeginWith;
}

