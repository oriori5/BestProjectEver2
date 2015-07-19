/*
 * Robot.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(char* ip, int port, Map map)
{
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);
	_map = map;

	// Loop to set the real position of the robot in the real world
	// (this is because bug of the player/robot)
	for (int i = 0; i < 20; ++i)
	{
		_pp->SetOdometry(9.05, 7.625, 0.35);
		_pc->Read();
		cout << "current x = " << _pp->GetXPos() << ", current y = " << _pp->GetYPos() << ", current yaw = " << _pp->GetYaw() << endl;
	}

	//_pp->SetOdometry(2.175, -2.875, 0.35); // For simulation robot

	_lc = new Localization(*_pp, _lp, map);

	isStillBlocked = false;
	shouldTurnleft = false;

	_pp->SetMotorEnable(true);

	// Fix the bug in the laser
	for(int i=0; i < 15; i++)
	{
		_pc->Read();
	}
}

void Robot::read()
{
	_pc->Read();
}

void Robot::setSpeed(float speed, float angularSpeed)
{
	_pp->SetSpeed(speed,angularSpeed);
}

double Robot::getLaserDistance(int index)
{
	return _lp->GetRange(index);
}

/*
 * Get the yaw from the robot
 */
double Robot::GetCurentYaw()
{
	return _pp->GetYaw();
}

Location Robot::getCurrentLocation()
{
	return (Location(_lc->getPredictedLocation().GetLocation().getX(),_lc->getPredictedLocation().GetLocation().getY()));
}

/*
 * Get the yaw from the localization manager
 */
float Robot::getYaw()
{
	return (fabs(_lc->getPredictedLocation().getYaw()));
}

void Robot::Update()
{
	_pc->Read();
	_lc->UpdateParticles();
}

bool Robot::isObstacle(bool* blocked_right)
{
	// Check if the robot blocked from the right side
	if (!isRightSideFree())
	{
		// Check if the robot didn't set already as blocked
		if (!isStillBlocked)
		{
			shouldTurnleft = true;
			isStillBlocked = true;
		}
	}
	// Check if the robot blocked from the left side or from the front
	else if (!isLeftSideFree() || (*_lp)[333] < 0.4f)
	{
		// Check if the robot didn't set already as blocked
		if (!isStillBlocked)
		{
			shouldTurnleft = false;
			isStillBlocked = true;
		}
	}
	// Not blocked from both sides
	else
	{
		isStillBlocked = false;
	}

	*blocked_right = shouldTurnleft;

	if (isStillBlocked)
	{
		cout << "Help me! I am blocked :(" << endl;
	}

	return isStillBlocked;
}

/*
 * Checking if the right side of the robot is free
 */
bool Robot::isRightSideFree()
{
	double minimal_obstacle_found = 1000;

	// Reading all the right side of the laser
	for(int i = 333; i < 566; i+= 5)
	{
		minimal_obstacle_found = MIN(minimal_obstacle_found, (*_lp)[i]);

		// If the current laser read discovered obstacle in less than 60 CM then
		// decide that the right side is NOT free
		if ((*_lp)[i] < 0.6)
	    {
	    	return false;
	    }
	}

	cout << "minimal obstacle distance right = " << minimal_obstacle_found << endl;

	// We didn't found obstacle in less than 60 CM then the right side is free!
	return true;
}

/*
 * Checking if the left side of the robot is free
 */
bool Robot::isLeftSideFree()
{
	double minimal_distance_found = 1000;

	// Reading all the left side of the laser
	for(int i = 100; i < 333; i+= 5)
	{
		minimal_distance_found = MIN(minimal_distance_found, (*_lp)[i]);

		// If the current laser read discovered obstacle in less than 60 CM then
		// decide that the left side is NOT free
	    if ((*_lp)[i] < 0.6)
	    {
	    	return false;
	    }
	}

	cout << "minimal obstacle distance left = " << minimal_distance_found << endl;

	// We didn't found obstacle in less than 60 CM then the left side is free!
	return true;
}

bool Robot::isCloseToLocation(Location location)
{
    float distance = getCurrentLocation().Distance(location);

    // Checking if we close to the given location (in radius of 30 CM)
	if (distance < 30.0f)
	{
		return true;
	}

	return false;
}

void Robot::setTargetLocation(Location target)
{
	this->_target = target;
}

Location Robot::getTargetLocation()
{
	return this->_target;
}




























Robot::~Robot()
{

}
