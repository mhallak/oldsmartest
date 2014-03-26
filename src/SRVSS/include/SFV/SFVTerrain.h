/*
 * SFVTerrain.h
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#ifndef SFVTERRAIN_H_
#define SFVTERRAIN_H_
#include "SFV/SFVInterface.h"
#include "utils/ParsableInterface.h"

class SFVTerrain: public SFVInterface, public ParsableInterface{
	int m_Id;
	int m_TerrainId;
public:
	SFVTerrain();
	virtual ~SFVTerrain();
	void setRolledValue(RolledValue * value);
	TiXmlElement *toXMLElement();
	void fromXMLElement(TiXmlElement * node);
	int getId() const;
	void setId(int id);
	int getTerrainId() const;
	void setTerrainId(int terrainId);
};

#endif /* SFVTERRAIN_H_ */
