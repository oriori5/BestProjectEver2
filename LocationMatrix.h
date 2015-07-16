/*
 * LocationMatrix.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef LOCATIONMATRIX_H_
#define LOCATIONMATRIX_H_

#include "Utils/Location.h"

class LocationMatrix
{
public:
	int _height;
	int _width;
	Location** _matrix;
	Location _defaultValue;

	LocationMatrix();
	virtual ~LocationMatrix();

	void DefineSize(int height, int width)
	{
		_height = height;
		_width = width;

		// Initialize the matrix
		_matrix = new Location*[_height];
		for (int row = 0; row < height; row++)
		{
			_matrix[row] = new Location[width];
		}
	};

	bool isPositionValid(unsigned x, unsigned y);
	bool isPositionDefault(Location pos);
};

#endif /* LOCATIONMATRIX_H_ */
