/*
 * PlanGoToTarget.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "PlanGoToTarget.h"

PlanGoToTarget::PlanGoToTarget(Robot* robot) : Plan(robot)
{
	//Creating Behaviors
	_beh[0] = new GoToWayPoint(robot); // first thing to be done! EVEN if start cond doesnt return true.
	_beh[1] = new GoRotate(robot);
	_beh[2] = new GoForward(robot);
	_beh[3] = new GoObstacle(robot);
	//Connecting Behaviors
	_beh[0]->addNextBehavior(_beh[1]); // first select a waypoint and than move to it.
	_beh[1]->addNextBehavior(_beh[2]);
	_beh[1]->addNextBehavior(_beh[3]); // will only reach here if drive couldnt be started (aka blocked!) so handle obstacle.
	_beh[2]->addNextBehavior(_beh[0]); // driving can lead to a waypoint -> and then we select a new one.
	_beh[2]->addNextBehavior(_beh[1]); // ORI ADDED
	_beh[2]->addNextBehavior(_beh[3]); // driving can lead to obstacle
	_beh[3]->addNextBehavior(_beh[0]); // avoiding obstacles might lead to waypoint -> and then we select a new one.
	_beh[3]->addNextBehavior(_beh[1]); // avoiding obstacles will change our angle, we need to set it back on target.
	_start = _beh[0];
}

PlanGoToTarget::PlanGoToTarget(Robot* robot, WayPointManager* wpManager) : PlanGoToTarget(robot)
{
    ((GoToWayPoint*)_beh[0])->setWaypointManager(wpManager);
}

PlanGoToTarget::~PlanGoToTarget()
{
	// TODO Auto-generated destructor stub
	for(int i=0;i<3;i++)
		delete _beh[i];
}
Behavior* PlanGoToTarget::getStartPoint()
{
	return this->_start;
}

