/*
 * ScenarioFeatureGroup.h
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#ifndef SCENARIOFEATUREGROUP_H_
#define SCENARIOFEATUREGROUP_H_

#include "ScenarioFeatureGroupType.h"
#include <string>
#include <vector>


class ScenarioFeatureGroup {

	ScenarioFeatureGroupType m_featureGroupType;
	std::string m_name;
	std::vector<ScenarioFeature*> *m_features;

public:
	ScenarioFeatureGroup();
	ScenarioFeatureGroup(std::string featureType);
	virtual ~ScenarioFeatureGroup();

	ScenarioFeatureGroupType get_featureGroupType();
	void set_featureGroupType(ScenarioFeatureGroupType type);

	std::string get_name();
	void set_name(std::string name);

	std::vector<ScenarioFeature*> * get_features();

	void addFeature(ScenarioFeature* feature);
};

#endif /* SCENARIOFEATUREGROUP_H_ */




