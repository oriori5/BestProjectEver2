/*
 * Particle.h
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <vector>
#include <math.h>
#include "../Utils/ExtendedLocation.h"
#include "../Map/Map.h"
#include <libplayerc++/playerc++.h>

using namespace PlayerCc;
using namespace std;

class Particle
{
private:
	float _belief;
	ExtendedLocation _extendedLocation;

public:
	vector<Particle> ChildParticles();
	Particle(float x, float y, float yaw, float belife);
	float getBelief();
	void setBelief(float belief);
	void Update(int x, int y, float yaw, LaserProxy* laser_proxy, Map& mp);
	double calcMove(int x, int y, float yaw);
	double calcScan(LaserProxy* laser_proxy, Map& mp);
	ExtendedLocation GetExtendedLocation();
	void SetExtendedLocation(ExtendedLocation ext);
	double Lasertord(int i);
	bool isInRange(double value, double min, double max);
	virtual ~Particle();
};

#endif /* PARTICLE_H_ */
