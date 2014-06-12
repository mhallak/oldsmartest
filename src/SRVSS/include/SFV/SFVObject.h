/*
 * SFVObject.h
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#ifndef SFVOBJECT_H_
#define SFVOBJECT_H_
#include "utils/ParsableInterface.h"
#include "SFV/DPGroup.h"
#include "SFV/DPObject.h"
#include "SFV/SFVBase.h"

class SFVObject : public SFVBase
{
public:

	void setStructure();


	SFVObject(DPGroup* dpGroup);
	virtual ~SFVObject();

	double getPitch() const;
	void setPitch(double pitch);
	double getRoll() const;
	void setRoll(double roll);
	double getScale() const;
	void setScale(double scale);
	int getType() const;
	void setType(int type);
	double getX() const;
	void setX(double x);
	double getY() const;
	void setY(double y);
	double getYaw() const;
	void setYaw(double yaw);
	double getZ() const;
	void setZ(double z);
	int getId() const;
	void setId(int id);
};

#endif /* SFVOBJECT_H_ */
