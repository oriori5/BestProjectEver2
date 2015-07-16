/*
 * Particle.h
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <vector>
#include "../Robot.h"
#include "../Utils/ExtendedLocation.h"
#include "../Map.h"

using namespace std;

class Particle
{
private:

	float belief;

public:
	ExtendedLocation ext_loc;
	vector<Particle> ChildParticles();
	Particle(float x, float y, float yaw, float belife);
	ExtendedLocation GetExtented();
	float getBelief();
	void setBelief(float belief);
	void Update(int x, int y, float yaw, LaserProxy* _lp, Map& mp);
	double calcMove(int x, int y, float yaw);
	double calcScan( LaserProxy* _lp, Map& mp);
	ExtendedLocation GetExtendedLocation();
	void SetExtendedLocation(ExtendedLocation ext);
	double Lasertord(int i);
	bool isInRange(double value, double min, double max);
	virtual ~Particle();
};

#endif /* PARTICLE_H_ */
