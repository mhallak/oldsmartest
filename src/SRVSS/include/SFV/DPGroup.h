/*
 * DPGroup.h
 *
 *  Created on: Jun 1, 2014
 *      Author: userws1
 */

#ifndef DPGROUP_H_
#define DPGROUP_H_

#include <SFDP/ScenarioFeatureType.h>
#include <SFDP/ScenarioFeatureGroupType.h>
#include "DPObject.h"
#include <string>
#include <map>

class DPGroup {
public:
	std::string m_name;
	ScenarioFeatureGroupType m_groupType;
	std::map<ScenarioFeatureType,DPObject *> *m_objects;
	DPGroup(std::string name,ScenarioFeatureGroupType groupType,std::map<ScenarioFeatureType,DPObject *> *objects);
	virtual ~DPGroup();
};

#endif /* DPGROUP_H_ */
