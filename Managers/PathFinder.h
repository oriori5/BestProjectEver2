
#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include <limits>
#include "../Utils/IntMatrix.h"
#include "../Utils/LocationMatrix.h"
#include "../AStar/AStarSearcher.h"
#include "../AStar/MapHolderAStar.h"

using namespace std;

class PathFinder
{
private:
	Map _map;
	vector<Location> _resultPath;
	AStarSearcher _searcher;
	LocationMatrix _parentsMap;
	IntMatrix _costsMap;

public:
	// Ctor and Dtor
	PathFinder(Map map);
	virtual ~PathFinder();

	/*
	 * Find the path from source to destination (using A-Star algorithm)
	 */
	vector<Location> findPath(Location source, Location destination);

private:
	/*
	 * Get the full path from the parents map (that we got from the A-Star algorithm)
	 */
	vector<Location> getPathFromParentMap(Location from, Location to);
};

#endif /* PATHFINDER_H_ */
