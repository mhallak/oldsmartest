/*
 * SFVTerrain.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#include "SFV/SFVTerrain.h"

SFVTerrain::SFVTerrain():
m_Id(-1),
m_TerrainId(-1)
{
}

int SFVTerrain::getId() const {
	return m_Id;
}

void SFVTerrain::setId(int id) {
	m_Id = id;
}

int SFVTerrain::getTerrainId() const {
	return m_TerrainId;
}

void SFVTerrain::setTerrainId(int terrainId) {
	m_TerrainId = terrainId;
}

SFVTerrain::~SFVTerrain() {
	// TODO Auto-generated destructor stub
}

