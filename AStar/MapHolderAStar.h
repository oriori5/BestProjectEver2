/*
 * MapHolderAStar.h
 *
 *  Created on: Jun 26, 2015
 *      Author: colman
 */

#ifndef MAPHOLDERASTAR_H_
#define MAPHOLDERASTAR_H_

#include "../Utils/Location.h"
#include "../Map/Map.h"
#include "../Utils/IntMatrix.h"
#include <vector>

using namespace std;

class MapHolderAStar
{
public:
	Map _mapObj;
	IntMatrix _costs;

public:
	// Ctor and Dtor
	MapHolderAStar(Map mapObj);
	virtual ~MapHolderAStar();

	/*
	 * Get the neighbors of the given location (neighbors = all the cells around the given location)
	 */
	vector<Location> getNeighborsOfLocation(Location location);

	/*
	 * Get the cost of the path (by the given source and dest locations)
	 */
	unsigned getCostOfPath(Location source, Location dest);
};

#endif /* MAPHOLDERASTAR_H_ */
