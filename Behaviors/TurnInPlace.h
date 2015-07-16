/*
 * TurnInPlace.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef TURNINPLACE_H_
#define TURNINPLACE_H_

#include "Behavior.h"
#include "../Plans/Resources.h"

class TurnInPlace: public Behavior {
public:
	TurnInPlace(Robot* robot);
	bool startCond();
	bool stopCond();
	ActionResult action();
	virtual ~TurnInPlace();
};

#endif /* TURNINPLACE_H_ */
