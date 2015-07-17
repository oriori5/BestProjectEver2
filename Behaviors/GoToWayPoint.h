/*
 * GoToWayPoint.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef GOTOWAYPOINT_H_
#define GOTOWAYPOINT_H_

#include "Behavior.h"
#include "../WayPointManager.h"

class GoToWayPoint : public Behavior
{
private:
	bool isWaypointSet;
	WayPointManager* wpManager;
public:
	GoToWayPoint(Robot* robot);
	virtual ~GoToWayPoint() {};
	bool startCond();
	bool stopCond();
	void action();
	void setWaypointManager(WayPointManager* wp);
};

#endif /* GOTOWAYPOINT_H_ */
