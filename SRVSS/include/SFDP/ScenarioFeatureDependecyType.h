/*
 * ScenarioFeatureDependecy.h
 *
 *  Created on: Feb 5, 2014
 *      Author: userws1
 */

#ifndef SCENARIOFEATUREDEPENDECYTYPE_H_
#define SCENARIOFEATUREDEPENDECYTYPE_H_
#include <string>


class ScenarioFeatureDependecyType {
public:
	enum ScenarioFeatureDependecyTypeE{
		unknown_dependecy,
		roll_number,
		upper_bound,
		lower_bound,
	};

	ScenarioFeatureDependecyType(ScenarioFeatureDependecyTypeE newType);

	ScenarioFeatureDependecyTypeE _type;

	static ScenarioFeatureDependecyType stringToDependencyType(std::string val) throw (std::string);

	void operator= (ScenarioFeatureDependecyTypeE newType);
	bool operator==(const ScenarioFeatureDependecyType& lhs);
	bool operator==(const ScenarioFeatureDependecyTypeE& lhs);
	bool operator!=(const ScenarioFeatureDependecyType& lhs);


};

#endif /* SCENARIOFEATUREDEPENDECYTYPE_H_ */
