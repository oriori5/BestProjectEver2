/*
 * Particle.cpp
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#include "Particle.h"

/**
* Ctor!
**/
Particle::Particle(float x, float y, float yaw, float belife)
{
	_extendedLocation.SetLocation(x, y);
	_extendedLocation.setYaw(yaw);
	setBelief(belife);
}

/**
* Dtor!
**/
Particle::~Particle()
{
}

/**
* Update Particle
**/
void Particle::Update(int x, int y, float yaw, LaserProxy* _lp, Map& mp)
{
	_extendedLocation.SetLocation((_extendedLocation.GetLocation().getX() + x), (_extendedLocation.GetLocation().getY() + y));
	_extendedLocation.setYaw(fmod((_extendedLocation.getYaw() + yaw), M_PI*2));
	_belief *= calcMove(x, y, yaw)* calcScan(_lp, mp) * 1.05;
}

/**
* Calculation by movement
**/
double Particle::calcMove(int x, int y, float yaw)
{	//
	return 1.0;
}

/**
* Calculation particals by Scanning the laser
**/
double Particle::calcScan(LaserProxy* _lp, Map& mp)
{
	unsigned calls = 0;
	unsigned not_calls = 0;

	// 666 - Laser Reading
	// 5 - Steps.
	for(int i = 0;  i < 666; i += 5) // 666 - the scans, 5 the steps
	{
		// Get angle in radians.
		double currentAngle = Lasertord(i);

		// Calc the angle with the yaw.
		double releventAngle = currentAngle + _extendedLocation.getYaw();

		// If the laser is in minimum range (75).
		if (_lp->GetRange(i) > 0.75)
		{
			// All over the range...
			for (double j = 0; j <= _lp->GetRange(i); j += (1 / Map::map_resolution_in_cm) )
			{
				// Calc the x and y.
				double currX = _extendedLocation.getX() + (j * 100 *  cos(releventAngle));
				double currY = _extendedLocation.getY() + (j * 100 *  sin(releventAngle));

				// If the x and y is negative.
				if (currX < 0)
				{
					currX = -currX;
				}

				if (currY < 0)
				{
					currY = -currY;
				}

				// If the real location is x,y and the map cell is free.
				if (mp.GetMapCellByRealLocation(currX / 100.0f,currY / 100.0f) == 0)
				{
					calls++;
				}
				else
				{
					not_calls++;
				}
			}
		}
		else
		{
			// Calc the x and y.
			double currX = _extendedLocation.getX() + cos(releventAngle);
			double currY = _extendedLocation.getY() + sin(releventAngle);

			// If the real location is x,y and if the map is occupied (1/2 is occupied).
			if (mp.GetMapCellByRealLocation(currX / 100.0f,currY / 100.0f) == 1 ||
				mp.GetMapCellByRealLocation(currX / 100.0f,currY / 100.0f) == 2)
			{
				calls++;
			}
			else
			{
				not_calls++;
			}
		}
	}

	return ((double) calls) / (calls + not_calls);
}

// Convert laser to radiant.
double Particle::Lasertord(int i)
{
	// 666 - laser scanning.
	double angle = 240/666;
	double deg_angle = i*angle - (240/2);

	return (deg_angle * (M_PI / 180));
}

// Utils function, is in range.
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

// Create child.
vector<Particle> Particle::ChildParticles()
{
	vector<Particle> children;

	// For all the 20 child's
	for(unsigned i = 0; i < 20; i++)
	{
		// Set random number between 15.
		int rand_x = rand() % 15 - 15;
		int rand_y = rand() % 15 - 15;
		float rand_yaw = rand() % 15  + (_extendedLocation.getYaw() * 180.0 / M_PI) - 1;
		rand_yaw = fmod(rand_yaw, 360.0);
	    rand_yaw *= M_PI / 180.0;

	    // Push the child.
		children.push_back(Particle(rand_x + _extendedLocation.getX(), rand_y + _extendedLocation.getY(), rand_yaw, _belief));
	}

	return children;
}

// Set Belief
void Particle::setBelief(float belief)
{
	this->_belief = belief;
}

// Get Belief
float Particle::getBelief()
{
	return this->_belief;
}

// Get ExtendedLocation
ExtendedLocation Particle::GetExtendedLocation()
{
	return this->_extendedLocation;
}
