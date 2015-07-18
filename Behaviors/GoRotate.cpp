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
	Location target_loc = _robot->getTargetLocation();
	Location current_loc = _robot->getCurrentLocation();
	double distance = current_loc.Distance(target_loc);
	double y_delta = fabs(target_loc.getY() - current_loc.getY());
	int x_target = target_loc.getX();
	int y_target = target_loc.getY();
	int x_robot = current_loc.getX();
	int y_robot = current_loc.getY();

	double temp_angle = asin(y_delta / distance);

	if (x_target < x_robot && y_target < y_robot)
	{
		right_angle = M_PI - temp_angle;
	}
	else if (x_target > x_robot && y_target < y_robot)
	{
		right_angle = temp_angle;
	}
	else if (x_target > x_robot && y_target > y_robot)
	{
		right_angle = -temp_angle;
	}
	else if (x_target < x_robot && y_target > y_robot)
	{
		right_angle = -M_PI + temp_angle;
	}

	//direction_unit_vector = (_robot->getTargetLocation() - _robot->getCurrentLocation());
	//rad_angle = atan2(fabs(direction_unit_vector.getY()), fabs(direction_unit_vector.getX()));


	/*rad_angle = asin(fabs(direction_unit_vector.getY()) / distance);

	if (direction_unit_vector.getX() > 0)
	{
		right_angle = rad_angle + 0.1;
	}
	else
	{
		right_angle = M_PI - rad_angle + 0.1;
	}*/

	/*right_angle = - _robot->GetCurentYaw() - rad_angle + 0.2;
	if (right_angle < 0)
	{
		right_angle += M_PI;
	}*/

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

	cout << "current angle = " << _robot->GetCurentYaw() << ", target angle = " << right_angle << endl;
	if (_robot->GetCurentYaw() >= right_angle - 0.03 && _robot->GetCurentYaw() <= right_angle + 0.03)
	{
		_robot->setSpeed(0.0, 0.0);
		cout << "stop rotated!" << endl;
		return true;
	}

	//cout << "rad_angle : " << rad_angle << "robot_angle : " << _robot->GetCurentYaw() << endl;
	//cout << "fabs value : " << fabs(rad_angle - _robot->GetCurentYaw()) << endl;

	/*if ((fabs(rad_angle - _robot->GetCurentYaw()) <= 2.0 * M_PI / 180.0) ||
	    (passed_correct_angle && (fabs(rad_angle - _robot->GetCurentYaw()) <= 5.0 * M_PI / 180.0))) // it is less than 3 degree diffrence.
	{
		_robot->setSpeed(0.0f,0.0f); // stop moving for now.
		return true;
	}*/

	return false;
}

void GoRotate::action()
{
	if	(_robot -> GetCurentYaw()> 0 && right_angle > 0 && right_angle >_robot -> GetCurentYaw())
	{
		_robot->setSpeed(0.0f, 0.10f);
	}
	else if	(_robot -> GetCurentYaw()> 0 && right_angle > 0 && right_angle <_robot -> GetCurentYaw())
	{
		_robot->setSpeed(0.0f, -0.10f);
	}
	else if	(_robot -> GetCurentYaw()< 0 && right_angle < 0 && right_angle >_robot -> GetCurentYaw())
	{
		_robot->setSpeed(0.0f, 0.10f);
	}
	else if	(_robot -> GetCurentYaw()< 0 && right_angle <0 && right_angle <_robot -> GetCurentYaw())
	{
		_robot->setSpeed(0.0f, -0.10f);
	}
	else
	{
		double a = _robot->GetCurentYaw();
		double b = right_angle;

		double sum_for_right_dir;
		double sum_for_left_dir;

		if (a > 0 && b < 0)
		{
			double a_to_right_dir = a;
			double b_to_right_dir = fabs(b);
			double a_to_left_dir = M_PI - a;
			double b_to_left_dir = M_PI + b;

			sum_for_right_dir = a_to_right_dir + b_to_right_dir;
			sum_for_left_dir = a_to_left_dir + b_to_left_dir;

			if (sum_for_right_dir < sum_for_left_dir)
			{
				_robot->setSpeed(0.0f, -0.10f);
			}
			else
			{
				_robot->setSpeed(0.0f, 0.10f);
			}
		}
		else if (a < 0 && b > 0)
		{
			double a_to_right_dir = fabs(a);
			double b_to_right_dir = b;
			double a_to_left_dir = M_PI + a;
			double b_to_left_dir = M_PI - b;

			sum_for_right_dir = a_to_right_dir + b_to_right_dir;
			sum_for_left_dir = a_to_left_dir + b_to_left_dir;

			if (sum_for_right_dir < sum_for_left_dir)
			{
				_robot->setSpeed(0.0f, 0.10f);
			}
			else
			{
				_robot->setSpeed(0.0f, -0.10f);
			}
		}
	}





	//Location direction_unit_vector = (_robot->getTargetLocation() - _robot->getCurrentLocation());//.Normalize();
	//double rad_angle = atan2(direction_unit_vector.getY(), direction_unit_vector.getX());
    /*if (rad_angle < 0)
    {
    	rad_angle += (2 * M_PI);
    }*/

    /*double curr_angle = _robot->GetCurentYaw();
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
    }*/

    /*
	// rotate slowly to target angle
	if (_robot->GetCurentYaw() > rad_angle)
	{
	    _robot->setSpeed(0.0f, -0.15f);
	}
	else
	{
		_robot->setSpeed(0.0f, 0.15f);
	}
	*/
}

