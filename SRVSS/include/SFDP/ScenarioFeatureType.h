/*
 * ScenarioFeatureType.h
 *
 *  Created on: Feb 5, 2014
 *      Author: userws1
 */

#ifndef SCENARIOFEATURETYPE_H_
#define SCENARIOFEATURETYPE_H_
#include <string>

/**
 * An enum class
 * This class defines the feature types and used for parsing and comparison
 */
class ScenarioFeatureType{

	/**
	 * overloaded method for debugging
	 */
	friend std::ostream& operator<<(std::ostream& os, const ScenarioFeatureType& dt);

	/**
	 * overloaded method for hashing
	 * @param lhs a ScenarioFeatureType used in the comparison
	 * @param rhs a ScenarioFeatureType used in the comparison
	 * return true if lhs < rhs
	 */
	friend bool operator< (const ScenarioFeatureType& lhs,const ScenarioFeatureType& rhs);

	/**
	 * overloaded method for hashing
	 * @param lhs a ScenarioFeatureType used in the comparison
	 * @param rhs a ScenarioFeatureType used in the comparison
	 * return true if lhs > rhs
	 */
	friend bool operator> (const ScenarioFeatureType& lhs,const ScenarioFeatureType& rhs);
public:

	/**
	 * An enum.
	 * Used to identify the different feature types
	 */
	enum ScenarioFeatureTypeE{
		unknown_feature,
		topographic_map,
		number_of_objects,
		object_i_type,
		object_i_scaling_factor,
		object_i_location_on_the_X_axis,
		object_i_location_on_the_Y_axis,
		object_i_location_on_the_Z_axis,
		object_i_location_Roll,
		object_i_location_Pitch,
		object_i_location_Yaw,
		number_of_light_sources,
		light_source_i_type,
		light_source_i_location_on_the_X_axis,
		light_source_i_location_on_the_Y_axis,
		light_source_i_location_on_the_Z_axis,
		light_source_i_range,
		light_source_i_direction_on_X_axis,
		light_source_i_direction_on_Y_axis,
		light_source_i_light_cone
	};

	/**
	 * A constructor.
	 */
	ScenarioFeatureType();

	/**
	 * A constructor.
	 * @param newType the feature type
	 * @see _type
	 */
	ScenarioFeatureType(ScenarioFeatureTypeE newType);

	/**
	 * A type field.
	 * Used to store the feature type
	 */
	ScenarioFeatureTypeE _type;

	/**
	 * Static method to parse the feature type from string
	 * @param val the string to be parsed
	 * @throw string exception in case of an unknown feature
	 * @return a ScenarioFeatureType object
	 */
	static ScenarioFeatureType stringToFeatureType(std::string val) throw (std::string);

	/**
	 * overloaded method for comparison
	 * @param newType a ScenarioFeatureType used in the comparison
	 * @see _type
	 * @return true if _type == newType
	 */
	void operator= (ScenarioFeatureTypeE newType);

	/**
	 * overloaded method for comparison
	 * @param lhs a ScenarioFeatureType used in the comparison
	 * @return true if this == lhs
	 */
	bool operator==(const ScenarioFeatureType& lhs);

	/**
	 * overloaded method for comparison
	 * @param lhs a ScenarioFeatureType used in the comparison
	 * @return true if this != lhs
	 */
	bool operator!=(const ScenarioFeatureType& lhs);


};


#endif /* SCENARIOFEATURETYPE_H_ */
