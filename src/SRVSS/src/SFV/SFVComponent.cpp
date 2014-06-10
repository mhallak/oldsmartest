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
#include "Rules/TerrainBoundsRule.h"
#include "SFV/SFVGeneric.h"
#include <boost/foreach.hpp>


SFVComponent::SFVComponent() {
	m_DPObjectMap=new std::map<ScenarioFeatureGroupType,std::vector<DPGroup*>*>;
	m_massLinks=new std::vector<SFVMassLink *>;
	m_frictionLinks=new std::vector<SFVFrictionLink *>;
	m_sensorLinks=new std::vector<SFVSensorLink *>;
	m_objects=new std::vector<SFVObjects *>;
	m_lights=new std::vector<SFVLights *>;
	m_terrains=new std::vector<SFVTerrain*>;
	m_platformPoses=new std::vector<SFVPlatformPose*>;
	m_waypoints=new std::vector<SFVWaypoints *>;
	m_rules=new std::vector<Rule*>;
	m_rules->push_back(new TerrainBoundsRule);
}

template<class T>
void SFVComponent::initAUX(ScenarioFeatureGroupType type,std::vector<T*> * vec)
{
	if(m_DPObjectMap->find(type)!=m_DPObjectMap->end())
	{
		for(auto it:*(*m_DPObjectMap)[type])
		{
			vec->push_back(new T(it));
		}
	}
}

void SFVComponent::init()
{
	initAUX<SFVTerrain>(ScenarioFeatureGroupType::map,m_terrains);
	initAUX<SFVObjects>(ScenarioFeatureGroupType::objects,m_objects);
	initAUX<SFVLights>(ScenarioFeatureGroupType::lights,m_lights);
	initAUX<SFVMassLink>(ScenarioFeatureGroupType::mass_link_i,m_massLinks);
	initAUX<SFVFrictionLink>(ScenarioFeatureGroupType::friction_link_i,m_frictionLinks);
	initAUX<SFVSensorLink>(ScenarioFeatureGroupType::sensor_link_i,m_sensorLinks);
	initAUX<SFVPlatformPose>(ScenarioFeatureGroupType::platform_pose,m_platformPoses);
	initAUX<SFVWaypoints>(ScenarioFeatureGroupType::waypoints,m_waypoints);
}

bool SFVComponent::calc()
{
	for(auto  tr : *m_terrains)  	  { tr->calc(this); }
	for(auto  tr : *m_objects)   	  { tr->calc(this); }
	for(auto  tr : *m_lights)   	  { tr->calc(this); }
	for(auto  tr : *m_massLinks) 	  { tr->calc(this); }
	for(auto  tr : *m_frictionLinks) { tr->calc(this); }
	for(auto  tr : *m_sensorLinks)   { tr->calc(this); }
	for(auto  tr : *m_platformPoses) { tr->calc(this); }
	for(auto  tr : *m_waypoints)     { tr->calc(this); }
	return true;
}

bool  SFVComponent::checkRules(){
	bool ans=true;
	for(auto tr : *m_rules)
	{
		ans=tr->isRuleValid(this);
		if(!ans)
		{
			break;
		}
	}
	return ans;
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

std::vector<SFVLights*>* SFVComponent::getLights()
{
	return m_lights;
}

std::vector<SFVObjects*>* SFVComponent::getObjects()
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
std::vector<SFVWaypoints*> * SFVComponent::getWaypoints()
{
	return m_waypoints;
}

void SFVComponent::addTerrain(SFVTerrain* terrain) {
	m_terrains->push_back(terrain);
}

void SFVComponent::addDPObjects(ScenarioFeatureGroupType groupType,DPGroup* values)
{
	std::map<ScenarioFeatureGroupType,std::vector<DPGroup*>*> ::iterator it;
	it=m_DPObjectMap->find(groupType);
	if(it == m_DPObjectMap->end())
	{
		((*m_DPObjectMap)[groupType])=new std::vector<DPGroup*>;
	}
	((*m_DPObjectMap)[groupType])->push_back(values);
}

TiXmlElement *SFVComponent::toXMLElement()
{
	TiXmlElement * element = new TiXmlElement( "sfv" );
	element->SetAttribute("version","1.0");
	for(auto  tr : *m_terrains)  	  { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_objects)   	  { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_lights)   	  { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_massLinks) 	  { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_frictionLinks) { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_sensorLinks)   { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_platformPoses) { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_waypoints)     { element->LinkEndChild(tr->toXMLElement()); }

	return element;
}
void SFVComponent::fromXMLElement(TiXmlElement * node)
{
	TiXmlNode* pChild;
	TiXmlAttribute* pAttrib;
	//search for an sdfp element to parse
	for ( pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT)
		{
			fromXMLElementAUX<SFVTerrain>("Terrain",pChild->ToElement(),getTerrains());
			fromXMLElementAUX<SFVMassLink>("MassLink",pChild->ToElement(),getMassLinks());
			fromXMLElementAUX<SFVFrictionLink>("FrictionLink",pChild->ToElement(),getFrictionLinks());
			fromXMLElementAUX<SFVSensorLink>("SensorLink",pChild->ToElement(),getSensorLinks());
			fromXMLElementAUX<SFVPlatformPose>("PlatformPose",pChild->ToElement(),getPlatformPoses());

			if(pChild->ValueStr().compare("Generic")==0)
			{
				ScenarioFeatureGroupType type;
				for ( pAttrib = pChild->ToElement()->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
				{
					if(pAttrib->NameTStr().compare("type")==0)
					{
						type=ScenarioFeatureGroupType::parseString(pAttrib->Value());
					}
				}
				switch(type.index())
				{
					case ScenarioFeatureGroupType::objects:
					{
						fromXMLElementAUX<SFVObjects>("Generic",pChild->ToElement(),getObjects());
					}
					break;
					case ScenarioFeatureGroupType::lights:
					{
						fromXMLElementAUX<SFVLights>("Generic",pChild->ToElement(),getLights());
					}
					break;
					case ScenarioFeatureGroupType::waypoints:
					{
						fromXMLElementAUX<SFVWaypoints>("Generic",pChild->ToElement(),getWaypoints());
					}
					break;
				}
			}
		}
	}
}

template<class T>
void SFVComponent::fromXMLElementAUX(std::string text,TiXmlElement * node,std::vector<T*> * vec)
{
	if(node->ValueStr().compare(text)==0)
	{
		std::string name;
		TiXmlAttribute* pAttrib;
		for ( pAttrib = node->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
		{
			if(pAttrib->NameTStr().compare("name")==0)
			{
				name=pAttrib->ValueStr();
			}
		}
		T *obj = new T(new DPGroup(name,ScenarioFeatureGroupType::unknown_feature_group,new std::map<ScenarioFeatureType,DPObject *>));
		obj->fromXMLElement(node);
		vec->push_back(obj);
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

