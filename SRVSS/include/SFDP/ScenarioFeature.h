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
#include "ScenarioFeatureDependecy.h"
#include <string>
#include <vector>


class ScenarioFeature {

	ScenarioFeatureType m_featureType;
	ScenarioFeatureDistributionType m_distType;
	float m_dist_param_1;
	float m_dist_param_2;
	std::vector<ScenarioFeatureDependecy * > *m_featureDependecies;
	float m_rolledValue;
	bool m_isCalculated;

public:
	ScenarioFeature(std::string featureType);
	virtual ~ScenarioFeature();

	float get_rolledValue();
	bool isCalculated();
	void reset();
	void set_rolledValue(float val);

	ScenarioFeatureType get_featureType();
	void set_featureType(ScenarioFeatureType type);

	ScenarioFeatureDistributionType get_distType();
	void set_distributionType(ScenarioFeatureDistributionType type);

	float get_dist_param_1();
	void set_dist_param_1(float val);

	float get_dist_param_2();
	void set_dist_param_2(float val);


	void addFeatureDependency(ScenarioFeatureDependecy * featureDepend);
	std::vector<ScenarioFeatureDependecy*> * get_featureDependecies();
	void set_supportingFeature(ScenarioFeature * suppFeature);

	bool isDependentOn(ScenarioFeature * other);
};

#endif /* SCENARIOFEATURE_H_ */




