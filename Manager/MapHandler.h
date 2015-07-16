/*
 * MapHandler.h
 *
 *  Created on: Jul 15, 2015
 *      Author: colman
 */

#ifndef MAPHANDLER_H_
#define MAPHANDLER_H_

#include "../Map.h"
#include "../PathFinder.h"
#include "../Utils/Location.h"
#include "../Manager/CofigurationManager.h"
#include <math.h>
using namespace std;

class MapHandler
{
public:
	MapHandler();
	virtual ~MapHandler();
	Map RunMapProcessing(ConfigurationParametersStruct ParametersStruct);
};

#endif /* MAPHANDLER_H_ */
