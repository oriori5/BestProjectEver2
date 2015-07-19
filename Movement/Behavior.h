/*
 * Behavior.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */
#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_

#include "../Robot/Robot.h"

class Behavior
{

vector<Behavior*> _behaviorVector;

protected:
	Robot* _robot;

public:
	Behavior();
	Behavior(Robot* robot);
	virtual ~Behavior();
	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual void action() = 0;
	bool isFree(int startIndex, int endIndex, double distance);
	void addNextBehavior(Behavior* next);
	Behavior* selectNext();
};

#endif /* BEHAVIOR_H_ */

