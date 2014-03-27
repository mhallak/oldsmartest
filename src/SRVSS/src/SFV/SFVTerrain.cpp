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

void SFVTerrain::setRolledValue(RolledValue * value)
{
	switch(value->getType()._type)
	{
		case ScenarioFeatureType::topographic_map:
			setId(value->getRollNumber());
			setTerrainId(value->getValue());
	}
}

TiXmlElement * SFVTerrain::toXMLElement()
{
	std::stringstream ss;
	TiXmlElement * terrain= new TiXmlElement( "terrain" );
	ss << getId();
	terrain->SetAttribute("id",ss.str());
	ss.str("");
	TiXmlElement * terrainId= new TiXmlElement( "terrainId" );
	ss << getTerrainId();
	TiXmlText * terrainIdVal= new TiXmlText( ss.str() );
	ss.str("");
	terrainId->LinkEndChild(terrainIdVal);
	terrain->LinkEndChild(terrainId);
	return terrain;
}

void SFVTerrain::fromXMLElement(TiXmlElement * xmlElement)
{
	TiXmlNode* pChild;
	TiXmlAttribute* pAttrib;

	for ( pAttrib = xmlElement->ToElement()->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
	{
		if(pAttrib->NameTStr().compare("id")==0)
		{
			setId(atoi(pAttrib->ValueStr().c_str()));
		}
	}

	for ( pChild = xmlElement->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("terrainId")==0){
			setTerrainId(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
	}
}

SFVTerrain::~SFVTerrain() {
	// TODO Auto-generated destructor stub
}

