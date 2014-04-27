/*
 * ScenarioFeatureDistributionType.h
 *
 *  Created on: Feb 5, 2014
 *      Author: userws1
 */

#ifndef SCENARIOFEATUREDISTRIBUTIONTYPE_H_
#define SCENARIOFEATUREDISTRIBUTIONTYPE_H_

#include <string>

class ScenarioFeatureDistributionType{

public:
	enum ScenarioFeatureDistributionTypeE{
		unknown_distribution,
		uniform_discrete,
		uniform_continuous,
		normal_continuous
	};


	ScenarioFeatureDistributionType(ScenarioFeatureDistributionTypeE newType);


	ScenarioFeatureDistributionTypeE _type;

	static ScenarioFeatureDistributionType stringToDistributionType(std::string val) throw (std::string);


	void operator= (ScenarioFeatureDistributionTypeE newType);
	bool operator==(const ScenarioFeatureDistributionType& lhs);
	bool operator==(const ScenarioFeatureDistributionTypeE& lhs);
	bool operator!=(const ScenarioFeatureDistributionType& lhs);

};




#endif /* SCENARIOFEATUREDISTRIBUTIONTYPE_H_ */
