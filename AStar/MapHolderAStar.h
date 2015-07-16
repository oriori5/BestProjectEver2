/*
 * MapHolderAStar.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef MAPHOLDERASTAR_H_
#define MAPHOLDERASTAR_H_

#include "../Utils/Location.h"
#include "../Map.h"
#include "../IntMatrix.h"
#include <vector>

using namespace std;

class MapHolderAStar
{
public:
	Map _mapObj;
	IntMatrix _costs;

public:
	MapHolderAStar(Map mapObj)
	{
		_mapObj = mapObj;
		_costs.DefineSize(mapObj._map._height, mapObj._map._width);

		// Initialize all the costs matrix to the default (0)
		for (int row = 0; row < mapObj._map._height; ++row)
		{
			for (int col = 0; col < mapObj._map._width; ++col)
			{
				_costs._matrix[row][col] = 0;
			}
		}

		// Setting very high cost (500) to the layer of 5 pixels near to each blown cell
		for (int row = 0; row < mapObj._map._height; ++row)
		{
			for (int col = 0; col < mapObj._map._width; ++col)
			{
				if (mapObj._map._matrix[row][col] == 2)
				{
					Map::BlowCell(_costs._matrix, mapObj._map._height, mapObj._map._width, row, col, 5, 500);
				}
			}
		}

		// Setting high cost (100) to the layer of 3 pixels from the previous layer (5 pixels of cost 500)
		for (int row = 0; row < mapObj._map._height; ++row)
		{
			for (int col = 0; col < mapObj._map._width; ++col)
			{
				if (_costs._matrix[row][col] == 500)
				{
					Map::BlowCell(_costs._matrix, mapObj._map._height, mapObj._map._width, row, col, 3, 100);
				}
			}
		}

		// Setting cost 1 for all the other cells (normal free cells)
		for (int row = 0; row < mapObj._map._height; ++row)
		{
			for (int col = 0; col < mapObj._map._width; ++col)
			{
				if (_costs._matrix[row][col] == 0)
				{
					_costs._matrix[row][col] = 1;
				}
			}
		}
	}

	MapHolderAStar();
	virtual ~MapHolderAStar();
	vector<Location> neighbors(Location center);
	unsigned cost(Location from, Location to);
};

#endif /* MAPHOLDERASTAR_H_ */
