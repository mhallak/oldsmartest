/*
 * SFVWaypoint.h
 *
 *  Created on: Apr 10, 2014
 *      Author: userws1
 */

#ifndef SFVWAYPOINT_H_
#define SFVWAYPOINT_H_

#include "SFV/SFVInterface.h"
#include "utils/ParsableInterface.h"

class SFVWaypoint : public SFVInterface , public ParsableInterface{
	int m_id;
	float m_wp_i_distance_i;
	float m_relative_angle;
	float m_wp_velocity;
public:
	SFVWaypoint();
	virtual ~SFVWaypoint();
	void setRolledValue(RolledValue * value);
	TiXmlElement *toXMLElement();
	void fromXMLElement(TiXmlElement * node);
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
