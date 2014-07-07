/*
 * ScenarioFeature.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#include "SFDP/ScenarioFeature.h"
#include <string>
#include <stdlib.h>
#include <tinyxml.h>
#include <string>

ScenarioFeature::ScenarioFeature(std::string featureType):
	m_featureType(ScenarioFeatureType::parseString(featureType.c_str())),
	m_distType(ScenarioFeatureDistributionType::unknown_distribution),
	m_dist_param_1(0),
	m_dist_param_2(0)
{
}

ScenarioFeature::ScenarioFeature(ScenarioFeature * source_ScenarioFeature)
{
	m_featureType=source_ScenarioFeature->get_featureType();
	m_distType=source_ScenarioFeature->get_distType();
	m_dist_param_1=source_ScenarioFeature->get_dist_param_1();
	m_dist_param_2=source_ScenarioFeature->get_dist_param_2();
}

ScenarioFeature::~ScenarioFeature()
{
}


ScenarioFeatureType ScenarioFeature::ScenarioFeature::get_featureType()
{
	return m_featureType;
}

ScenarioFeatureDistributionType ScenarioFeature::get_distType()
{
	return m_distType;
}

float ScenarioFeature::get_dist_param_1()
{
	return m_dist_param_1;
}

float ScenarioFeature::get_dist_param_2()
{
	return m_dist_param_2;
}


void ScenarioFeature::set_dist_param_1(float val)
{
	m_dist_param_1=val;
}


void ScenarioFeature::set_dist_param_2(float val)
{
	m_dist_param_2=val;
}

void ScenarioFeature::set_featureType(ScenarioFeatureType type)
{
	m_featureType=type;
}


void ScenarioFeature::set_distributionType(ScenarioFeatureDistributionType type)
{
	m_distType=type;
}



/*
void parseScenarioFeature(ScenarioFeature *feature,TiXmlNode* xmlNode) throw (std::string)
{
	TiXmlNode* pChild;
	std::string distribution;
	std::string dist_param_1;
	std::string dist_param_2;

	bool distributionFound=false;
	bool dist_param_1Found=false;
	bool dist_param_2Found=false;

	for ( pChild = xmlNode->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("distribution")==0){
			distribution=pChild->FirstChild()->ToText()->ValueStr();
			distributionFound=true;
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("dist_param_1")==0){
			dist_param_1=pChild->FirstChild()->ToText()->ValueStr();
			dist_param_1Found=true;
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("dist_param_2")==0){
			dist_param_2=pChild->FirstChild()->ToText()->ValueStr();
			dist_param_2Found=true;
		}
	}
	if(distributionFound && dist_param_1Found && dist_param_2Found){
		feature->set_distributionType(ScenarioFeatureDistributionType::parseString(distribution.c_str()));
		feature->set_dist_param_1(atof(dist_param_1.c_str()));
		feature->set_dist_param_2(atof(dist_param_2.c_str()));
	}else{
		throw "feature not complete!, missing distribution,dist_param_1 or dist_param_2";
	}
}
*/


TiXmlElement *ScenarioFeature::toXMLElement()
{
	TiXmlElement * xml_feature= new TiXmlElement("scenario_feature");
	xml_feature->SetAttribute("type",m_featureType.str());

		TiXmlElement * xml_dist= new TiXmlElement("distribution");
		TiXmlText * dist_val= new TiXmlText( m_distType.str() );
		xml_dist->LinkEndChild(dist_val);
		xml_feature->LinkEndChild(xml_dist);


		std::stringstream temp_ss;
		temp_ss.str("");
		temp_ss << m_dist_param_1;
		TiXmlElement * xml_dp1= new TiXmlElement("dist_param_1");
		TiXmlText * dp1_val= new TiXmlText( temp_ss.str() );
		xml_dp1->LinkEndChild(dp1_val);
		xml_feature->LinkEndChild(xml_dp1);

		temp_ss.str("");
		temp_ss << m_dist_param_2;
		TiXmlElement * xml_dp2= new TiXmlElement("dist_param_2");
		TiXmlText * dp2_val= new TiXmlText( temp_ss.str() );
		xml_dp2->LinkEndChild(dp2_val);
		xml_feature->LinkEndChild(xml_dp2);

	return(xml_feature);
}

