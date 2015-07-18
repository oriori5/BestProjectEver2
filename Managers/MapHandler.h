/*
 * MapHandler.h
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#ifndef MAPHANDLER_H_
#define MAPHANDLER_H_

#include "../Map/Map.h"
#include "PathFinder.h"
#include "../Utils/Location.h"
#include "CofigurationManager.h"
#include <math.h>

using namespace std;

class MapHandler
{
public:
	// Ctor and Dtor
	MapHandler();
	virtual ~MapHandler();

	/*
	 * Running all the logic that needed for creating map from png, blow it, etc.
	 */
	Map RunMapProcessing(ConfigurationParametersStruct ParametersStruct);
};

#endif /* MAPHANDLER_H_ */
