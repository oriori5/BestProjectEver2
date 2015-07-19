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
#include "../Managers/WayPointManager.h"

using namespace PlayerCc;

class Robot
{
	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
	Localization* _lc;
	Map _map;
	bool isStillBlocked;
	bool shouldTurnleft;
	Location _target;

public:
	Robot(char* ip, int port, Map _map);
	void read();
	void setSpeed(float speed, float angularSpeed);
	double getLaserDistance(int index);
	bool isObstacle(bool* blocked_right);
	bool isRightSideFree();
	bool isLeftSideFree();
	bool isCloseToLocation(Location location);
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
