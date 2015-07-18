/*
 * GoObstacle.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "GoObstacle.h"

GoObstacle::GoObstacle(Robot* robot) : Behavior(robot)
{
	// TODO Auto-generated constructor stub
    obstacle_from_right = false;
    drive_away = false;
    drive_away_start_time = 999;
}

bool GoObstacle::startCond()
{
	cout << "started Action_Obstacle" <<endl;
    return true; // if the drive action returned false it comes here, therefore no need to check.
}
bool GoObstacle::stopCond()
{
    if (!_robot->isObstacle(&obstacle_from_right))
    {
    	if(drive_away)
    	{
    	   return false; // we are not blocked and moving forward
    	}
    	else if (float(drive_away_start_time) == 999) // we are not blocked but need to move away.
    	{
    		drive_away = true;
    		drive_away_start_time = clock();
    		return false;
    	}
    	else // not blocked and moved away
    	{
    		drive_away = false;
    		drive_away_start_time = 999;
    		return true;
    	}

    }

    return false;
}
void GoObstacle::action()
{
	if ((_robot->isObstacle(&obstacle_from_right)))
	{
		// turn to the most 'free' side to avoid obstable.
	    // later try driving to the latest waypoint as instructed.
	    if (obstacle_from_right)
	    {
		    // turn left
		    _robot->setSpeed(0.0f, -0.3f);
	    }
	    else
	    {
		    // turn right
		    _robot->setSpeed(0.0f, 0.3f);

	    }
	}
	else if (drive_away)
	{
		if(clock() - drive_away_start_time >= DRIVE_AWAY_TIME_SECONDS)
		{
			_robot->setSpeed(0.0f,0.0f); // stop moving for now.
		   drive_away = false; // finished driving away.
		}
		// if we still need to move away, do it.
		else
		{
			_robot->setSpeed(1.0f, 0.0f);
		}
	}

}
