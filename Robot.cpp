/*
 * Robot.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#include "Robot.h"

Robot::Robot(char* ip, int port)
{
	_pc = new PlayerClient(ip,port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);

	_pp->SetMotorEnable(true);
	int i;

	//Bug in player
	for(i=0;i<15;i++)
		_pc->Read();
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


Robot::~Robot()
{

}
