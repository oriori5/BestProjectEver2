/*
 * A.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef A_H_
#define A_H_

#include "Behavior.h"
#include "../Robot.h"

class A : public Behavior
{
public:
	A(Robot* robot) : Behavior(robot) {};
	virtual ~A();
	virtual bool startCond() { return false; };
	virtual bool stopCond() { return false; };
	virtual ActionResult action() {};
};

#endif /* A_H_ */
