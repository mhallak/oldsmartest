#include "SFDP/ScenarioFeatureDistributionType.h"

ScenarioFeatureDistributionType::ScenarioFeatureDistributionType(ScenarioFeatureDistributionTypeE newType):
_type(newType)
{

}

ScenarioFeatureDistributionType ScenarioFeatureDistributionType::stringToDistributionType(std::string val) throw (std::string)
{
	if(val.compare("uniform_int_discrete")==0)
	{
		return uniform_int_discrete;
	}
	else if(val.compare("uniform_real_discrete")==0)
	{
		return uniform_real_discrete;
	}
	else if(val.compare("uniform_int_continuous")==0)
	{
		return uniform_int_continuous;
	}
	else if(val.compare("uniform_real_continuous")==0)
	{
		return uniform_real_continuous;
	}
	else if(val.compare("normal_int_continuous")==0)
	{
		return normal_int_continuous;
	}
	else if(val.compare("normal_real_continuous")==0)
	{
		return normal_real_continuous;
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
