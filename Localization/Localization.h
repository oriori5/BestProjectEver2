/*
 * Localization.h
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#ifndef LOCALIZATION_H_
#define LOCALIZATION_H_
#include <libplayerc++/playerc++.h>
#include "../Utils/ExtendedLocation.h"
#include "Particle.h"
#include "../Map/Map.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace PlayerCc;
using namespace std;

class Localization
{

private:
	Position2dProxy* pos_proxy;
	LaserProxy* laser_proxy;
	ExtendedLocation privious_location;
	ExtendedLocation current_location;
	vector<Particle> particles_vector;
	Map grid_map;

	void InitializeRandomParticles();
	static bool getBestParticle(Particle first_particle, Particle second_particle);
public:
	Localization();
	Localization(Position2dProxy &position2dProxy, LaserProxy* laserProxy, Map& map);
	ExtendedLocation getEstimatedLocation();
	void UpdateParticles();
	virtual ~Localization();
};

#endif /* LOCALIZATION_H_ */
