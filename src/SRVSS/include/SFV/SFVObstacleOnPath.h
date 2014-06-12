/*
 * SFVObject.h
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#ifndef SFVOBSTACLE_ON_PATH_H_
#define SFVOBSTACLE_ON_PATH_H_
#include "utils/ParsableInterface.h"
#include "SFV/DPGroup.h"
#include "SFV/DPObject.h"
#include "SFV/SFVBase.h"

class SFVObstacleOnPath : public SFVBase
{
	DPGroup* m_dpGroup;
public:

	void setStructure();


	SFVObstacleOnPath(DPGroup* dpGroup);
	virtual ~SFVObstacleOnPath();

	double getPitch() const;
	void setPitch(double pitch);
	double getRoll() const;
	void setRoll(double roll);
	double getScale() const;
	void setScale(double scale);
	int getType() const;
	void setType(int type);
	double getAlong() const;
	void setAlong(double x);
	double getPerpendicular() const;
	void setPerpendicular(double y);
	double getYaw() const;
	void setYaw(double yaw);
	double getZ() const;
	void setZ(double z);
	int getId() const;
	void setId(int id);
};

#endif /* SFVOBSTACLE_ON_PATH_H_ */
