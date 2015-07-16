/*
 * Resources.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef RESOURCES_H_
#define RESOURCES_H_

class Resources {
public:
	Resources();
	virtual ~Resources();
	 static const int forwardStartIndex = 245;
	 static const int forwardEndIndex = 402;
	 static const int leftStartIndex = 500;
	 static const int leftEndIndex = 620;
	 static const int rightStartIndex = 40;
	 static const int rightEndIndex = 200;

	 static const float sleepTime = 0.3;
	 static const int resolutioncoefficient = 10;

	 static const int worldWidth = 850;
	 static const int worldHight = 850;
	 static const int globalStartX = worldWidth / 2;
	 static const int globalStartY = worldHight / 2;

	 //Signs
	 static const int freeSign = 0;
	 static const int unknowenSign = 1;
	 static const int blockSign = 4;
	 static const int robotSign = 7;

	 static const double minProbability = 0.4;
	 static const double numberOfParticles = 4;
	 static const int reasonableNumberOfWrongs = 27;

	 //Probability thresholds
	 #define DISTANCE_THRESHOLD 	10
	 #define YAW_THRESHOLD 		0.52
	 #define MIU  1.41;

	 #define PI 3.14159265
};

#endif /* RESOURCES_H_b */
