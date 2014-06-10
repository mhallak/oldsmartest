/*
 * SFVBase.h
 *
 *  Created on: Jun 8, 2014
 *      Author: userws1
 */

#ifndef SFVBASE_H_
#define SFVBASE_H_
#include "SFV/DPGroup.h"
#include <map>

class SFVComponent;
class SFVBase:public ParsableInterface{

public:
	int m_Id;
	std::string m_name;
	std::string m_objectType;
	std::map<ScenarioFeatureType,DPObject *> * m_objects;
	SFVBase(DPGroup * dpGroup);
	void init(DPGroup * dpGroup);
	virtual ~SFVBase();
	bool calc(SFVComponent * sfvComp);
	virtual void setStructure();
	DPGroup * m_dpGroup;

	TiXmlElement *toXMLElement();
	void fromXMLElement(TiXmlElement * node);
};
#endif /* SFVBASE_H_ */
