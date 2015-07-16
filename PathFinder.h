
#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include <limits>
#include "IntMatrix.h"
#include "LocationMatrix.h"
#include "AStar/AStarSearcher.h"
#include "AStar/MapHolderAStar.h"

using namespace std;

class PathFinder
{
private:
	Map _map;
	vector<Location> _resultPath;
	vector<Location> _locationsMatrix;
	AStarSearcher _searcher;
	LocationMatrix _parentsMap;
	IntMatrix _costsMap;

public:
	//************
	//	Ctor and initialization
	//************
	PathFinder(Map map);

	//************
	//	Accessors
	//************
	vector<Location> getChosenPath()
	{
		return _locationsMatrix;
	}


	//************
	//	Navigation methods
	//************
	/**
	 * Orders the class to find the path from source to destination and
	 * keep it.
	 */
	vector<Location> findPath(Location source, Location destination);

private :

	//***********
	//	Path finding helpers
	//***********
	vector<Location> pathFromParentMap(Location from, Location to)
	{
		vector<Location> path;

		// Starts from the end and go to the begining
		Location current = to;

		path.insert(path.begin(),current);

		while ((current.getX() != from.getX()) || (current.getY() != from.getY()))
		{
			current = _parentsMap._matrix[current.getY()][current.getX()];
			path.insert(path.begin(),current);
		}

		return path;
	}
};

#endif /* PATHFINDER_H_ */
