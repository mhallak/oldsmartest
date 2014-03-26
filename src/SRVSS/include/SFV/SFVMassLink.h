/*
 * SFVMassLink.h
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#ifndef SFVMASSLINK_H_
#define SFVMASSLINK_H_
#include "SFV/SFVInterface.h"
#include "utils/ParsableInterface.h"
class SFVMassLink : public SFVInterface , public ParsableInterface{
	int m_Id;
	std::string m_link_name;
	double m_mass;
	double m_inertiaIxxComponent;
	double m_inertiaIyyComponent;
	double m_inertiaIzzComponent;
	double m_locationXDeviation;
	double m_locationYDeviation;
	double m_locationZDeviation;
	double m_locationRollDeviation;
	double m_locationPitchDeviation;
	double m_locationYawDeviation;
public:
	SFVMassLink();
	virtual ~SFVMassLink();


	int getId() const;
	void setId(int id);

	void setRolledValue(RolledValue * value);
	TiXmlElement *toXMLElement();
	void fromXMLElement(TiXmlElement * node);

	double getInertiaIxxComponent() const;
	void setInertiaIxxComponent(double inertiaIxxComponent);

	double getInertiaIyyComponent() const;
	void setInertiaIyyComponent(double inertiaIyyComponent);

	double getInertiaIzzComponent() const;
	void setInertiaIzzComponent(double inertiaIzzComponent);

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

	double getMass() const;
	void setMass(double mass);
	const std::string& getLinkName() const;
	void setLinkName(const std::string& linkName);
};

#endif /* SFVMASSLINK_H_ */
