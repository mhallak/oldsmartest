/*
 * ScenarioFeatureDependecy.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: userws1
 */

#include "SFDP/ScenarioFeatureDependecyType.h"


ScenarioFeatureDependecyType::ScenarioFeatureDependecyType(ScenarioFeatureDependecyTypeE newType):
_type(newType)
{

}

ScenarioFeatureDependecyType ScenarioFeatureDependecyType::stringToDependencyType(std::string val) throw (std::string)
{
	if(val.compare("roll_number")==0)
	{
		return roll_number;
	}
	else if(val.compare("upper_bound")==0)
	{
		return upper_bound;
	}
	else if(val.compare("lower_bound")==0)
	{
		return upper_bound;
	}
	else
		throw val+"is an unknown dependency type!";
}


void ScenarioFeatureDependecyType::operator= (ScenarioFeatureDependecyTypeE newType)
{
	_type=newType;
}
bool ScenarioFeatureDependecyType::operator==(const ScenarioFeatureDependecyType& lhs)
{
	return _type ==lhs._type;
}
bool ScenarioFeatureDependecyType::operator==(const ScenarioFeatureDependecyTypeE& lhs)
{
	return _type ==lhs;
}
bool ScenarioFeatureDependecyType::operator!=(const ScenarioFeatureDependecyType& lhs)
{
	return !operator==(lhs);
}
