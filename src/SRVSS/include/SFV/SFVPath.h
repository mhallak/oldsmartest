/*
 * Path.h
 *
 *  Created on: Jun 12, 2014
 *      Author: userws3
 */

#ifndef PATH_H_
#define PATH_H_
#include "SFV/SFVGeneric.h"
#include "SFV/SFVWaypoint.h"
#include "SFDP/ScenarioFeature.h"

class SFVPath : public SFVGeneric<SFVWaypoint,ScenarioFeatureType::number_of_way_points>{
public:
	SFVPath(DPGroup * dpGroup);
	double getPathLength();
	double getNumOfWayPoints();
	virtual ~SFVPath();
};

#endif /* PATH_H_ */
