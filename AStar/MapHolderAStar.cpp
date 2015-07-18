/*
 * MapHolderAStar.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#include "MapHolderAStar.h"

MapHolderAStar::MapHolderAStar(Map mapObj)
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

MapHolderAStar::~MapHolderAStar()
{
}

vector<Location> MapHolderAStar::getNeighborsOfLocation(Location location)
{
	vector<Location> neighborsList;

	// Running over all the directions which the neighbors could be in
	for (int direction = Up; direction <= Up_Left; direction++)
	{
		// Get the current currentNeighbor
		Location currentNeighbor = location.getRelativePosition((Directions)direction);

		// Checking if the current neighbor is valid (in the map borders and free cell)
		if ((_mapObj._map.isPositionValid(currentNeighbor.getX(), currentNeighbor.getY())) &&
			(_mapObj._map._matrix[currentNeighbor.getY()][currentNeighbor.getX()] == 0))
		{
			// Add it to the list
			neighborsList.push_back(currentNeighbor);
		}
	}

	// Return the valid neighbors list
	return (neighborsList);
}

unsigned MapHolderAStar::getCostOfPath(Location source, Location dest)
{
	// Get the max cost between the locations
	return max(_costs._matrix[source.getY()][source.getX()], _costs._matrix[dest.getY()][dest.getX()]);
}

