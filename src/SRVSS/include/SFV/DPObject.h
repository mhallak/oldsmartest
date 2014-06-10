/*
 * DPObject.h
 *
 *  Created on: Jun 1, 2014
 *      Author: userws1
 */

#ifndef DPOBJECT_H_
#define DPOBJECT_H_
#include <SFDP/ScenarioFeature.h>
#include <vector>

class DPObject {
public:
	DPObject();
	DPObject(ScenarioFeature * feature);
	DPObject *clone();
	void calc();
	virtual ~DPObject();
	float m_result;
	float getResult();
	void setResult(float res);
	ScenarioFeature * m_feature;
};

#endif /* DPOBJECT_H_ */
