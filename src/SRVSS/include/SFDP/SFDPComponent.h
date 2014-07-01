/*
 * SFDPComponent.h
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#ifndef SFDPCOMPONENT_H_
#define SFDPCOMPONENT_H_

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
class SFDPComponent {



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



public:

	/**
	 * A constructor
	 */
	SFDPComponent();

	/**
	 * A distructor
	 */
	virtual ~SFDPComponent();

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
	SFVComponent* genSFV(std::string resources_file_url);

	std::vector<SFVComponent *> * genSFVs(int num_of_SFVs, std::string SFVs_destination_folder_path, std::string resources_file_url);

	std::vector<ScenarioFeatureGroup*> * getFeatureGroups();

};

#endif /* SFDPCOMPONENT_H_ */
