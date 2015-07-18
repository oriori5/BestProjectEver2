/*
 * Matrix.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "IntMatrix.h"

IntMatrix::IntMatrix() {
	// TODO Auto-generated constructor stub

}

IntMatrix::~IntMatrix() {
	// TODO Auto-generated destructor stub
}

bool IntMatrix::isPositionValid(unsigned x, unsigned y)
{
	return ((x > 0) && (x < _width)) &&
			((y > 0) && (y < _height));
}

bool IntMatrix::isPositionDefault(Location pos)
{
	return (_matrix[pos.getY()][pos.getX()] == _defaultValue);
}

