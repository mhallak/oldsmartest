/*
 * RolledValue.h
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#ifndef ROLLEDVALUE_H_
#define ROLLEDVALUE_H_
#include "SFDP/ScenarioFeatureType.h"
class RolledValue {
	int m_rollNumber;
	ScenarioFeatureType m_type;
	double m_value;
public:
	RolledValue();
	virtual ~RolledValue();

	int getRollNumber() const;
	void setRollNumber(int rollNumber);
	ScenarioFeatureType getType() const;
	void setType(ScenarioFeatureType type);
	double getValue() const;
	void setValue(double value);
};

#endif /* ROLLEDVALUE_H_ */
