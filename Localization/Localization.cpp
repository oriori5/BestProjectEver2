/*
 * Localization.cpp
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#include "Localization.h"

// Empty Ctor
Localization::Localization()
{
}

// Full Ctor
Localization::Localization(Position2dProxy &position2dProxy, LaserProxy* laserProxy, Map& map)
{
	// Init the variables.
	pos_proxy = &position2dProxy;
	laser_proxy = laserProxy;
	grid_map = map;
	particles_vector = vector<Particle>();

	// Set the robot location, privious location and the particles.
	Location robot_location_in_meters(pos_proxy->GetXPos(),pos_proxy->GetYPos());
	double loc_x = pos_proxy->GetXPos() * 100;
	double loc_y = pos_proxy->GetYPos() * 100;
	//double loc_x = ((pos_proxy->GetXPos() + 6.875) * 100);//simulator
	//double loc_y = (((pos_proxy->GetYPos() * -1) + 4.75) * 100);//simulator
	privious_location.SetLocation(loc_x, loc_y);
	privious_location.setYaw(pos_proxy->GetYaw());
	InitParticles();
}

bool Localization::getSuccessParticle(Particle part1, Particle part2)
{
	// Return the Best (first) Particle.
	return part1.getBelief() > part2.getBelief();
}

// Get Estimated Location
ExtendedLocation Localization::getPredictedLocation()
{
	// If there is particle
	if (particles_vector.empty())
	{
		// Set location for 0,0
		current_location.SetLocation(0,0);
		cout << "Particles are empty" << endl;
	}

	// Get location of the best particle.
	return (particles_vector.front().GetExtendedLocation());
}

// Update particles
void Localization::UpdateParticles()
{
	// Set Robot Location
	//Location robot_location_in_meters(pos_proxy->GetXPos(),pos_proxy->GetYPos());

	// Calculation the location
	int loc_x = pos_proxy->GetXPos() * 100;
	int loc_y = pos_proxy->GetYPos() * 100;
	//int loc_x = ((pos_proxy->GetXPos() + 6.875) * 100);//simulator
	//int loc_y = (((pos_proxy->GetYPos() * -1) + 4.75) * 100);//simulator

	// Calc the real location
	double x = loc_x - privious_location.getX();
	double y = -1 * (loc_y - privious_location.getY());
	double yaw = pos_proxy->GetYaw() - privious_location.getYaw();

	unsigned int particle_count = 0;

	// Set the privious location
	privious_location.SetLocation(loc_x, loc_y);
	privious_location.setYaw(pos_proxy->GetYaw());

	// Init the particle for the chiledrens
	vector<Particle> FuterParticalsVector = vector<Particle>();

	// All over the particles
	vector<Particle>::iterator particale = particles_vector.begin();
	while (particale != particles_vector.end() && particle_count < 100)
	{
		// Update the particle
		particale->Update(x, y, yaw,laser_proxy,grid_map);

		// If the particle is not good enough - delete it.
		// Good belief - 0.7, High belief - 0.8, Maximum Particle 150.
		if (particale->getBelief() < 0.7 && particles_vector.size() > 150 / 5)
		{
			// Erase
			particale = particles_vector.erase(particale);
		}
		else
		{
			// Check if we can add particles
			if (FuterParticalsVector.size() + particles_vector.size() < 150 && particale->getBelief() > 0.8)
			{
				vector<Particle> childParticles = particale->ChildParticles();
				FuterParticalsVector.insert(FuterParticalsVector.end(),childParticles.begin(),childParticles.end());
			}

			particale++;
			particle_count++;
		}
	}

	// Sort the particles
	std::sort(FuterParticalsVector.begin(), FuterParticalsVector.end(), getSuccessParticle);

	// Push back the particles
	vector<Particle>::iterator push_back_particles = FuterParticalsVector.begin();
	unsigned free_particles = 150 - particles_vector.size();

	for (unsigned i = 0; i < free_particles && i < FuterParticalsVector.size(); i++)
	{
		particles_vector.push_back(*push_back_particles);
		push_back_particles ++;
	}

	// Sort the particles again
	sort(particles_vector.begin(), particles_vector.end(), getSuccessParticle);
}

// Init Random Particles
void Localization::InitParticles()
{
	srand (time(NULL));
	unsigned particle_count = 0;

	cout << "Start to generate random particles (" << privious_location.getX() << "," << privious_location.getY() << ")" << endl;

	// Generate 100 Particles
	while(particle_count < 100)
	{

		int loc_x = privious_location.getX();
		int loc_y = privious_location.getY();

		int rand_x = rand() % 15 + (loc_x - 1);
		int rand_y = rand() % 15 + (loc_y - 1);

		if (rand_x < 0)
		{
			rand_x = -rand_x;
		}

		if(rand_y < 0)
		{
			rand_y = -rand_y;
		}

		float rand_yaw = rand() % 2 + (privious_location.getYaw() * 180.0 / M_PI) - 1;
		rand_yaw = fmod(rand_yaw, 360.0);
		rand_yaw *= M_PI / 180.0;

		if (grid_map.GetMapCellByRealLocation(rand_x, rand_y) != 1 && grid_map.GetMapCellByRealLocation(rand_x, rand_y) != 2)
		{
			cout << "created new particle with following data = (" << rand_x << "," << rand_y << "," << rand_yaw << ")" << endl;
			particles_vector.push_back(Particle(rand_x, rand_y, rand_yaw, 1.0));
			particle_count++;
		}
	}
	cout << "Finish to generate particles around! :) (" << privious_location.getX() << "," << privious_location.getY() << ")" << endl;
}

Localization::~Localization()
{
}
