/*
 * SFVComponent.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#include "SFV/SFVComponent.h"
#include "SFDP/ScenarioFeatureType.h"
#include "SFV/SFVTerrain.h"
#include "SFV/SFVObject.h"
#include "SFV/SFVLight.h"

SFVComponent::SFVComponent() {
	m_massLinks=new std::vector<SFVMassLink *>;
	m_frictionLinks=new std::vector<SFVFrictionLink *>;
	m_sensorLinks=new std::vector<SFVSensorLink *>;
	m_objects=new std::vector<SFVObject *>;
	m_lights=new std::vector<SFVLight *>;
	m_terrains=new std::vector<SFVTerrain*>;
	m_platformPoses=new std::vector<SFVPlatformPose*>;
	m_waypoints=new std::vector<SFVWaypoint*>;
}

std::vector<SFVMassLink *>* SFVComponent::getMassLinks()
{
	return m_massLinks;
}

std::vector<SFVFrictionLink *>* SFVComponent::getFrictionLinks()
{
	return m_frictionLinks;
}

std::vector<SFVSensorLink *>* SFVComponent::getSensorLinks()
{
	return m_sensorLinks;
}

std::vector<SFVLight*>* SFVComponent::getLights()
{
	return m_lights;
}

std::vector<SFVObject*>* SFVComponent::getObjects()
{
	return m_objects;
}
std::vector<SFVTerrain*>* SFVComponent::getTerrains()
{
	return m_terrains;
}

std::vector<SFVPlatformPose*> * SFVComponent::getPlatformPoses()
{
	return m_platformPoses;
}
std::vector<SFVWaypoint*> * SFVComponent::getWaypoints()
{
	return m_waypoints;
}

void SFVComponent::addTerrain(SFVTerrain* terrain) {
	m_terrains->push_back(terrain);
}

void SFVComponent::addRolledValues(ScenarioFeatureGroup* group,std::vector<RolledValue*>* values)
{
	std::vector<RolledValue*>::iterator valueItter=values->begin();
	//add new objects if needed
	switch(group->get_featureGroupType()._type)
	{
		case ScenarioFeatureGroupType::map:
			m_terrains->push_back(new SFVTerrain);
			break;
		case ScenarioFeatureGroupType::objects:
		case ScenarioFeatureGroupType::lights:
			break;
		case ScenarioFeatureGroupType::mass_link_i:
			m_massLinks->push_back(new SFVMassLink);
			m_massLinks->back()->setLinkName(group->get_name());
			m_massLinks->back()->setId(m_massLinks->size()-1);
			break;
		case ScenarioFeatureGroupType::friction_link_i:
			m_frictionLinks->push_back(new SFVFrictionLink);
			m_frictionLinks->back()->setLinkName(group->get_name());
			m_frictionLinks->back()->setId(m_frictionLinks->size()-1);
			break;
		case ScenarioFeatureGroupType::sensor_link_i:
			m_sensorLinks->push_back(new SFVSensorLink);
			m_sensorLinks->back()->setLinkName(group->get_name());
			m_sensorLinks->back()->setId(m_sensorLinks->size()-1);
			break;
		case ScenarioFeatureGroupType::platform_pose:
			m_platformPoses->push_back(new SFVPlatformPose);
			m_platformPoses->back()->setPlatformName(group->get_name());
			m_platformPoses->back()->setId(m_platformPoses->size()-1);
			break;
	}
	//set values
	while(valueItter!=values->end())
	{
		switch((*valueItter)->getType()._type)
		{
			case ScenarioFeatureType::unknown_feature:
				break;
			case ScenarioFeatureType::topographic_map:
				m_terrains->back()->setRolledValue((*valueItter));
				break;
			case ScenarioFeatureType::number_of_objects:
				for(int i=0;i<(*valueItter)->getValue();i++)
				{
					m_objects->push_back(new SFVObject);
					m_objects->at(i)->setId(i);
				}
				break;
			case ScenarioFeatureType::object_i_type:
			case ScenarioFeatureType::object_i_scaling_factor:
			case ScenarioFeatureType::object_i_location_on_the_X_axis:
			case ScenarioFeatureType::object_i_location_on_the_Y_axis:
			case ScenarioFeatureType::object_i_location_on_the_Z_axis:
			case ScenarioFeatureType::object_i_location_Roll:
			case ScenarioFeatureType::object_i_location_Pitch:
			case ScenarioFeatureType::object_i_location_Yaw:
				m_objects->at((*valueItter)->getRollNumber())->setRolledValue((*valueItter));
				break;
			case ScenarioFeatureType::number_of_light_sources:
				for(int i=0;i<(*valueItter)->getValue();i++)
				{
					m_lights->push_back(new SFVLight);
					m_lights->at(i)->setId(i);
				}
				break;
			case ScenarioFeatureType::light_source_i_type:
			case ScenarioFeatureType::light_source_i_location_on_the_X_axis:
			case ScenarioFeatureType::light_source_i_location_on_the_Y_axis:
			case ScenarioFeatureType::light_source_i_location_on_the_Z_axis:
			case ScenarioFeatureType::light_source_i_range:
			case ScenarioFeatureType::light_source_i_direction_on_X_axis:
			case ScenarioFeatureType::light_source_i_direction_on_Y_axis:
			case ScenarioFeatureType::light_source_i_light_cone:
				m_lights->at((*valueItter)->getRollNumber())->setRolledValue((*valueItter));
				break;
			case ScenarioFeatureType::mass_link_i_mass:
			case ScenarioFeatureType::mass_link_i_inertia_Ixx_component:
			case ScenarioFeatureType::mass_link_i_inertia_Iyy_component:
			case ScenarioFeatureType::mass_link_i_inertia_Izz_component:
			case ScenarioFeatureType::mass_link_i_location_deviation_X:
			case ScenarioFeatureType::mass_link_i_location_deviation_Y:
			case ScenarioFeatureType::mass_link_i_location_deviation_Z:
			case ScenarioFeatureType::mass_link_i_location_deviation_Yaw:
			case ScenarioFeatureType::mass_link_i_location_deviation_Pitch:
			case ScenarioFeatureType::mass_link_i_location_deviation_Roll:
				m_massLinks->back()->setRolledValue((*valueItter));
				break;
			case ScenarioFeatureType::sensor_link_i_location_deviation_X:
			case ScenarioFeatureType::sensor_link_i_location_deviation_Y:
			case ScenarioFeatureType::sensor_link_i_location_deviation_Z:
			case ScenarioFeatureType::sensor_link_i_location_deviation_Yaw:
			case ScenarioFeatureType::sensor_link_i_location_deviation_Pitch:
			case ScenarioFeatureType::sensor_link_i_location_deviation_Roll:
				m_sensorLinks->back()->setRolledValue((*valueItter));
				break;
			case ScenarioFeatureType::friction_link_friction_deviation:
				m_frictionLinks->back()->setRolledValue((*valueItter));
				break;
			case ScenarioFeatureType::initial_platform_position_on_map_X_axis:
			case ScenarioFeatureType::initial_platform_position_on_map_Y_axis:
			case ScenarioFeatureType::initial_platform_azimut_on_map:
				m_platformPoses->back()->setRolledValue((*valueItter));
				break;
			case ScenarioFeatureType::number_of_way_points:
				for(int i=0;i<(*valueItter)->getValue();i++)
				{
					m_waypoints->push_back(new SFVWaypoint);
					m_waypoints->at(i)->setId(i);
				}
				break;
			case ScenarioFeatureType::wp_i_distance_i:
			case ScenarioFeatureType::relative_angle_teta:
			case ScenarioFeatureType::wp_velocity:
				m_waypoints->at((*valueItter)->getRollNumber())->setRolledValue((*valueItter));
				break;

			}
		valueItter++;
	}
}

TiXmlElement *SFVComponent::toXMLElement()
{
	TiXmlElement * element = new TiXmlElement( "sfv" );
	element->SetAttribute("version","1.0");
	for(size_t i=0;i<m_terrains->size();i++)
	{
		element->LinkEndChild(m_terrains->at(i)->toXMLElement());
	}
	for(size_t i=0;i<m_objects->size();i++)
	{
		element->LinkEndChild(m_objects->at(i)->toXMLElement());
	}
	for(size_t i=0;i<m_lights->size();i++)
	{
		element->LinkEndChild(m_lights->at(i)->toXMLElement());
	}
	for(size_t i=0;i<m_massLinks->size();i++)
	{
		element->LinkEndChild(m_massLinks->at(i)->toXMLElement());
	}
	for(size_t i=0;i<m_frictionLinks->size();i++)
	{
		element->LinkEndChild(m_frictionLinks->at(i)->toXMLElement());
	}
	for(size_t i=0;i<m_sensorLinks->size();i++)
	{
		element->LinkEndChild(m_sensorLinks->at(i)->toXMLElement());
	}
	for(size_t i=0;i<m_platformPoses->size();i++)
	{
		element->LinkEndChild(m_platformPoses->at(i)->toXMLElement());
	}
	for(size_t i=0;i<m_waypoints->size();i++)
	{
		element->LinkEndChild(m_waypoints->at(i)->toXMLElement());
	}
	return element;
}
void SFVComponent::fromXMLElement(TiXmlElement * node)
{
	TiXmlNode* pChild;
	TiXmlAttribute* pAttrib;
	//search for an sdfp element to parse
	for ( pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("terrain")==0)
		{
			SFVTerrain *terrain = new SFVTerrain;
			terrain->fromXMLElement(pChild->ToElement());
			getTerrains()->push_back(terrain);
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("object")==0)
		{
			SFVObject *object = new SFVObject;
			object->fromXMLElement(pChild->ToElement());
			getObjects()->push_back(object);
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("light")==0)
		{
			SFVLight *light = new SFVLight;
			light->fromXMLElement(pChild->ToElement());
			getLights()->push_back(light);
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("mass_link")==0)
		{
			SFVMassLink *mass_link = new SFVMassLink;
			mass_link->fromXMLElement(pChild->ToElement());
			getMassLinks()->push_back(mass_link);
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("friction_link")==0)
		{
			SFVFrictionLink *friction_link = new SFVFrictionLink;
			friction_link->fromXMLElement(pChild->ToElement());
			getFrictionLinks()->push_back(friction_link);
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("sensor_link")==0)
		{
			SFVSensorLink *sensor_link = new SFVSensorLink;
			sensor_link->fromXMLElement(pChild->ToElement());
			getSensorLinks()->push_back(sensor_link);
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("platform_pose")==0)
		{
			SFVPlatformPose*platform_pose = new SFVPlatformPose;
			platform_pose->fromXMLElement(pChild->ToElement());
			getPlatformPoses()->push_back(platform_pose);
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("waypoint")==0)
		{
			SFVWaypoint *waypoint = new SFVWaypoint;
			waypoint->fromXMLElement(pChild->ToElement());
			getWaypoints()->push_back(waypoint);
		}
	}
}

void SFVComponent::genFileFromSFV(std::string filename)
{

	TiXmlDocument doc(filename);
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild(decl);
	doc.LinkEndChild(toXMLElement());
	doc.SaveFile(filename.c_str());
}

void SFVComponent::genSFVFromFile(std::string filename) throw (std::string)
{
	TiXmlDocument doc(filename);
	if (!doc.LoadFile())
	{
		std::string error("Failed to load file \"");
		error+=filename;
		error+="\"\n";
		throw error;
	}
	TiXmlNode* pChild;
	//search for an sdfp element to parse
	for ( pChild = doc.FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("sfv")==0){
			fromXMLElement(pChild->ToElement());
			break;
		}
	}
}

SFVComponent::~SFVComponent() {
	for(size_t i=0;i<m_objects->size();i++)
	{
		delete m_objects->at(i);
	}
	for(size_t i=0;i<m_lights->size();i++)
	{
		delete m_lights->at(i);
	}
	//delete m_terrain;
}

