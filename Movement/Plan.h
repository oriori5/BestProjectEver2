/*
 * Plan.h
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#ifndef PLAN_H_
#define PLAN_H_
#include "Behavior.h"
#include "../Robot/Robot.h"
class Plan {

protected:
	Behavior* _behaviorToBeginWith;
public:
	Plan(Robot* robot);
	virtual Behavior* getBehvaiorToBeginWith()
	{
		return _behaviorToBeginWith;
	}

	virtual ~Plan();
};

#endif /* PLAN_H_ */
