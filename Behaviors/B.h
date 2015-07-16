/*
 * B.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef B_H_
#define B_H_

#include "Behavior.h"
#include "../Robot.h"

class B : public Behavior
{
public:
	B(Robot* robot) : Behavior(robot) {};
	virtual ~B();
	virtual bool startCond() { return false; };
	virtual bool stopCond() { return false; };
	virtual ActionResult action() {};
};

#endif /* B_H_ */
