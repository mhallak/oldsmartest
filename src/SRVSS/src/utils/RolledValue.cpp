/*
 * RolledValue.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#include "utils/RolledValue.h"

RolledValue::RolledValue() {
	// TODO Auto-generated constructor stub

}

int RolledValue::getRollNumber() const {
	return m_rollNumber;
}

void RolledValue::setRollNumber(int rollNumber) {
	m_rollNumber = rollNumber;
}

ScenarioFeatureType RolledValue::getType() const {
	return m_type;
}

void RolledValue::setType(ScenarioFeatureType type) {
	m_type = type;
}

double RolledValue::getValue() const {
	return m_value;
}

void RolledValue::setValue(double value) {
	m_value = value;
}

RolledValue::~RolledValue() {
	// TODO Auto-generated destructor stub
}

