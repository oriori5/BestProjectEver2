/*
 * Robot.h
 *
 *  Created on: Dec 14, 2014
 *      Author: user
 */

#ifndef ROBOT_H_
#define ROBOT_H_
#include <libplayerc++/playerc++.h>


using namespace PlayerCc;

class Robot
{
	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
public:
	Robot(char* ip, int port);
	void read();
	void setSpeed(float speed, float angularSpeed);
	void setSpeed(double xSpeed, double ySpeed, double yaw);
	double getLaserDistance(int index);
	double GetCurentYaw();
	double getXPos();
	double getYPos();
	virtual ~Robot();
};


#endif /* ROBOT_H_ */
