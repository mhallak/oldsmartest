/*
 * SFVMassLink.h
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#ifndef SFVMASSLINK_H_
#define SFVMASSLINK_H_
#include "utils/ParsableInterface.h"
#include "SFVBase.h"
class SFVMassLink : public SFVBase{

public:
	void setStructure();

	SFVMassLink(DPGroup *);
	virtual ~SFVMassLink();


	int getId() const;
	void setId(int id);


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
	std::string& getLinkName();
	void setLinkName(const std::string& linkName);
};

#endif /* SFVMASSLINK_H_ */
