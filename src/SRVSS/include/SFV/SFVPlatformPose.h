/*
 * SFVPlatformPose.h
 *
 *  Created on: Apr 10, 2014
 *      Author: userws1
 */
#ifndef SFVPLATFORMPOSE_H_
#define SFVPLATFORMPOSE_H_
#include "utils/ParsableInterface.h"
#include "SFVBase.h"

class SFVPlatformPose : public SFVBase{

public:
	void setStructure();

	SFVPlatformPose(DPGroup * dpGroup);
	virtual ~SFVPlatformPose();

	int getId() const;
	void setId(int id);
	double getLocationAzimut() const;
	void setLocationAzimut(double locationAzimut);
	double getLocationX() const;
	void setLocationX(double locationX);
	double getLocationY() const;
	void setLocationY(double locationY);
	const std::string& getPlatformName() const;
	void setPlatformName(const std::string& platformName);
};

#endif /* SFVPLATFORMPOSE_H_ */
