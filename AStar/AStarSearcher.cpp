/*
 * AStarSearcher.cpp
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#include "AStarSearcher.h"

AStarSearcher::AStarSearcher()
{
}

void AStarSearcher::aStarSearch(MapHolderAStar mapGraph, Location start, Location target,
								LocationMatrix& parentsMap, IntMatrix& costMap)
{
	// Define the sizes of the matrices
	parentsMap.DefineSize(mapGraph._mapObj._map._height, mapGraph._mapObj._map._width);
	costMap.DefineSize(mapGraph._mapObj._map._height, mapGraph._mapObj._map._width);
	costMap._defaultValue = 0;

	PriorityQueue frontier;

	// initialize the start node
	frontier.put(start, 0);
	parentsMap._matrix[start.getY()][start.getX()] = start;
	costMap._matrix[start.getY()][start.getX()] = 0;

	// Perform the search
	while (!frontier.empty())
	{
		Location current = frontier.get();
		vector<Location> neighbors = mapGraph.getNeighborsOfLocation(current);

		// Run over all the neighbors of the current location
		for (int i = 0; i < neighbors.size(); i++)
		{
			Location next = neighbors[i];

			// Calculating the new cost of the path to the current neighbor
			int newCost = costMap._matrix[current.getY()][current.getX()] + mapGraph.getCostOfPath(current,next);

			// Checking if we didn't visit yet in the next node or the new cost is lower than the existing
			// cost of the next node
			if ((costMap.isPositionDefault(next)) || (newCost < costMap._matrix[next.getY()][next.getX()]))
			{
				costMap._matrix[next.getY()][next.getX()] = newCost;

				// Get the new priority of the node
				int priority = newCost + AStarSearcher::heuristic(next, target);

				frontier.put(next, priority);
				parentsMap._matrix[next.getY()][next.getX()] = current;
			}
		}
	}

	// Checking if we didn't reach the target
	if (parentsMap.isPositionDefault(target))
	{
		cout << "Target wasn't reached :(" << endl;
	}
}

int AStarSearcher::heuristic(Location source, Location dest)
{
	// Return the heuristic calculate for the algorithm
	return (abs(source.getX() - dest.getX()) + abs(source.getY() - dest.getY()));
}
