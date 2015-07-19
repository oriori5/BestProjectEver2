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
}

bool GoRotate::startCond()
{
	Location target_loc = _robot->getTargetLocation();
	Location current_loc = _robot->getCurrentLocation();

	// Distance between the robot and the desired target
	double distance = current_loc.Distance(target_loc);

	// Taking the y values delta for calculating the alpha by SINUS function
	double y_delta = fabs(target_loc.getY() - current_loc.getY());
	int x_target = target_loc.getX();
	int y_target = target_loc.getY();
	int x_robot = current_loc.getX();
	int y_robot = current_loc.getY();

	// The alpha angle (from the sinus calculate)
	double temp_angle = asin(y_delta / distance);

	/*
	 * Checking in which quarter the target is located relatively the robot and determine the desired angle
	 */

	if (x_target < x_robot && y_target < y_robot)
	{
		desired_angle = M_PI - temp_angle;
	}
	else if (x_target > x_robot && y_target < y_robot)
	{
		desired_angle = temp_angle;
	}
	else if (x_target > x_robot && y_target > y_robot)
	{
		desired_angle = (2 * M_PI) - temp_angle;
	}
	else if (x_target < x_robot && y_target > y_robot)
	{
		desired_angle = M_PI + temp_angle;
	}

	cout << "Started Action_Rotate" << endl;
	cout << "Rotating towards target : " << _robot->getTargetLocation().getX() << ", " << _robot->getTargetLocation().getY() << endl;
	cout << "My current Location is : " << _robot->getCurrentLocation().getX() << ", " << _robot->getCurrentLocation().getY() << endl;
	return true;
}

bool GoRotate::stopCond()
{
	cout << "current angle = " << _robot->getYaw() << ", target angle = " << desired_angle << endl;

	// Checking if the robot's angle is in the correct range and if it is true then stop rotating
	if (_robot->getYaw() >= desired_angle - 0.03 && _robot->getYaw() <= desired_angle + 0.03)
	{
		_robot->setSpeed(0.0, 0.0);
		cout << "stop rotated!" << endl;
		return true;
	}

	return false;
}

void GoRotate::action()
{
	/*
	 * determine the side that the robot will rotate.
	 * we decide it by comparing the angle of the robot and the target angle.
	 */

	if	(_robot -> getYaw()> 0 && desired_angle > 0 && desired_angle >_robot -> getYaw())
	{
		_robot->setSpeed(0.0f, 0.12f);
	}
	else if	(_robot -> getYaw()> 0 && desired_angle > 0 && desired_angle <_robot -> getYaw())
	{
		_robot->setSpeed(0.0f, -0.12f);
	}
	else if	(_robot -> getYaw()< 0 && desired_angle < 0 && desired_angle >_robot -> getYaw())
	{
		_robot->setSpeed(0.0f, 0.12f);
	}
	else if	(_robot -> getYaw()< 0 && desired_angle <0 && desired_angle <_robot -> getYaw())
	{
		_robot->setSpeed(0.0f, -0.12f);
	}
	else
	{
		double a = _robot->getYaw();
		double b = desired_angle;

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
				_robot->setSpeed(0.0f, -0.12f);
			}
			else
			{
				_robot->setSpeed(0.0f, 0.12f);
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
				_robot->setSpeed(0.0f, 0.12f);
			}
			else
			{
				_robot->setSpeed(0.0f, -0.12f);
			}
		}
	}
}

