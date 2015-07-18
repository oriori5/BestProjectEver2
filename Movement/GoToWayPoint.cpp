/*
 * GoToWayPoint.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "GoToWayPoint.h"

GoToWayPoint::GoToWayPoint(Robot* robot) : Behavior(robot)
{
	// TODO Auto-generated constructor stub
	isWaypointSet = false;
}

bool GoToWayPoint::startCond()
{
	// check if the robot is near our current waypoint.
    if (_robot->isClosetToLocation(wpManager->getCurrnetWayPoint().getLocation()))
    {
    	isWaypointSet = false; // do it before we select a waypoint. so action will be called.
    	cout << "Started Action_SelectWaypoint" << endl;
    	return true;
    }

    // the robot is not close to the current waypoint. cant switch waypoints.
    return false;
}

bool GoToWayPoint::stopCond()
{
	// if the waypoint was not set, stay in the behaviour.
	// basicly im just making sure the action func ran atleast once.
   return isWaypointSet;
}

void GoToWayPoint::action()
{
	// if you reached your current waypoint, set a new one!
	if (_robot->isClosetToLocation(wpManager->getCurrnetWayPoint().getLocation()))
	{
		if (wpManager->isCurrentWayPointLastOne())
		{
			cout << "Reached the target!!! :-)" << endl;
			WayPointManager::isTargetReached = true;
			isWaypointSet = true;
			return;
		}
		else
		{
			wpManager->continueToNextWayPoint();
		}
	}

	Location waypoint_loc =  wpManager->getCurrnetWayPoint().getLocation();

	// Give the robot his current target. (might be the same way point if he didn't reach it or a new one).
	_robot->setTargetLocation(waypoint_loc);

	isWaypointSet = true;
}

void GoToWayPoint::setWaypointManager(WayPointManager* wp)
{
	this->wpManager = wp;
}

