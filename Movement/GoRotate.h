/*
 * GoRotate.h
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#ifndef GOROTATE_H_
#define GOROTATE_H_

#include "Behavior.h"

class GoRotate : public Behavior
{
private:
	double desired_angle;
public:
	GoRotate(Robot* robot);
	virtual ~GoRotate() {};
	bool startCond();
	bool stopCond();
	void action();
};

#endif /* GOROTATE_H_ */
