/*
 * PlanGoToTarget.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef PLANGOTOTARGET_H_
#define PLANGOTOTARGET_H_

#include "Plan.h"
#include "../WayPointManager.h"
#include "../Behaviors/GoForward.h"
#include "../Behaviors/GoToWayPoint.h"
#include "../Behaviors/GoRotate.h"
#include "../Behaviors/GoObstacle.h"

class PlanGoToTarget: public Plan
{
	Behavior* _beh[4];

public:
	PlanGoToTarget(Robot* robot);
	PlanGoToTarget(Robot* robot, WayPointManager* wpManager);
	Behavior* getStartPoint();
	virtual ~PlanGoToTarget();
};

#endif /* PLANGOTOTARGET_H_ */
