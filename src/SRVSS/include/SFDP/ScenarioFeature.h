/*
 * ScenarioFeature.h
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#ifndef SCENARIOFEATURE_H_
#define SCENARIOFEATURE_H_

#include "ScenarioFeatureType.h"
#include "ScenarioFeatureDistributionType.h"
#include <string>
#include <vector>


class ScenarioFeature {

	ScenarioFeatureType m_featureType;
	ScenarioFeatureDistributionType m_distType;
	float m_dist_param_1;
	float m_dist_param_2;

public:
	ScenarioFeature(std::string featureType);
	virtual ~ScenarioFeature();


	ScenarioFeatureType get_featureType();
	void set_featureType(ScenarioFeatureType type);

	ScenarioFeatureDistributionType get_distType();
	void set_distributionType(ScenarioFeatureDistributionType type);

	float get_dist_param_1();
	void set_dist_param_1(float val);

	float get_dist_param_2();
	void set_dist_param_2(float val);
};

#endif /* SCENARIOFEATURE_H_ */




