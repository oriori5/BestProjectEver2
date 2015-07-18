/*
 * Robot.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>
#include "../Localization/Localization.h"
#include "../Map/Map.h"

using namespace PlayerCc;

class Robot
{
	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
	Localization* _lc;
	Map _map;
	bool get_call;
	bool get_call_left;
	Location _target;


public:
	Robot(char* ip, int port, Map _map);
	void read();
	void setSpeed(float speed, float angularSpeed);
	void setSpeed(double xSpeed, double ySpeed, double yaw);
	double getLaserDistance(int index);
	bool isObstacle(bool* blocked_right);
	bool isRightSideClear();
	bool isLeftSideClear();
	bool isClosetToLocation(Location location);
	void setTargetLocation(Location target);
	Location getTargetLocation();
	double GetCurentYaw();
	double getXPos();
	double getYPos();
	Location getCurrentLocation();
	float getYaw();
	void Update();


	virtual ~Robot();
};


#endif /* ROBOT_H_ */
