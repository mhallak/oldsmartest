/*
 * SFVLight.h
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#ifndef SFVLIGHT_H_
#define SFVLIGHT_H_
#include "utils/ParsableInterface.h"
#include "SFVBase.h"
class SFVLight : public SFVBase
{
public:

	void setStructure();

	SFVLight(DPGroup * dpGroup);
	virtual ~SFVLight();

	double getCone() const;
	void setCone(double cone);
	double getDirectionX() const;
	void setDirectionX(double directionX);
	double getDirectionY() const;
	void setDirectionY(double directionY);
	int getId() const;
	void setId(int id);
	double getRange() const;
	void setRange(double range);
	int getType() const;
	void setType(int type);
	double getX() const;
	void setX(double x);
	double getY() const;
	void setY(double y);
	double getZ() const;
	void setZ(double z);
};

#endif /* SFVLIGHT_H_ */
