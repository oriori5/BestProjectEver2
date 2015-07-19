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

	//_pp->SetOdometry(9.05, 7.625, 0.35); // For real robot

	for (int i = 0; i < 20; ++i)
	{
		_pp->SetOdometry(9.05, 7.625, 0.35);
		_pc->Read();
		cout << "current x = " << _pp->GetXPos() << ", current y = " << _pp->GetYPos() << ", current yaw = " << _pp->GetYaw() << endl;
	}
	/*while (_pp->GetXPos() != 9.05 || _pp->GetYPos() != 7.625 || _pp->GetYaw() != 0.35)
	{
		_pp->SetOdometry(9.05, 7.625, 0.35);
	}*/
	//_pp->SetOdometry(2.175, -2.875, 0.35); // For simulation robot

	//Bug in player
	/*for(int i=0;i<15;i++)
	{
		_pc->Read();
	}*/

	//double x = _pp->GetXPos();
	//double y = _pp->GetYPos();

	_lc = new Localization(*_pp, _lp, map);

	get_call = false;
	get_call_left = false;

	_pp->SetMotorEnable(true);
	//int i;
	for(int i=0;i<15;i++)
	{
		_pc->Read();
	}
}

bool turnOnTheNoise = false;

void Robot::read()
{
	//== 1
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
	Location a(_lc->getPredictedLocation().GetLocation().getX(),_lc->getPredictedLocation().GetLocation().getY());
	//Location a(_lc->getEstimatedLocation().GetLocation().getX() / 100,_lc->getEstimatedLocation().GetLocation().getY() / 100);
	return (a);
}

float Robot::getYaw()
{
	return (fabs(_lc->getPredictedLocation().getYaw()));
}

void Robot::Update()
{
	_pc->Read();
	_lc->UpdateParticles();
	Location meters_robot_loc = getCurrentLocation();
}

bool Robot::isObstacle(bool* blocked_right)
{
// Check if blocked from the right.
	if (!isRightSideClear())
	{
		// if still blocked but turning side was decided - keep it.
		if (!get_call)
		{
			get_call_left = true;

			//_pp.SetSpeed(0.0, -0.3);
			get_call = true;
		}
	}
	// Check if blocked from the left or front.
	else if (!isLeftSideClear() || (*_lp)[333] < 0.4f)
	{
		if (!get_call)
		{
			get_call_left = false;
			//_pp.SetSpeed(0.0, 0.3);
			get_call = true;
		}
	}
	// if not blocked from both sides - reset desition.
	else
	{
		//pp.SetSpeed(1.0,0);
		get_call = false;
	}

	*blocked_right = get_call_left;

	if (get_call)
	{
		cout << "BLOCKED BLOCKED BLOCKED" << endl;
	}

	return get_call;
}

bool Robot::isRightSideClear()
{

	double min_distance = 1000;
	for(int i = 333; i < 566; i+= 5)
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
	for(int i = 100; i < 333; i+= 5)
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
    float distance = getCurrentLocation().Distance(location);

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
