/*
 * GoRotate.cpp
 *
 *  Created on: Jul 17, 2015
 *      Author: colman
 */

#include "GoRotate.h"
#include <math.h>

GoRotate::GoRotate(Robot* robot) : Behavior(robot)
{
	// TODO Auto-generated constructor stub
	direction_decided = false;
    passed_correct_angle = false;
    is_dir_right = false;
}

bool GoRotate::startCond()
{
	direction_unit_vector = (_robot->getTargetLocation() - _robot->getCurrentLocation());
	rad_angle = atan2(direction_unit_vector.getY(), direction_unit_vector.getX());

	direction_decided = false;
    passed_correct_angle = false;
	is_dir_right = false;

	cout << "Started Action_Rotate" << endl;
	cout << "Rotating towards target : " << _robot->getTargetLocation().getX() << ", " << _robot->getTargetLocation().getY() << endl;
	cout << "My current Location is : " << _robot->getCurrentLocation().getX() << ", " << _robot->getCurrentLocation().getY() << endl;
	return true;
}

bool GoRotate::stopCond()
{
	//.Normalize();


	cout << "rad_angle : " << rad_angle << "robot_angle : " << _robot->getYaw() << endl;
	cout << "fabs value : " << fabs(rad_angle - _robot->getYaw()) << endl;

	if ((fabs(rad_angle - _robot->getYaw()) <= 2.0 * M_PI / 180.0) ||
	    (passed_correct_angle && (fabs(rad_angle - _robot->getYaw()) <= 5.0 * M_PI / 180.0))) // it is less than 3 degree diffrence.
	{
		_robot->setSpeed(0.0f,0.0f); // stop moving for now.
		return true;
	}

	return false;
}

void GoRotate::action()
{
	//Location direction_unit_vector = (_robot->getTargetLocation() - _robot->getCurrentLocation());//.Normalize();
	//double rad_angle = atan2(direction_unit_vector.getY(), direction_unit_vector.getX());
    /*if (rad_angle < 0)
    {
    	rad_angle += (2 * M_PI);
    }*/

    double curr_angle = _robot->getYaw();
    curr_angle = curr_angle > 0? curr_angle : 2.0 * M_PI + curr_angle;

    if ((curr_angle > rad_angle &&  curr_angle - rad_angle < M_PI) ||
    		(curr_angle < rad_angle &&  rad_angle - curr_angle  > M_PI))
    {
    	_robot->setSpeed(0.0f, -0.15f);

    	if (!direction_decided)
    	{
    	   direction_decided = true;
    	   is_dir_right = true;
    	}
    	else
    	{

    	   // we started rotating left and now we want to rotate right -> DONT DO THAT. DRIVE!
           if (!is_dir_right)
           {
        	   passed_correct_angle = true;
           }
    	}
    }
    else
    {
    	_robot->setSpeed(0.0f, 0.15f);
    	if (!direction_decided)
    	{
    		direction_decided = true;
    	   is_dir_right = false;
    	}
    	else
    	{
    		// we started rotating right and now we want to rotate left -> DONT DO THAT. DRIVE!
    		if (is_dir_right)
    		{
    		    passed_correct_angle = true;
    		}
    	}
    }

    /*
	// rotate slowly to target angle
	if (_robot->getYaw() > rad_angle)
	{
	    _robot->setSpeed(0.0f, -0.15f);
	}
	else
	{
		_robot->setSpeed(0.0f, 0.15f);
	}
	*/
}

