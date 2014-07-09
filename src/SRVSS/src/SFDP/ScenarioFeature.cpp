/*
 * ScenarioFeature.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#include "SFDP/ScenarioFeature.h"
#include "utils/TinyXmlDef.h"

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

ScenarioFeature::ScenarioFeature():
	m_featureType(ScenarioFeatureType::unknown_feature),
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




int ScenarioFeature::parseScenarioFeatureFromXML(TiXmlNode* xmlFeature)
{
	if (! (xmlFeature->ValueStr().compare("scenario_feature")==0))
	{
		std::cout <<  " could not parse " << xmlFeature->ValueStr() << " because it is not a Scenario Feature " << std::endl;
		return 0;
	}

	std::string FeatureType = "";
	std::string distribution = "";
	std::string dist_param_1 = "";
	std::string dist_param_2 = "";

	FeatureType = xmlFeature->ToElement()->FirstAttribute()->ValueStr();

	TiXmlNode* pChild;
	for ( pChild = xmlFeature->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("distribution")==0){
			distribution=pChild->FirstChild()->ToText()->ValueStr();
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("dist_param_1")==0){
			dist_param_1=pChild->FirstChild()->ToText()->ValueStr();
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("dist_param_2")==0){
			dist_param_2=pChild->FirstChild()->ToText()->ValueStr();
		}
	}

	if ( (FeatureType=="" ) || (distribution=="") || (dist_param_1=="") || (dist_param_2=="") )
	{
		std::cout <<  " could not parse " << xmlFeature->ValueStr() << " = " << FeatureType << " its type, distribution, or distribution parameters are not valid " << std::endl;
		return 0;
	}

		m_featureType = ScenarioFeatureType::parseString(FeatureType.c_str());
		m_distType = ScenarioFeatureDistributionType::parseString(distribution.c_str());
		m_dist_param_1 = atof(dist_param_1.c_str());
		m_dist_param_2 = atof(dist_param_2.c_str());

	return 1;
}



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

