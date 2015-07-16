
#include "Robot.h"
#include "Manager.h"
#include "Plans/PlnObstacleAvoid.h"
#include "Manager/MapHandler.h"
#include "WayPointManager.h"
#include "Map.h"
#include "Utils.h"
#include "PathFinder.h"
#include "Utils/Location.h"
#include "Manager/CofigurationManager.h"

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


	Robot robot("localhost",6665);
	PlnObstacleAvoid plnOA(&robot);
	Manager manager(&robot, &plnOA);
	manager.run();





}
