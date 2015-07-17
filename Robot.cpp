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

	_lc = new Localization(*_pp, _lp, map);

	_pp->SetMotorEnable(true);
	int i;

	//Bug in player
	for(i=0;i<15;i++)
	{
		_pc->Read();
	}
}

bool turnOnTheNoise = false;

void Robot::read()
{
	_pc->Read();
}
void Robot::setSpeed(float speed, float angularSpeed)
{
	_pp->SetSpeed(speed,angularSpeed);
}

void Robot::setSpeed(double xSpeed, double ySpeed, double yaw)
{
	_pp->SetSpeed(xSpeed,ySpeed,yaw);
}
double Robot::getLaserDistance(int index)
{
	return _lp->GetRange(index);
}

double RandGauss(double min, double max, double avg, double stdandartDiviotion)
{
	double random = (min + (max-min) * (double)rand()/RAND_MAX); //create random domain between [min,max]

	return random;
}

double Robot::GetCurentYaw()
{
	return _pp->GetYaw();
}

Location Robot::getCurrentLocation()
{
	Location a(_lc->getEstimatedLocation().GetLocation().getX() / 100,_lc->getEstimatedLocation().GetLocation().getY() / 100);
	return (a);
}

float Robot::getYaw()
{
	return (_lc->getEstimatedLocation().getYaw());
}

void Robot::Update()
{
	_lc->UpdateParticles();
	Location meters_robot_loc = getCurrentLocation();
}

bool Robot::isObstacle(bool* blocked_right)

	// Check if blocked from the right.
	if (!isRightSideClear())
	{
		// if still blocked but turning side was decided - keep it.
		if (!decision_made)
		{
			decided_direction_is_left = true;

			//_pp.SetSpeed(0.0, -0.3);
			decision_made = true;
		}
	}
	// Check if blocked from the left or front.
	else if (!left_flank_clear() || (*_lp)[forward] < 0.4f)
	{
		if (!decision_made)
		{
			decided_direction_is_left = false;
			//_pp.SetSpeed(0.0, 0.3);
			decision_made = true;
		}
	}
	// if not blocked from both sides - reset desition.
	else
	{
		//pp.SetSpeed(1.0,0);
		decision_made = false;
	}

	*is_blocked_from_right = decided_direction_is_left;

	if (decision_made)
	{
		cout << "BLOCKED BLOCKED BLOCKED" << endl;
	}

	return decision_made;
}

bool Robot::isRightSideClear()
{

	double min_distance = 1000;
	for(int i = forward; i < 566; i+= 5)
	{
		min_distance = MIN(min_distance, (*_lp)[i]);
		// If the obstacle is near the front, stay further away.
		if ((*_lp)[i] < 0.6)
	    {
			//report_obstacle(i,(*_lp)[i], _pp);
	    	return false;
	    }
	}

	cout << "min obstacle distance right : " << min_distance << endl;
	return true;
}

bool Robot::isLeftSideClear()
{
	double min_distance = 1000;
	for(int i = 100; i < forward; i+= 5)
	{
		min_distance = MIN(min_distance, (*_lp)[i]);
		// If the obstacle is near the front, stay further away.
	    if ((*_lp)[i] < 0.6)
	    {
	    	//report_obstacle(i,(*_lp)[i], _pp);
	    	return false;
	    }
	}

	cout << "min obstacle distance left : " << min_distance << endl;
	return true;
}

bool Robot::isClosetToLocation(Location location)
{
    float distance = getCurrentLocation().Distance(loc);

	if (distance < 1.0f) // TODO : check what does "near" mean in numbers...
	{
		return true;
	}

	return false;
}

void Robot::setTargetLocation(Location target)
{
	this->target_location = target;
}

Location Robot::getTargetLocation()
{
	return this->target_location;
}




























Robot::~Robot()
{

}
