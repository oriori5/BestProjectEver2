/*
 * TurnRight.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef TURNRIGHT_H_
#define TURNRIGHT_H_

#include "Behavior.h"
#include "../Plans/Resources.h"

class TurnRight: public Behavior {
public:
	TurnRight(Robot* robot);
	bool startCond();
	bool stopCond();
	void action();
	virtual ~TurnRight();
};

#endif /* TURNRIGHT_H_ */
