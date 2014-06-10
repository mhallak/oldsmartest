/*
 * SFVWaypoint.h
 *
 *  Created on: Apr 10, 2014
 *      Author: userws1
 */

#ifndef SFVWAYPOINT_H_
#define SFVWAYPOINT_H_

#include "utils/ParsableInterface.h"
#include "SFV/SFVBase.h"

class SFVWaypoint : public SFVBase{

public:
	void setStructure();
	SFVWaypoint(DPGroup * dpGroup);
	virtual ~SFVWaypoint();


	int getId() const;
	void setId(int id);
	float getRelativeAngle() const;
	void setRelativeAngle(float relativeAngle);
	float getWpIDistanceI() const;
	void setWpIDistanceI(float wpIDistanceI);
	float getWpVelocity() const;
	void setWpVelocity(float wpVelocty);
};

#endif /* SFVWAYPOINT_H_ */
