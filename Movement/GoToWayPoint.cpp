/*
 * GoToWayPoint.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "GoToWayPoint.h"

GoToWayPoint::GoToWayPoint(Robot* robot) : Behavior(robot)
{
	canSetNewWayPoint = false;
}

bool GoToWayPoint::startCond()
{
	// Check if we should proceed to the next way point
    if (_robot->isClosetToLocation(wpManager->getCurrnetWayPoint().getLocation()))
    {
    	canSetNewWayPoint = false;
    	cout << "Started Action_SelectWaypoint" << endl;
    	return true;
    }

    // No need to switch way point
    return false;
}

bool GoToWayPoint::stopCond()
{
	// If we can't set new way point we stay in this behavior
    return canSetNewWayPoint;
}

void GoToWayPoint::action()
{
	// If you reached your current waypoint, set the next one
	if (_robot->isClosetToLocation(wpManager->getCurrnetWayPoint().getLocation()))
	{
		// If we reached the last way point
		if (wpManager->isCurrentWayPointLastOne())
		{
			cout << "Reached the target!!! :-)" << endl;
			WayPointManager::isTargetReached = true;
			canSetNewWayPoint = true;
			return;
		}
		// We are not in the last way point, keep going
		else
		{
			wpManager->continueToNextWayPoint();
			cout << "Switched to the next waypoint" << endl;
		}
	}

	Location waypoint_loc =  wpManager->getCurrnetWayPoint().getLocation();

	// Set the target location to the robot (If we reached a way point, assign new one,
	// if not, we stay in the current way point)
	_robot->setTargetLocation(waypoint_loc);

	canSetNewWayPoint = true;
}

void GoToWayPoint::setWaypointManager(WayPointManager* wp)
{
	this->wpManager = wp;
}

