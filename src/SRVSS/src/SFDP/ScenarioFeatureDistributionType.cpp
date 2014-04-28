#include "SFDP/ScenarioFeatureDistributionType.h"

ScenarioFeatureDistributionType::ScenarioFeatureDistributionType(ScenarioFeatureDistributionTypeE newType):
_type(newType)
{

}

ScenarioFeatureDistributionType ScenarioFeatureDistributionType::stringToDistributionType(std::string val) throw (std::string)
{
	if(val.compare("uniform_discrete")==0)
	{
		return uniform_discrete;
	}
	else if(val.compare("uniform_continuous")==0)
	{
		return uniform_continuous;
	}
	else if(val.compare("normal_continuous")==0)
	{
		return normal_continuous;
	}
	else
		throw val+"is an unknown distribution type!";
}


void ScenarioFeatureDistributionType::operator= (ScenarioFeatureDistributionTypeE newType)
{
	_type=newType;
}
bool ScenarioFeatureDistributionType::operator==(const ScenarioFeatureDistributionType& lhs)
{
	return _type ==lhs._type;
}
bool ScenarioFeatureDistributionType::operator==(const ScenarioFeatureDistributionTypeE& lhs)
{
	return _type ==lhs;
}
bool ScenarioFeatureDistributionType::operator!=(const ScenarioFeatureDistributionType& lhs)
{
	return !operator==(lhs);
}
