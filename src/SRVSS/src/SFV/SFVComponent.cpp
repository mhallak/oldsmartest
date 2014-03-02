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
	m_objects=new std::vector<SFVObject *>;
	m_lights=new std::vector<SFVLight *>;
	m_terrain=new SFVTerrain;
}

std::vector<SFVLight*>* SFVComponent::getLights()
{
	return m_lights;
}

std::vector<SFVObject*>* SFVComponent::getObjects()
{
	return m_objects;
}

void SFVComponent::addRolledValue(ScenarioFeatureType type, double rolledValue,
		int rolledID)
{
	switch(type._type)
	{
		case ScenarioFeatureType::unknown_feature:
			break;
		case ScenarioFeatureType::topographic_map:
			m_terrain->setId(rolledID);
			m_terrain->setTerrainId(rolledValue);
			break;
		case ScenarioFeatureType::number_of_objects:
			for(int i=0;i<rolledValue;i++)
			{
				m_objects->push_back(new SFVObject);
				m_objects->at(i)->setId(i);
			}
			break;
		case ScenarioFeatureType::object_i_type:
			m_objects->at(rolledID)->setType(rolledValue);
			break;
		case ScenarioFeatureType::object_i_scaling_factor:
			m_objects->at(rolledID)->setScale(rolledValue);
			break;
		case ScenarioFeatureType::object_i_location_on_the_X_axis:
			m_objects->at(rolledID)->setX(rolledValue);
			break;
		case ScenarioFeatureType::object_i_location_on_the_Y_axis:
			m_objects->at(rolledID)->setY(rolledValue);
			break;
		case ScenarioFeatureType::object_i_location_on_the_Z_axis:
			m_objects->at(rolledID)->setZ(rolledValue);
			break;
		case ScenarioFeatureType::object_i_location_Roll:
			m_objects->at(rolledID)->setRoll(rolledValue);
			break;
		case ScenarioFeatureType::object_i_location_Pitch:
			m_objects->at(rolledID)->setPitch(rolledValue);
			break;
		case ScenarioFeatureType::object_i_location_Yaw:
			m_objects->at(rolledID)->setYaw(rolledValue);
			break;
		case ScenarioFeatureType::number_of_light_sources:
			for(int i=0;i<rolledValue;i++)
			{
				m_lights->push_back(new SFVLight);
				m_lights->at(i)->setId(i);
			}
			break;
		case ScenarioFeatureType::light_source_i_type:
			m_lights->at(rolledID)->setType(rolledValue);
			break;
		case ScenarioFeatureType::light_source_i_location_on_the_X_axis:
			m_lights->at(rolledID)->setX(rolledValue);
			break;
		case ScenarioFeatureType::light_source_i_location_on_the_Y_axis:
			m_lights->at(rolledID)->setY(rolledValue);
			break;
		case ScenarioFeatureType::light_source_i_location_on_the_Z_axis:
			m_lights->at(rolledID)->setZ(rolledValue);
			break;
		case ScenarioFeatureType::light_source_i_range:
			m_lights->at(rolledID)->setRange(rolledValue);
			break;
		case ScenarioFeatureType::light_source_i_direction_on_X_axis:
			m_lights->at(rolledID)->setDirectionX(rolledValue);
			break;
		case ScenarioFeatureType::light_source_i_direction_on_Y_axis:
			m_lights->at(rolledID)->setDirectionY(rolledValue);
			break;
		case ScenarioFeatureType::light_source_i_light_cone:
			m_lights->at(rolledID)->setCone(rolledValue);
			break;

	}
}

SFVTerrain * SFVComponent::getTerrain()
{
	return m_terrain;
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
	delete m_terrain;
}

void SFVComponent::setTerrain(SFVTerrain* terrain) {
	delete m_terrain;
	m_terrain=terrain;
}
