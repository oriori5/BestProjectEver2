/*
 * Particle.cpp
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#include "Particle.h"


Particle::Particle(float x, float y, float yaw, float belife)
{
	ext_loc.SetLocation(x, y);
	ext_loc.setYaw(yaw);
	setBelief(belife);
}

Particle::~Particle()
{
}

void Particle::Update(int x, int y, float yaw, LaserProxy* _lp, Map& mp)
{
	//float new_x = ext_loc.getLocation().getX() + x;
	//float new_y = ext_loc.getLocation().getY() + y;
	ext_loc.SetLocation((ext_loc.GetLocation().getX() + x), (ext_loc.GetLocation().getY() + y));
	ext_loc.setYaw(fmod((ext_loc.getYaw() + yaw), M_PI*2));
	belief *= calcMove(x, y, yaw)* calcScan(_lp, mp) * 1.05;
}

double Particle::calcMove(int x, int y, float yaw)
{
	return 1.0;
}

double Particle::calcScan(LaserProxy* _lp, Map& mp)
{
	unsigned bad_calls = 0, good_calls = 0;

	for(int i = 0;  i < 666; i+= 5) // 666 - the scans, 5 the steps
	{
		double currentAngle = Lasertord(i);
		double releventAngle = currentAngle + ext_loc.getYaw();

		if (_lp->GetRange(i) > 0.75) // 75 cm - laser min range / 100
		{
			/*for (double j = 0; j <= _lp->GetRange(i); j += (1/mp.getCell2Cm()) ) ///TODO:ori - map?
			{
				double currX = ext_loc.getX() + (j * 100 *  cos(releventAngle));
				double currY = ext_loc.getY() + (j * 100 *  sin(releventAngle));

				if (mp.getCellAtRealLocation(currX / 100.0f,currY / 100.0f) == 0)
					good_calls ++;
				else
					bad_calls ++;

			}*/
		}
		else
		{
			double currX = ext_loc.getX() + cos(releventAngle);
			double currY = ext_loc.getY() + sin(releventAngle);

			/*if (mp.getCellAtRealLocation(currX / 100.0f,currY / 100.0f) == 1) TODO:ori - map?
				good_calls ++;
			else
				bad_calls ++;*/
		}
	}

	return ((double) good_calls) / (good_calls + bad_calls);
}

double Particle::Lasertord(int i)
{
	double angle = 240/666;
	double deg_angle = i*angle - (240/2);

	return (deg_angle * (M_PI / 180));
}

bool Particle::isInRange(double value, double min, double max)
{
	if (value < min)
	{
		return false;
	}
	else if (value > max)
	{
		return true;
	}
	else
	{
		return true;
	}
}

vector<Particle> Particle::ChildParticles()
{
	vector<Particle> children;

	for(unsigned i = 0; i < 20; i++) // 20- num of children's
	{
		int rand_x = rand() % 15 - 15; //random between -15 to 15
		int rand_y = rand() % 15 - 15; //random between -15 to 15
		float rand_yaw = rand() % 15  + (ext_loc.getYaw() * 180.0 / M_PI) - 1; // Random
		rand_yaw = fmod(rand_yaw, 360.0);
	    rand_yaw *= M_PI / 180.0;

		children.push_back(Particle(rand_x + ext_loc.getX(), rand_y + ext_loc.getY(), rand_yaw, belief));
	}

	return children;
}

void Particle::setBelief(float belief)
{
	this->belief = belief;
}

