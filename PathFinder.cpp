/*
 * PathFinder.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "PathFinder.h"


PathFinder::PathFinder(Map map)
{
	this->_map = map;
	_costsMap.DefineSize(map._map._height, map._map._width);
}

//************
//	Navigation methods
//************
vector<Location>  PathFinder::findPath(Location source, Location destination)
{
	// a graph object
	MapHolderAStar graphObject(_map);

	// Apply A*
	_searcher.aStarSearch(graphObject, source, destination, _parentsMap, _costsMap);

	// Get path from parents map
	_resultPath = pathFromParentMap(source, destination);

	// Copy the original map
	IntMatrix mapWithPath;
	mapWithPath.DefineSize(_map._map._height, _map._map._width);
	for (int row = 0; row < _map._map._height; ++row)
	{
		for (int col = 0; col < _map._map._width; ++col)
		{
			mapWithPath._matrix[row][col] = _map._map._matrix[row][col];
		}
	}

	// Add the path to the map
	for (int i = 0; i < _resultPath.size(); i++)
	{
		Location location = _resultPath[i];
		mapWithPath._matrix[location.getY()][location.getX()] = 5;
	}

	// Save the map with the path to PNG file
	Map::WriteMapMatrixToPng(mapWithPath._matrix, mapWithPath._height, mapWithPath._width, "mapWithPath.png");

	// Return the path
	return (_resultPath);
}
