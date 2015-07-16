/*
 * ActionResult.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */


#include "ActionResult.h"

ActionResult::ActionResult()
{

}

ActionResult::ActionResult(float monment, float yaw)
{
	_monment = monment;
	_yawResult = yaw;
}

float ActionResult::GetMovment()
{
	return _monment;
}

float ActionResult::GetYaw()
{
	return _yawResult;
}

ActionResult::~ActionResult()
{

}
