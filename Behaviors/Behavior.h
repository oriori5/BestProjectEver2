/*
 * Behavior.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */
#ifndef BEHAVIOR_H_
#define BEHAVIOR_H_
#include "../Robot.h"
//#include "../Helpers/MappingHelper.h"

#include "ActionResult.h"
//#include "../Helpers/MovmentHelper.h"

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
	void addNextBehavior(Behavior* next)
	{
		_behaviorVector.push_back(next);
	}
	Behavior* selectNext()
	{
		//Run over vector and return first true
		//startCond of the first behavior
		for (int i=0; i < _behaviorVector.size(); i++)
		{
			if (_behaviorVector[i]->startCond())
			{
				return _behaviorVector[i];
			}
		}

		// aka still not out of behaviour,
		// because there is nothing else to choose.
		return this;
	};

/*	Behavior** _next;
	int _arrSize;
protected:
	Robot* _robot;
	public:	Behavior(Robot* robot);
	virtual bool startCond() = 0;
	virtual bool stopCond() = 0;
	virtual ActionResult action() = 0;
	Behavior* addNext(Behavior* behavior);
	Behavior* selectNext();

	virtual ~Behavior();
*/
};

#endif /* BEHAVIOR_H_ */

