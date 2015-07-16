/*
 * C.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef C_H_
#define C_H_

#include "Behavior.h"
#include "../Robot.h"

class C : public Behavior
{
public:
	C(Robot* robot) : Behavior(robot) {};
	virtual ~C();
	virtual bool startCond() { return false; };
	virtual bool stopCond() { return false; };
	virtual ActionResult action() {};
};

#endif /* C_H_ */
