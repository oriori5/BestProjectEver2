/*
 * Map.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef MAP_H_
#define MAP_H_

#include "lodepng.h"
#include "pngUtil.h"
#include "../Utils/IntMatrix.h"
#include "../Utils/Consts.h"
#include "../Utils/Location.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Map
{
public:
	// Static variables to save the map and grid resolutions
	static double map_resolution_in_cm;
	static double grid_resolution_in_cm;

	IntMatrix _map;
	IntMatrix _grid;

public:
	// Ctor and Dtor
	Map();
	virtual ~Map();

	/*
	 * Reading a map from png file into int matrix
	 */
	static void ReadMapFromPngToMatrix(const char* filename, int**& map_matrix, int& rows, int& cols);

	/*
	 * Blowing the given cell with the given blow factor
	 */
	static void BlowCell(int**& map_matrix, int height, int width, int cell_row, int cell_col, int blow_factor, int blow_indication);

	/*
	 * Blowing the map with the given blow factor
	 */
	static void BlowMap(int**& map_matrix, int height, int width, int blow_factor);

	/*
	 * Converting the map to grid (using the map and grid resolutions)
	 */
	void ConvertMapToGrid();

	/*
	 * Getting the grid index by the given map index
	 */
	static int GetGridIndexByMapIndex(int map_index);

	/*
	 * Writing a map from matrix into png file
	 */
	static void WriteMapMatrixToPng(int**& map_matrix, int height, int width, const char* filename);

	/*
	 * Returning the map cell index by the given real location in cm
	 */
	static int LocationInCmToMapCell(float nLocation);

	/*
	 * Returning the map cell by the given real location in cm
	 */
	int GetMapCellByRealLocation(float x, float y);
};

#endif /* MAP_H_ */
