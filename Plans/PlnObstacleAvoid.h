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
#include "../Behaviors/A.h"
#include "../Behaviors/B.h"
#include "../Behaviors/C.h"

class PlnObstacleAvoid : public Plan
{
	Behavior* _beh[3];
	Behavior* _start;

public:
	PlnObstacleAvoid(Robot* robot);
	Behavior* getStartPoint(){return _start;}
	virtual ~PlnObstacleAvoid();
};

#endif /* PLNOBSTACLEAVOID_H_ */
