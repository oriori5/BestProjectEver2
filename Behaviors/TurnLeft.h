/*
 * TurnLeft.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef TURNLEFT_H_
#define TURNLEFT_H_

#include "Behavior.h"
#include "../Plans/Resources.h"

class TurnLeft: public Behavior {
public:
	TurnLeft(Robot* robot);
	bool startCond();
	bool stopCond();
	ActionResult action();
	virtual ~TurnLeft();
};

#endif /* TURNLEFT_H_ */
