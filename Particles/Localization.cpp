/*
 * Localization.cpp
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#include "Localization.h"

Localization::Localization()
{
	// TODO Auto-generated constructor stub

}

Localization::Localization(Position2dProxy &position2dProxy, LaserProxy* laserProxy, Map& map)
{
	pos_proxy = &position2dProxy;
	laser_proxy = laserProxy;
	grid_map = map;
	particles_vector = vector<Particle>();

	Location robot_location_in_meters(pos_proxy->GetXPos(),pos_proxy->GetYPos());
	privious_location.SetLocation(robot_location_in_meters.getX() * 100, robot_location_in_meters.getY() * 100);
	privious_location.setYaw(pos_proxy->GetYaw());
	InitializeRandomParticles();
}

bool Localization::getBestParticle(Particle first_particle, Particle second_particle)
{
	return first_particle.getBelief() > second_particle.getBelief();
}

ExtendedLocation Localization::getEstimatedLocation()
{
	if (particles_vector.empty())
	{
		current_location.SetLocation(0,0);
		cout << "Particles are empty" << endl;
		//throw "";
	}

		Particle best_particle = particles_vector.front();

		return best_particle.GetExtendedLocation();
}

void Localization::UpdateParticles()
{
	Location robot_location_in_meters(pos_proxy->GetXPos(),pos_proxy->GetYPos());

	double x = robot_location_in_meters.getX() * 100 - privious_location.getX();
	double y = robot_location_in_meters.getY() * 100 - privious_location.getY();
	double yaw = pos_proxy->GetYaw() - privious_location.getYaw();

	privious_location.SetLocation(robot_location_in_meters.getX() * 100, robot_location_in_meters.getY() * 100);
	privious_location.setYaw(pos_proxy->GetYaw());
	//cout << "oudometry location (" << meters_robot_loc.getX() << "," << meters_robot_loc.getY() << "," << last_location.getYaw() * 180.0 / M_PI << ")" << endl;

	vector<Particle> FuterParticalsVector = vector<Particle>();

	vector<Particle>::iterator particale = particles_vector.begin();
	while (particale != particles_vector.end())
	{
		// Update the particle
		particale->Update(x, y, yaw,laser_proxy,grid_map);

		// If not probable - delete
		//NORMAL_BELIEF = 0.7
		//MaxParticleAmount = 150
		//HIGH_BELIEF = 0.8
		if (particale->getBelief() < 0.7 && particles_vector.size() > 150 / 5)
		{
			particale = particles_vector.erase(particale);
		} else
		{
			// Is there room for more particles ?
			if (FuterParticalsVector.size() + particles_vector.size() < 150 && particale->getBelief() > 0.8)
			{
				vector<Particle> childParticles = particale->ChildParticles();
				FuterParticalsVector.insert(FuterParticalsVector.end(),childParticles.begin(),childParticles.end());
			}
			particale++;
		}
	}

	std::sort(FuterParticalsVector.begin(), FuterParticalsVector.end(), getBestParticle);

	vector<Particle>::iterator another_it = FuterParticalsVector.begin();
	unsigned available_space = 150 - particles_vector.size();

	for (unsigned i = 0; i < available_space && i < FuterParticalsVector.size(); i++)
	{
		particles_vector.push_back(*another_it);
		another_it ++;
	}

	sort(particles_vector.begin(), particles_vector.end(), getBestParticle);
}

void Localization::InitializeRandomParticles()
{
	//srand (time(NULL));
	unsigned particle_count = 0;

	cout << "About to generate particles around (" << privious_location.getX() << "," << privious_location.getY() << ")" << endl;

	while(particle_count < 150)
	{
		int rand_x = rand() % 10 + (privious_location.getX() - 1); // 0.25 meter radius
		int rand_y = rand() % 10 + (privious_location.getY() - 1); // 0.15 meter radius

		//float rand_yaw = rand() % 360 + 1;
		float rand_yaw = rand() % 10 + (privious_location.getYaw() * 180.0 / M_PI) - 1;
		rand_yaw = fmod(rand_yaw, 360.0);
		rand_yaw *= M_PI / 180.0;

		/*if (grid_map.getCellAtRealLocation(rand_x / 100.0f, rand_y / 100.0f) != 1) // TODO:ori - map?
		{
			Particle p =  Particle(rand_x, rand_y, rand_yaw, 1.0);
			particles_vector.push_back(p);
			particle_count++;
		}*/
	}
}

Localization::~Localization()
{
	// TODO Auto-generated destructor stub
}
