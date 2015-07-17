/*
 * PlnObstacleAvoid.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "PlnObstacleAvoid.h"

PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot) : Plan(robot)
{
	//Creating Behaviors
		_beh[0] = new Action_SelectWaypoint(robot); // first thing to be done! EVEN if start cond doesnt return true.
		_beh[1] = new Action_Rotate(robot);
		_beh[2] = new Action_Drive(robot);
		_beh[3] = new Action_Obstacle(robot);
		//Connecting Behaviors
		_beh[0]->addBeh(_beh[1]); // first select a waypoint and than move to it.
		_beh[1]->addBeh(_beh[2]);
		_beh[1]->addBeh(_beh[3]); // will only reach here if drive couldnt be started (aka blocked!) so handle obstacle.
		_beh[2]->addBeh(_beh[0]); // driving can lead to a waypoint -> and then we select a new one.
		_beh[2]->addBeh(_beh[3]); // driving can lead to obstacle
		_beh[3]->addBeh(_beh[0]); // avoiding obstacles might lead to waypoint -> and then we select a new one.
		_beh[3]->addBeh(_beh[1]); // avoiding obstacles will change our angle, we need to set it back on target.
		_start = _beh[0];
}

PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot, WayPointManager* wpManager) : PlnObstacleAvoid(robot)
{
    ((Action_SelectWaypoint*)_beh[0])->setWaypointManager(wpManager);
}

Behavior* PlnObstacleAvoid::getStartPoint()
{
	return this->_start;
}


PlnObstacleAvoid::~PlnObstacleAvoid()
{
	// TODO Auto-generated destructor stub
	for(int i=0;i<3;i++)
		delete _beh[i];
}
