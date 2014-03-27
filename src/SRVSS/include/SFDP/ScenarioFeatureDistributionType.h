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
		uniform_int_discrete,
		uniform_real_discrete,
		uniform_int_continuous,
		uniform_real_continuous,
		normal_int_continuous,
		normal_real_continuous
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
