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
	static double map_resolution_in_cm;
	static double grid_resolution_in_cm;

	IntMatrix _map;
	IntMatrix _grid;

public:
	Map();
	virtual ~Map();
	static void ReadMapFromPngToMatrix(const char* filename, int**& map_matrix, int& rows, int& cols);
	static void BlowCell(int**& map_matrix, int height, int width, int cell_row, int cell_col, int blow_factor, int blow_indication);
	static void BlowMap(int**& map_matrix, int height, int width, int blow_factor);
	void ConvertMapToGrid();
	static int GetGridIndexByMapIndex(int map_index);
	static void WriteMapMatrixToPng(int**& map_matrix, int height, int width, const char* filename);
	static int LocationInCmToMapCell(float nLocation);
	int GetMapCellByRealLocation(float x, float y);
};

#endif /* MAP_H_ */
