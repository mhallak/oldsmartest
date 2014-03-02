#include "SFDP/ScenarioFeatureType.h"


#include <ostream>
ScenarioFeatureType::ScenarioFeatureType():
_type(ScenarioFeatureType::unknown_feature)
{

}

ScenarioFeatureType::ScenarioFeatureType(ScenarioFeatureTypeE newType):
_type(newType)
{

}

ScenarioFeatureType ScenarioFeatureType::stringToFeatureType(std::string val) throw (std::string)
{
	if(val.compare("topographic_map")==0)
	{
		return topographic_map;
	}
	else if(val.compare("number_of_objects")==0)
	{
		return number_of_objects;
	}
	else if(val.compare("object_i_type")==0)
	{
		return object_i_type;
	}
	else if(val.compare("object_i_scaling_factor")==0)
	{
		return object_i_scaling_factor;
	}
	else if(val.compare("object_i_location_on_the_X_axis")==0)
	{
		return object_i_location_on_the_X_axis;
	}
	else if(val.compare("object_i_location_on_the_Y_axis")==0)
	{
		return object_i_location_on_the_Y_axis;
	}
	else if(val.compare("object_i_location_on_the_Z_axis")==0)
	{
		return object_i_location_on_the_Z_axis;
	}
	else if(val.compare("object_i_location_Roll")==0)
	{
		return object_i_location_Roll;
	}
	else if(val.compare("object_i_location_Pitch")==0)
	{
		return object_i_location_Pitch;
	}
	else if(val.compare("object_i_location_Yaw")==0)
	{
		return object_i_location_Yaw;
	}
	else if(val.compare("number_of_light_sources")==0)
	{
		return number_of_light_sources;
	}
	else if(val.compare("light_source_i_type")==0)
	{
		return light_source_i_type;
	}
	else if(val.compare("light_source_i_location_on_the_X_axis")==0)
	{
		return light_source_i_location_on_the_X_axis;
	}
	else if(val.compare("light_source_i_location_on_the_Y_axis")==0)
	{
		return light_source_i_location_on_the_Y_axis;
	}
	else if(val.compare("light_source_i_location_on_the_Z_axis")==0)
	{
		return light_source_i_location_on_the_Z_axis;
	}
	else if(val.compare("light_source_i_range")==0)
	{
		return light_source_i_range;
	}
	else if(val.compare("light_source_i_direction_on_X_axis")==0)
	{
		return light_source_i_direction_on_X_axis;
	}
	else if(val.compare("light_source_i_direction_on_Y_axis")==0)
	{
		return light_source_i_direction_on_Y_axis;
	}
	else if(val.compare("light_source_i_light_cone")==0)
	{
		return light_source_i_light_cone;
	}
	else
		throw val+" is an unknown feature!";
}


std::string  ScenarioFeatureType::toString(ScenarioFeatureType type)
{
	std::string str;
	switch(type._type)
	{
		case ScenarioFeatureType::unknown_feature:
			str="unknown_feature";
			break;
		case ScenarioFeatureType::topographic_map:
			str= "topographic_map";
			break;
		case ScenarioFeatureType::number_of_objects:
			str= "number_of_objects";
			break;
		case ScenarioFeatureType::object_i_type:
			str= "object_i_type";
			break;
		case ScenarioFeatureType::object_i_scaling_factor:
			str= "object_i_scaling_factor";
			break;
		case ScenarioFeatureType::object_i_location_on_the_X_axis:
			str= "object_i_location_on_the_X_axis";
			break;
		case ScenarioFeatureType::object_i_location_on_the_Y_axis:
			str= "object_i_location_on_the_Y_axis";
			break;
		case ScenarioFeatureType::object_i_location_on_the_Z_axis:
			str= "object_i_location_on_the_Z_axis";
			break;
		case ScenarioFeatureType::object_i_location_Roll:
			str= "object_i_location_Roll";
			break;
		case ScenarioFeatureType::object_i_location_Pitch:
			str= "object_i_location_Pitch";
			break;
		case ScenarioFeatureType::object_i_location_Yaw:
			str= "object_i_location_Yaw";
			break;
		case ScenarioFeatureType::number_of_light_sources:
			str= "number_of_light_sources";
			break;
		case ScenarioFeatureType::light_source_i_type:
			str= "light_source_i_type";
			break;
		case ScenarioFeatureType::light_source_i_location_on_the_X_axis:
			str= "light_source_i_location_on_the_X_axis";
			break;
		case ScenarioFeatureType::light_source_i_location_on_the_Y_axis:
			str= "light_source_i_location_on_the_Y_axis";
			break;
		case ScenarioFeatureType::light_source_i_location_on_the_Z_axis:
			str= "light_source_i_location_on_the_Z_axis";
			break;
		case ScenarioFeatureType::light_source_i_range:
			str= "light_source_i_range";
			break;
		case ScenarioFeatureType::light_source_i_direction_on_X_axis:
			str= "light_source_i_direction_on_X_axis";
			break;
		case ScenarioFeatureType::light_source_i_direction_on_Y_axis:
			str= "light_source_i_direction_on_Y_axis";
			break;
		case ScenarioFeatureType::light_source_i_light_cone:
			str= "light_source_i_light_cone";
			break;
	}
	return str;
}

void  ScenarioFeatureType::operator= (ScenarioFeatureTypeE newType)
{
	this->_type=newType;
}


bool ScenarioFeatureType::operator==(const ScenarioFeatureType& lhs)
{
	return _type ==lhs._type;
}

bool ScenarioFeatureType::operator!=(const ScenarioFeatureType& lhs)
{
	return !operator==(lhs);
}

bool operator< (const ScenarioFeatureType& lhs, const ScenarioFeatureType& rhs)
{
	return lhs._type<rhs._type;
}
bool operator> (const ScenarioFeatureType& lhs, const ScenarioFeatureType& rhs)
{
	return operator< (rhs,lhs);
}



std::ostream& operator<<(std::ostream& os, const ScenarioFeatureType& dt)
{
	os<< ScenarioFeatureType::toString(dt);
	return os;
}
