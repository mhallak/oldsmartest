/*
 * SFVSensorLink.h
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#ifndef SFVSENSORLINK_H_
#define SFVSENSORLINK_H_
#include "SFV/SFVInterface.h"
#include "utils/ParsableInterface.h"
class SFVSensorLink : public SFVInterface , public ParsableInterface{
	int m_Id;
	std::string m_link_name;
	double m_locationXDeviation;
	double m_locationYDeviation;
	double m_locationZDeviation;
	double m_locationRollDeviation;
	double m_locationPitchDeviation;
	double m_locationYawDeviation;
public:
	SFVSensorLink();
	virtual ~SFVSensorLink();

	int getId() const;
	void setId(int id);
	void setRolledValue(RolledValue * value);
	TiXmlElement *toXMLElement();
	void fromXMLElement(TiXmlElement * node);
	double getLocationPitchDeviation() const;
	void setLocationPitchDeviation(double locationPitchDeviation);

	double getLocationRollDeviation() const;
	void setLocationRollDeviation(double locationRollDeviation);

	double getLocationXDeviation() const;
	void setLocationXDeviation(double locationXDeviation);

	double getLocationYawDeviation() const;
	void setLocationYawDeviation(double locationYawDeviation);

	double getLocationYDeviation() const;
	void setLocationYDeviation(double locationYDeviation);

	double getLocationZDeviation() const;
	void setLocationZDeviation(double locationZDeviation);
	const std::string& getLinkName() const;
	void setLinkName(const std::string& linkName);
};

#endif /* SFVSENSORLINK_H_ */
