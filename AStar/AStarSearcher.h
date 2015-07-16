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
#include "../Map.h"
#include "MapHolderAStar.h"
#include "../Utils/Location.h"
#include "../IntMatrix.h"
#include "../LocationMatrix.h"
#include "../Utils/PriorityQueue.h"

using namespace std;
using namespace tr1;


class AStarSearcher
{
public:
	AStarSearcher();

	//***********
	//	Search methods
	//***********
	static void aStarSearch(MapHolderAStar mapGraph,
			Location start, Location target,
			LocationMatrix& parentsMap,
			IntMatrix& costMap);

	//***********
	//	Algotihm's logic methods
	//***********
	static int heuristic(Location from, Location to);
};

#endif /* ASTARSEARCHER_H_ */
