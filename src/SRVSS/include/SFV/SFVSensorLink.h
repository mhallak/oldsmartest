/*
 * SFVSensorLink.h
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#ifndef SFVSENSORLINK_H_
#define SFVSENSORLINK_H_
#include "utils/ParsableInterface.h"
#include "SFV/SFVBase.h"

class SFVSensorLink : public SFVBase{

public:
	void setStructure();

	SFVSensorLink(DPGroup *dpGroup);
	virtual ~SFVSensorLink();
	int getId() const;
	void setId(int id);

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
