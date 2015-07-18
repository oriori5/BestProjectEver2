/*
 * AStarSearcher.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef ASTARSEARCHER_H_
#define ASTARSEARCHER_H_

#include <tr1/unordered_map>
#include <vector>
#include <queue>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* abs */
#include "../Map/Map.h"
#include "MapHolderAStar.h"
#include "../Utils/Location.h"
#include "../Utils/IntMatrix.h"
#include "../Utils/LocationMatrix.h"
#include "../Utils/PriorityQueue.h"

using namespace std;
using namespace tr1;

class AStarSearcher
{
public:
	AStarSearcher();

	/*
	 * Run the A-Star algorithm
	 */
	static void aStarSearch(MapHolderAStar mapGraph, Location start, Location target,
							LocationMatrix& parentsMap, IntMatrix& costMap);

	/*
	 * The heuristic method for the A-Star algorithm
	 */
	static int heuristic(Location source, Location dest);
};

#endif /* ASTARSEARCHER_H_ */
