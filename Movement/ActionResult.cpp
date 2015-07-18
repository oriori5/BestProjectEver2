/*
 * ActionResult.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */


#include "ActionResult.h"

//Empty Ctor
ActionResult::ActionResult()
{

}

// Full Ctor
ActionResult::ActionResult(float monment, float yaw)
{
	_monment = monment;
	_yawResult = yaw;
}

// Get Movement
float ActionResult::GetMovment()
{
	return _monment;
}

// Get Yaw
float ActionResult::GetYaw()
{
	return _yawResult;
}

// Dtor
ActionResult::~ActionResult()
{

}
