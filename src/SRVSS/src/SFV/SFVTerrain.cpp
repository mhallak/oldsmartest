/*
 * SFVTerrain.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#include "SFV/SFVTerrain.h"

SFVTerrain::SFVTerrain(DPGroup * dpGroup): SFVBase(dpGroup)
{
	setStructure();
	init(dpGroup);
}

void SFVTerrain::setStructure()
{
	m_objectType="Terrain";
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::topographic_map,0));
}

int SFVTerrain::getId() const {
	return m_Id;
}

void SFVTerrain::setId(int id) {
	m_Id = id;
}

int SFVTerrain::getTerrainId() const {
	return m_objects->at(ScenarioFeatureType::topographic_map)->getResult();
}

void SFVTerrain::setTerrainId(int terrainId) {
	m_objects->at(ScenarioFeatureType::topographic_map)->setResult(terrainId);
}


SFVTerrain::~SFVTerrain() {
	// TODO Auto-generated destructor stub
}

