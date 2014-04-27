#include "SFDP/ScenarioFeatureGroupType.h"


#include <ostream>
ScenarioFeatureGroupType::ScenarioFeatureGroupType():
_type(ScenarioFeatureGroupType::unknown_feature_group)
{

}

ScenarioFeatureGroupType::ScenarioFeatureGroupType(ScenarioFeatureGroupTypeE newType):
_type(newType)
{

}

ScenarioFeatureGroupType ScenarioFeatureGroupType::stringToFeatureGroupType(std::string val) throw (std::string)
{
	if(val.compare("map")==0)
	{
		return map;
	}
	else if(val.compare("lights")==0)
	{
		return lights;
	}
	else if(val.compare("objects")==0)
	{
		return objects;
	}
	else if(val.compare("mass_link_i")==0)
	{
		return mass_link_i;
	}
	else if(val.compare("friction_link_i")==0)
	{
		return friction_link_i;
	}
	else if(val.compare("sensor_link_i")==0)
	{
		return sensor_link_i;
	}
	else if(val.compare("platform_pose")==0)
	{
		return platform_pose;
	}
	else if(val.compare("waypoints")==0)
	{
		return waypoints;
	}
	else
		throw val+" is an unknown feature group!";
}


std::string  ScenarioFeatureGroupType::toString(ScenarioFeatureGroupType type)
{
	std::string str;
	switch(type._type)
	{
		case ScenarioFeatureGroupType::map:
			str="map";
			break;
		case ScenarioFeatureGroupType::objects:
			str= "objects";
			break;
		case ScenarioFeatureGroupType::lights:
			str= "lights";
			break;
		case ScenarioFeatureGroupType::mass_link_i:
			str="mass_link_i";
			break;
		case ScenarioFeatureGroupType::friction_link_i:
			str= "friction_link_i";
			break;
		case ScenarioFeatureGroupType::sensor_link_i:
			str= "sensor_link_i";
			break;
		case ScenarioFeatureGroupType::platform_pose:
			str= "platform_pose";
			break;
		case ScenarioFeatureGroupType::waypoints:
			str= "waypoints";
			break;
	}
	return str;
}

void  ScenarioFeatureGroupType::operator= (ScenarioFeatureGroupTypeE newType)
{
	this->_type=newType;
}


bool ScenarioFeatureGroupType::operator==(const ScenarioFeatureGroupType& lhs)
{
	return _type ==lhs._type;
}

bool ScenarioFeatureGroupType::operator!=(const ScenarioFeatureGroupType& lhs)
{
	return !operator==(lhs);
}

bool operator< (const ScenarioFeatureGroupType& lhs, const ScenarioFeatureGroupType& rhs)
{
	return lhs._type<rhs._type;
}
bool operator> (const ScenarioFeatureGroupType& lhs, const ScenarioFeatureGroupType& rhs)
{
	return operator< (rhs,lhs);
}



std::ostream& operator<<(std::ostream& os, const ScenarioFeatureGroupType& dt)
{
	os<< ScenarioFeatureGroupType::toString(dt);
	return os;
}
