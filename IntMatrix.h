/*
 * Matrix.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef INT_MATRIX_H_
#define INT_MATRIX_H_

#include "Utils/Location.h"

class IntMatrix
{
public:
	int _height;
	int _width;
	int** _matrix;
	int _defaultValue;

	IntMatrix();
	virtual ~IntMatrix();

	void DefineSize(int height, int width)
	{
		_height = height;
		_width = width;

		// Initialize the matrix
		_matrix = new int*[_height];
		for (int row = 0; row < height; row++)
		{
			_matrix[row] = new int[width];
		}
	};

	bool isPositionValid(unsigned x, unsigned y);
	bool isPositionDefault(Location pos);
};

#endif /* INT_MATRIX_H_ */
