
#include "Robot/Robot.h"
#include "Managers/Manager.h"
#include "Managers/MapHandler.h"
#include "Managers/WayPointManager.h"
#include "Map/Map.h"
#include "Utils/Utils.h"
#include "Managers/PathFinder.h"
#include "Utils/Location.h"
#include "Managers/CofigurationManager.h"
#include "Movement/PlanGoToTarget.h"

#include <fstream>

using namespace std;

int main()
{
	CofigurationManager CofigurationManager;
	MapHandler MapHandler;
	ConfigurationParametersStruct ParametersStruct = CofigurationManager.ReadFromFile();
	Map mapObject = MapHandler.RunMapProcessing(ParametersStruct);
	PathFinder PathFinder(mapObject);
	Location robotLoc(ParametersStruct.robot_location_x, ParametersStruct.robot_location_y);
	Location destLoc(ParametersStruct.dest_x, ParametersStruct.dest_y);
	vector<Location> _resultPath = PathFinder.findPath(robotLoc, destLoc);
	cout << "the p was read are:" << endl;
	WayPointManager WayPointManager(_resultPath,mapObject,ParametersStruct);
	//WayPointManager::isTargetReached = false;

	Robot robot("localhost",6665, mapObject);
	PlanGoToTarget plnToTarget(&robot, &WayPointManager);
	Manager manager(&robot, &plnToTarget);
	manager.run();





}
