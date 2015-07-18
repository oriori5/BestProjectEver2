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

vector<Location> PathFinder::findPath(Location source, Location destination)
{
	// Creating a graph object
	MapHolderAStar graphObject(_map);

	// Run the A-Star algorithm to find a path
	_searcher.aStarSearch(graphObject, source, destination, _parentsMap, _costsMap);

	// Get the path from the parents map
	_resultPath = getPathFromParentMap(source, destination);

	/*
	 * This code is for the bonus!
	 * Printing the robot path to a PNG file.
	 */

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

vector<Location> PathFinder::getPathFromParentMap(Location from, Location to)
{
	vector<Location> pathResult;

	// Starts from the target location (and then going to the start location)
	Location current = to;

	pathResult.insert(pathResult.begin(),current);

	// If we didn't get the start locaton, continue saving the path
	while ((current.getX() != from.getX()) || (current.getY() != from.getY()))
	{
		// Adding the current location to the path result
		current = _parentsMap._matrix[current.getY()][current.getX()];
		pathResult.insert(pathResult.begin(),current);
	}

	// Return the full path
	return (pathResult);
}

PathFinder::~PathFinder()
{
}
