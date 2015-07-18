/*
 * LocationMatrix.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "LocationMatrix.h"

LocationMatrix::LocationMatrix() {
	// TODO Auto-generated constructor stub

}

LocationMatrix::~LocationMatrix() {
	// TODO Auto-generated destructor stub
}

bool LocationMatrix::isPositionValid(unsigned x, unsigned y)
{
	return ((x > 0) && (x < _width)) &&
			((y > 0) && (y < _height));
}

bool LocationMatrix::isPositionDefault(Location pos)
{
	return (_matrix[pos.getY()][pos.getX()].getX() == _defaultValue.getX() &&
			_matrix[pos.getY()][pos.getX()].getY() == _defaultValue.getY());
}

