/*
 * SDFPComponent.h
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#ifndef SDFPCOMPONENT_H_
#define SDFPCOMPONENT_H_

#include <string>
#include <vector>
#include <map>
#include <tinyxml.h>

#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeatureType.h"
#include "ScenarioFeatureDistributionType.h"

#include "SFV/SFVComponent.h"

/**
 * A data handling class.
 * This class reviews all the given Scenario Features and generates an SFVcomponent according to them
 */
class SDFPComponent {



	std::vector<ScenarioFeatureGroup*> *m_featureGroups;

	/**
	* An auxiliary method to sample a number according to the desired distribution
	* @param distType the distribution type, defines the distribution for the feature
	* @param distParam1 an integer argument, a lower bound for the distribution
	* @param distParam2 an integer argument, an upper bound for the distribution
	* @see rollDice()
	* @see NumberSampler
	* @see ScenarioFeatureDistributionType
	* @return returns a float number sampled according to distribution and bounds
	*/
	float rollForDistType(ScenarioFeatureDistributionType distType,float distParam1,float distParam2);

	/**
	 * An auxiliary method to sample a number for a given feature while taking it's dependencies into account
	 * @param feature a feature object
	 * @see rollDice()
	 * @see ScenarioFeature
	 */

public:

	/**
	 * A constructor
	 */
	SDFPComponent();

	/**
	 * A distructor
	 */
	virtual ~SDFPComponent();

	/**
	 * Adds a feature to the list of features
	 * @param feature a feature object to add
	 * @throw string exception is thrown if the feature is already in the list
	 * @see ScenarioFeature
	 */
	void addScenarioFeatureGroup (ScenarioFeatureGroup *featureGroup) throw (std::string);

	/**
	 * generate a SFVObject by rolling all the features according to their dependencies
	 * @return a SFVObject
	 */
	SFVComponent* genSFV();


	std::vector<ScenarioFeatureGroup*> * getFeatureGroups();
};

#endif /* SDFPCOMPONENT_H_ */
