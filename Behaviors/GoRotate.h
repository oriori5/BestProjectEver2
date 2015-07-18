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
	Location direction_unit_vector;
	double rad_angle;
	bool direction_decided;
	bool passed_correct_angle;
	bool is_dir_right;
	double right_angle;
public:
	GoRotate(Robot* robot);
	virtual ~GoRotate() {};
	bool startCond();
	bool stopCond();
	void action();
};

#endif /* GOROTATE_H_ */
