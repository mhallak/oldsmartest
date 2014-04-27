/*
 * SFVPlatformPose.h
 *
 *  Created on: Apr 10, 2014
 *      Author: userws1
 */
#ifndef SFVPLATFORMPOSE_H_
#define SFVPLATFORMPOSE_H_

#include "SFV/SFVInterface.h"
#include "utils/ParsableInterface.h"

class SFVPlatformPose : public SFVInterface , public ParsableInterface{
	int m_Id;
	std::string m_platform_name;
	double m_locationX;
	double m_locationY;
	double m_locationAzimut;
public:
	SFVPlatformPose();
	virtual ~SFVPlatformPose();
	void setRolledValue(RolledValue * value);
	TiXmlElement *toXMLElement();
	void fromXMLElement(TiXmlElement * node);
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
