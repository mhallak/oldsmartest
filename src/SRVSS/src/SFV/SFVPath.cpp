/*
 * Path.cpp
 *
 *  Created on: Jun 12, 2014
 *      Author: userws3
 */

#include "SFV/SFVPath.h"

#include <iostream>

SFVPath::SFVPath(DPGroup* dpGroup) : SFVGeneric<SFVWaypoint,ScenarioFeatureType::number_of_way_points>(dpGroup){
}

SFVPath::~SFVPath() {

	// TODO Auto-generated destructor stub
}

double SFVPath::getPathLength()
{
	double path_length = 0;
	for(SFVWaypoint* wp:*m_objects)
	{
		path_length = path_length + wp->getWpIDistanceI();
	}
	//std::cout << "path_length = " << path_length << std::endl;

 return path_length;
}

double SFVPath::getNumOfWayPoints()
{
return 0;
}
