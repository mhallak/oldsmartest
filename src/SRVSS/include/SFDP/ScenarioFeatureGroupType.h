/*
 * ScenarioFeatureGroupType.h
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#ifndef SCENARIOFEATUREGROUPTYPE_H_
#define SCENARIOFEATUREGROUPTYPE_H_
#include <string>
#include <SFDP/ScenarioFeature.h>
/**
 * An enum class
 * This class defines the feature types and used for parsing and comparison
 */
class ScenarioFeatureGroupType{

	/**
	 * overloaded method for debugging
	 */
	friend std::ostream& operator<<(std::ostream& os, const ScenarioFeatureGroupType& dt);

	/**
	 * overloaded method for hashing
	 * @param lhs a ScenarioFeatureGroupType used in the comparison
	 * @param rhs a ScenarioFeatureGroupType used in the comparison
	 * return true if lhs < rhs
	 */
	friend bool operator< (const ScenarioFeatureGroupType& lhs,const ScenarioFeatureGroupType& rhs);

	/**
	 * overloaded method for hashing
	 * @param lhs a ScenarioFeatureGroupType used in the comparison
	 * @param rhs a ScenarioFeatureGroupType used in the comparison
	 * return true if lhs > rhs
	 */
	friend bool operator> (const ScenarioFeatureGroupType& lhs,const ScenarioFeatureGroupType& rhs);
public:

	/**
	 * An enum.
	 * Used to identify the different feature types
	 */
	enum ScenarioFeatureGroupTypeE{
		unknown_feature_group,
		map,
		lights,
		objects,
		mass_link_i,
		friction_link_i,
		sensor_link_i
	};

	/**
	 * A constructor.
	 */
	ScenarioFeatureGroupType();

	/**
	 * A constructor.
	 * @param newType the feature type
	 * @see _type
	 */
	ScenarioFeatureGroupType(ScenarioFeatureGroupTypeE newType);

	/**
	 * A type field.
	 * Used to store the feature type
	 */
	ScenarioFeatureGroupTypeE _type;

	/**
	 * Static method to parse the feature type from string
	 * @param val the string to be parsed
	 * @throw string exception in case of an unknown feature
	 * @return a ScenarioFeatureGroupType object
	 */
	static ScenarioFeatureGroupType stringToFeatureGroupType(std::string val) throw (std::string);


	/**
	 * string method for printing
	 * @return a string object
	 */
	static std::string toString(ScenarioFeatureGroupType type);


	/**
	 * overloaded method for comparison
	 * @param newType a ScenarioFeatureGroupType used in the comparison
	 * @see _type
	 * @return true if _type == newType
	 */
	void operator= (ScenarioFeatureGroupTypeE newType);

	/**
	 * overloaded method for comparison
	 * @param lhs a ScenarioFeatureGroupType used in the comparison
	 * @return true if this == lhs
	 */
	bool operator==(const ScenarioFeatureGroupType& lhs);

	/**
	 * overloaded method for comparison
	 * @param lhs a ScenarioFeatureGroupType used in the comparison
	 * @return true if this != lhs
	 */
	bool operator!=(const ScenarioFeatureGroupType& lhs);


};


#endif /* SCENARIOFEATUREGROUPTYPE_H_ */
