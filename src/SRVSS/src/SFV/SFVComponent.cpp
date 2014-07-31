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
#include "Rules/RULE_wp_path_inside_map.h"
#include "Rules/RULE_platform_init_pose_with_no_obj_colisions.h"
#include "SFV/SFVGeneric.h"
#include <boost/foreach.hpp>

#include <iostream>


SFVComponent::SFVComponent(std::string resource_file_path) {

	m_DPObjectMap=new std::map<ScenarioFeatureGroupType,std::vector<DPGroup*>*>;

	m_massLinks=new std::vector<SFVMassLink *>;
	m_frictionLinks=new std::vector<SFVFrictionLink *>;
	m_sensorLinks=new std::vector<SFVSensorLink *>;
	m_objects=new std::vector<SFVObjects *>;
	m_obstaclesOnPath=new std::vector<SFVObstaclesOnPath *>;
	m_lights=new std::vector<SFVLights *>;
	m_terrains=new std::vector<SFVTerrain*>;
	m_platformPoses=new std::vector<SFVPlatformPose*>;
	m_paths=new std::vector<SFVPath*>;

	m_rules=new std::vector<Rule*>;
	m_rules->push_back(new Rule_wp_path_inside_map);
	m_rules->push_back(new Rule_platform_init_pose_with_no_obj_colisions);

	m_resource_file_path = resource_file_path;
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
	initAUX<SFVObstaclesOnPath>(ScenarioFeatureGroupType::obstacles_on_path,m_obstaclesOnPath);
	initAUX<SFVLights>(ScenarioFeatureGroupType::lights,m_lights);
	initAUX<SFVMassLink>(ScenarioFeatureGroupType::mass_link_i,m_massLinks);
	initAUX<SFVFrictionLink>(ScenarioFeatureGroupType::friction_link_i,m_frictionLinks);
	initAUX<SFVSensorLink>(ScenarioFeatureGroupType::sensor_link_i,m_sensorLinks);
	initAUX<SFVPlatformPose>(ScenarioFeatureGroupType::platform_pose,m_platformPoses);
	initAUX<SFVPath>(ScenarioFeatureGroupType::waypoints,m_paths);
}


template<class T>
void SFVComponent::rollAUX(std::vector<T*> * vec,bool & state)
{
	if(!state)
		return;
	for(auto  tr : *vec)
	    {
		state = tr->calc(this);
	    if (! state)
	    	break;
	    }
}


bool SFVComponent::calc()
{
	std::cout << " ######## starting roll of SFV ######## " << std::endl;
	bool roll_success = true;

	rollAUX(m_terrains,roll_success);
	rollAUX(m_objects,roll_success);
	rollAUX(m_lights,roll_success);
	rollAUX(m_massLinks,roll_success);
	rollAUX(m_frictionLinks,roll_success);
	rollAUX(m_sensorLinks,roll_success);
	rollAUX(m_platformPoses,roll_success);
	rollAUX(m_paths,roll_success);
	rollAUX(m_obstaclesOnPath,roll_success);

	m_paths->at(0)->getPathLength();

    std::cout << " ######## ending roll of SFV ######## success = " << roll_success << std::endl;

    return roll_success;
}


bool  SFVComponent::checkRules(){
	bool ans=true;
	std::cout << " !! checking rules : " << std::endl;
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

std::vector<SFVObstaclesOnPath*>* SFVComponent::getObstaclesOnPath()
{
	return m_obstaclesOnPath;
}

std::vector<SFVTerrain*>* SFVComponent::getTerrains()
{
	return m_terrains;
}

std::vector<SFVPlatformPose*> * SFVComponent::getPlatformPoses()
{
	return m_platformPoses;
}
std::vector<SFVPath*> * SFVComponent::getPaths()
{
	return m_paths;
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
	for(auto  tr : *m_terrains)  	  	 { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_objects)   	  	 { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_obstaclesOnPath)  { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_lights)   	 	 { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_massLinks) 	 	 { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_frictionLinks)	 { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_sensorLinks)   	 { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_platformPoses) 	 { element->LinkEndChild(tr->toXMLElement()); }
	for(auto  tr : *m_paths)     	     { element->LinkEndChild(tr->toXMLElement()); }

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
					case ScenarioFeatureGroupType::obstacles_on_path:
					{
						fromXMLElementAUX<SFVObstaclesOnPath>("Generic",pChild->ToElement(),getObstaclesOnPath());
					}
					break;
					case ScenarioFeatureGroupType::lights:
					{
						fromXMLElementAUX<SFVLights>("Generic",pChild->ToElement(),getLights());
					}
					break;
					case ScenarioFeatureGroupType::waypoints:
					{
						fromXMLElementAUX<SFVPath>("Generic",pChild->ToElement(),getPaths());
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

int SFVComponent::genSFVFromFile(std::string filename) throw (std::string)
{
	TiXmlDocument *SFVfile = new TiXmlDocument(filename);
	if (!SFVfile->LoadFile())
	{
		std::cout << " failed to load file : " << filename << " it might not exist or be not valid XML " << std::endl;
		return 0;
	}

	TiXmlNode* pChild;
	//search for an sfv element to parse
	for ( pChild = SFVfile->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("sfv")==0)
		{
			fromXMLElement(pChild->ToElement());
			break;
		}
	}
	return 1;
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

