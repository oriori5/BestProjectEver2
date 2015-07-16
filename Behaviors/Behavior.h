/*
 * Behavior.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */
#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_
#include "../Robot.h"
//#include "../Helpers/MappingHelper.h"

#include "ActionResult.h"
//#include "../Helpers/MovmentHelper.h"

class Behavior
{
	Behavior** _next;
	int _arrSize;
protected:
	Robot* _robot;
	public:	Behavior(Robot* robot);
	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual ActionResult action() = 0;
	Behavior* addNext(Behavior* behavior);
	Behavior* selectNext();
	bool isFree(int startIndex, int endIndex, double distance);
	virtual ~Behavior();

};

#endif /* BEHAVIOR_H_ */

