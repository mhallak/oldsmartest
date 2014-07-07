/*
 * ScenarioFeatureGroup.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#include "SFDP/ScenarioFeatureGroup.h"
#include <string>
#include <stdlib.h>
#include <tinyxml.h>


ScenarioFeatureGroup::ScenarioFeatureGroup() :
m_featureGroupType(ScenarioFeatureGroupType::unknown_feature_group)
{
	m_name="";
	m_features=(new std::vector<ScenarioFeature *>);
}
ScenarioFeatureGroup::ScenarioFeatureGroup(std::string featureType):
	m_featureGroupType(ScenarioFeatureGroupType::parseString(featureType.c_str()))
{
	m_features=(new std::vector<ScenarioFeature *>);
	m_name="";
	set_featureGroupType(ScenarioFeatureGroupType::parseString(featureType.c_str()));
}

ScenarioFeatureGroup::ScenarioFeatureGroup(ScenarioFeatureGroup * source_ScenarioFeatureGroup)
{
	m_name = source_ScenarioFeatureGroup->m_name;
	m_featureGroupType = source_ScenarioFeatureGroup->m_featureGroupType;
	m_features=(new std::vector<ScenarioFeature *>);

	ScenarioFeature * feature_temp;
	for (ScenarioFeature * feature_it : *(source_ScenarioFeatureGroup->get_features()) )
	{
		feature_temp = new ScenarioFeature(feature_it);
		m_features->push_back(feature_temp);
	}
}

ScenarioFeatureGroup::~ScenarioFeatureGroup()
{
	delete m_features;
}


ScenarioFeatureGroupType ScenarioFeatureGroup::get_featureGroupType()
{
	return m_featureGroupType;
}
void ScenarioFeatureGroup::set_featureGroupType(ScenarioFeatureGroupType type)
{
	m_featureGroupType=type;
}

std::string ScenarioFeatureGroup::get_name()
{
	return m_name;
}

void ScenarioFeatureGroup::set_name(std::string name)
{
	m_name=name;
}

std::vector<ScenarioFeature*> * ScenarioFeatureGroup::get_features()
{
	return m_features;
}

void ScenarioFeatureGroup::addFeature(ScenarioFeature* feature)
{
	m_features->push_back(feature);
}



TiXmlElement *ScenarioFeatureGroup::toXMLElement()
{
	TiXmlElement * xml_featureRroup= new TiXmlElement("scenario_feature_group");
	xml_featureRroup->SetAttribute("type",m_featureGroupType.str());
	xml_featureRroup->SetAttribute("name",m_featureGroupType.str());
	for (ScenarioFeature * feat_it : * m_features )
	{
		xml_featureRroup->LinkEndChild(feat_it->toXMLElement());
	}
	return(xml_featureRroup);
}

