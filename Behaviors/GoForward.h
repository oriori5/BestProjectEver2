/*
 * GoForward.h

 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */
#ifndef GOFORWARD_H_
#define GOFORWARD_H_

#include "Behavior.h"
#include "../Robot.h"
#include "../Plans/Resources.h"
#include "../Utils/Location.h"

class GoForward: public Behavior
{
public:
	GoForward(Robot* robot);
	bool startCond();
	bool stopCond();
	void action();
	virtual ~GoForward();
};

#endif /* GOFORWARD_H_ */
