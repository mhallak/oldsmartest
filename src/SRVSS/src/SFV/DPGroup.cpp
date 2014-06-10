/*
 * DPGroup.cpp
 *
 *  Created on: Jun 1, 2014
 *      Author: userws1
 */

#include "SFV/DPGroup.h"

DPGroup::DPGroup(std::string name,ScenarioFeatureGroupType groupType,std::map<ScenarioFeatureType,DPObject *> *objects):
m_name(name),
m_groupType(groupType),
m_objects(objects)
{
}

DPGroup::~DPGroup() {
	// TODO Auto-generated destructor stub
}

