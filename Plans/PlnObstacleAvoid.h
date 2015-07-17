/*
 * PlnObstacleAvoid.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef PLNOBSTACLEAVOID_H_
#define PLNOBSTACLEAVOID_H_

#include "../Behaviors/Behavior.h"
#include "Plan.h"
#include "../WayPointManager.h"

class PlnObstacleAvoid : public Plan
{
	Behavior* _beh[4];

	public:
	PlnObstacleAvoid(Robot* robot);
	PlnObstacleAvoid(Robot* robot, WayPointManager* wpManager);
	Behavior* getStartPoint();
	virtual ~PlnObstacleAvoid();

#endif /* PLNOBSTACLEAVOID_H_ */
