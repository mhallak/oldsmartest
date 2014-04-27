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
	else if(val.compare("mass_link_i_mass")==0)
	{
		return mass_link_i_mass;
	}
	else if(val.compare("mass_link_i_inertia_Ixx_component")==0)
	{
		return mass_link_i_inertia_Ixx_component;
	}
	else if(val.compare("mass_link_i_inertia_Iyy_component")==0)
	{
		return mass_link_i_inertia_Iyy_component;
	}
	else if(val.compare("mass_link_i_inertia_Izz_component")==0)
	{
		return mass_link_i_inertia_Izz_component;
	}
	else if(val.compare("mass_link_i_location_deviation_X")==0)
	{
		return mass_link_i_location_deviation_X;
	}
	else if(val.compare("mass_link_i_location_deviation_Y")==0)
	{
		return mass_link_i_location_deviation_Y;
	}
	else if(val.compare("mass_link_i_location_deviation_Z")==0)
	{
		return mass_link_i_location_deviation_Z;
	}
	else if(val.compare("mass_link_i_location_deviation_Roll")==0)
	{
		return mass_link_i_location_deviation_Roll;
	}
	else if(val.compare("mass_link_i_location_deviation_Pitch")==0)
	{
		return mass_link_i_location_deviation_Pitch;
	}
    else if(val.compare("mass_link_i_location_deviation_Yaw")==0)
	{
    	return mass_link_i_location_deviation_Yaw;
	}
    else if(val.compare("friction_link_friction_deviation")==0)
	{
    	return friction_link_friction_deviation;
	}
    else if(val.compare("sensor_link_i_location_deviation_X")==0)
	{
    	return sensor_link_i_location_deviation_X;
	}
    else if(val.compare("sensor_link_i_location_deviation_Y")==0)
	{
    	return sensor_link_i_location_deviation_Y;
	}
    else if(val.compare("sensor_link_i_location_deviation_Z")==0)
	{
    	return sensor_link_i_location_deviation_Z;
	}
    else if(val.compare("sensor_link_i_location_deviation_Roll")==0)
	{
    	return sensor_link_i_location_deviation_Roll;
	}
    else if(val.compare("sensor_link_i_location_deviation_Pitch")==0)
	{
    	return sensor_link_i_location_deviation_Pitch;
	}
    else if(val.compare("sensor_link_i_location_deviation_Yaw")==0)
	{
    	return sensor_link_i_location_deviation_Yaw;
	}
    else if(val.compare("initial_platform_position_on_map_X_axis")==0)
	{
    	return initial_platform_position_on_map_X_axis;
	}
    else if(val.compare("initial_platform_position_on_map_Y_axis")==0)
    {
    	return initial_platform_position_on_map_Y_axis;
    }
    else if(val.compare("initial_platform_azimut_on_map")==0)
    {
        return initial_platform_azimut_on_map;
    }
    else if(val.compare("number_of_way_points")==0)
    {
        return number_of_way_points;
    }
    else if(val.compare("wp_i_distance_i")==0)
    {
        return wp_i_distance_i;
   	}
    else if(val.compare("relative_angle_teta")==0)
    {
        return relative_angle_teta;
    }
    else if(val.compare("wp_velocity")==0)
    {
        return wp_velocity;
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
		case ScenarioFeatureType::mass_link_i_mass:
			str= "mass_link_i_mass";
			break;
		case ScenarioFeatureType::mass_link_i_inertia_Ixx_component:
			str= "mass_link_i_inertia_Ixx_component";
			break;
		case ScenarioFeatureType::mass_link_i_inertia_Iyy_component:
			str= "mass_link_i_inertia_Iyy_component";
			break;
		case ScenarioFeatureType::mass_link_i_inertia_Izz_component:
			str= "mass_link_i_inertia_Izz_component";
			break;
		case ScenarioFeatureType::mass_link_i_location_deviation_X:
			str= "mass_link_i_location_deviation_X";
			break;
		case ScenarioFeatureType::mass_link_i_location_deviation_Y:
			str= "mass_link_i_location_deviation_Y";
			break;
		case ScenarioFeatureType::mass_link_i_location_deviation_Z:
			str= "mass_link_i_location_deviation_Z";
			break;
		case ScenarioFeatureType::mass_link_i_location_deviation_Roll:
			str= "mass_link_i_location_deviation_Roll";
			break;
		case ScenarioFeatureType::mass_link_i_location_deviation_Pitch:
			str= "mass_link_i_location_deviation_Pitch";
			break;
		case ScenarioFeatureType::mass_link_i_location_deviation_Yaw:
			str= "mass_link_i_location_deviation_Yaw";
			break;
		case ScenarioFeatureType::friction_link_friction_deviation:
			str= "friction_link_friction_deviation";
			break;
		case ScenarioFeatureType::sensor_link_i_location_deviation_X:
			str= "sensor_link_i_location_deviation_X";
			break;
		case ScenarioFeatureType::sensor_link_i_location_deviation_Y:
			str= "sensor_link_i_location_deviation_Y";
			break;
		case ScenarioFeatureType::sensor_link_i_location_deviation_Z:
			str= "sensor_link_i_location_deviation_Z";
			break;
		case ScenarioFeatureType::sensor_link_i_location_deviation_Roll:
			str= "sensor_link_i_location_deviation_Roll";
			break;
		case ScenarioFeatureType::sensor_link_i_location_deviation_Pitch:
			str= "sensor_link_i_location_deviation_Pitch";
			break;
		case ScenarioFeatureType::sensor_link_i_location_deviation_Yaw:
			str= "sensor_link_i_location_deviation_Yaw";
			break;
		case ScenarioFeatureType::initial_platform_position_on_map_X_axis:
			str= "initial_platform_position_on_map_X_axis";
			break;
		case ScenarioFeatureType::initial_platform_position_on_map_Y_axis:
			str= "initial_platform_position_on_map_Y_axis";
			break;
		case ScenarioFeatureType::initial_platform_azimut_on_map:
			str= "initial_platform_azimut_on_map";
			break;
		case ScenarioFeatureType::number_of_way_points:
			str= "number_of_way_points";
			break;
		case ScenarioFeatureType::wp_i_distance_i:
			str= "wp_i_distance_i";
			break;
		case ScenarioFeatureType::relative_angle_teta:
			str= "relative_angle_teta";
			break;
		case ScenarioFeatureType::wp_velocity:
			str= "wp_velocity";
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
