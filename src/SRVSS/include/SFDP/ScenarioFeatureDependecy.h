/*
 * ScenarioFeatureDependecy.h
 *
 *  Created on: Feb 5, 2014
 *      Author: userws1
 */

#ifndef SCENARIOFEATUREDEPENDECY_H_
#define SCENARIOFEATUREDEPENDECY_H_
#include <string>
#include "ScenarioFeatureType.h"
#include "ScenarioFeatureDependecyType.h"

class ScenarioFeature;
class ScenarioFeatureDependecy {
	ScenarioFeature * m_supportingFeature;
	ScenarioFeatureType m_supportingFeatureType;
	ScenarioFeatureDependecyType m_dependencyType;

public:
	ScenarioFeatureDependecy(std::string val);
	ScenarioFeatureDependecy();
	ScenarioFeatureDependecy(ScenarioFeatureDependecyType val);
	virtual ~ScenarioFeatureDependecy();

	void set_dependecyType(ScenarioFeatureDependecyType val);
	void set_supportingFeature(ScenarioFeature * feature);
	void set_supportingFeatureType(ScenarioFeatureType featureType);

	ScenarioFeatureDependecyType get_dependecyType();
	ScenarioFeature * get_supportingFeature();
	ScenarioFeatureType get_supportingFeatureType();
};

#endif /* SCENARIOFEATUREDEPENDECY_H_ */
