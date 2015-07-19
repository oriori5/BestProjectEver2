/*
 * GoObstacle.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef GOOBSTACLE_H_
#define GOOBSTACLE_H_

#include "Behavior.h"
#include <ctime>

#define DRIVE_AWAY_TIME_SECONDS 2

class GoObstacle : public Behavior
{
private:
	bool obstacle_from_right;
	clock_t drive_away_start_time;
	bool can_we_keep_driving;
public:
	GoObstacle(Robot* robot);
	virtual ~GoObstacle() {};
	bool startCond();
	bool stopCond();
	void action();
};

#endif /* GOOBSTACLE_H_ */
