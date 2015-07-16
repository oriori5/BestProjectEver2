/*
 * PlnObstacleAvoid.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "PlnObstacleAvoid.h"

PlnObstacleAvoid::PlnObstacleAvoid(Robot* robot) : Plan(robot)
{
	/*//Creating Behaviors
	_beh[0] = new A(robot);
	_beh[1] = new B(robot);
	_beh[2] = new C(robot);

	//Connecting Behaviors
	_beh[0]->addBeh(_beh[1]);
	_beh[0]->addBeh(_beh[2]);
	_beh[1]->addBeh(_beh[2]);
	_beh[2]->addBeh(_beh[0]);
	_start = _beh[0];*/
}

PlnObstacleAvoid::~PlnObstacleAvoid()
{
	// TODO Auto-generated destructor stub
	for(int i=0;i<3;i++)
		delete _beh[i];
}
