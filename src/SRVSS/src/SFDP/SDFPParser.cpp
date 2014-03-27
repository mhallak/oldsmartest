/*
 * SDFPParser.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#include "SFDP/SDFPParser.h"
#include "SFDP/SDFPComponent.h"
#include "SFDP/ScenarioFeature.h"
#include "utils/TinyXmlDef.h"
#include <stdio.h>




SDFPParser::SDFPParser() {

}

SDFPParser::~SDFPParser() {
}


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
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("feature_dependency")==0){
			TiXmlAttribute* pAttrib=pChild->ToElement()->FirstAttribute();
			if(pAttrib->NameTStr().compare("type")==0){
				ScenarioFeatureDependecy *dependecy=new ScenarioFeatureDependecy(pAttrib->ValueStr());
				dependecy->set_supportingFeatureType(ScenarioFeatureType::stringToFeatureType(pChild->FirstChild()->ToText()->ValueStr()));
				feature->addFeatureDependency(dependecy);
			}else{
				throw pAttrib->NameTStr()+" is not a valid scenario_feature type";
			}
		}
	}
	if(distributionFound && dist_param_1Found && dist_param_2Found){
		feature->set_distributionType(ScenarioFeatureDistributionType::stringToDistributionType(distribution));
		feature->set_dist_param_1(atof(dist_param_1.c_str()));
		feature->set_dist_param_2(atof(dist_param_2.c_str()));
	}else{
		throw "feature not complete!, missing distribution,dist_param_1 or dist_param_2";
	}
}






void parseScenarioFeatureGroup(ScenarioFeatureGroup *featureGroup,TiXmlNode* xmlNode) throw (std::string)
{
	TiXmlNode* pChild;

	TiXmlAttribute* pAttrib;
	//search for an sdfp element to parse
	for ( pChild = xmlNode->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
	if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("scenario_feature")==0)
	{
	ScenarioFeature *feature=0;
	for ( pAttrib = pChild->ToElement()->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
	{
	if(pAttrib->NameTStr().compare("type")==0)
	{
	feature=new ScenarioFeature(pAttrib->ValueStr());
	parseScenarioFeature(feature,pChild);
	featureGroup->addFeature(feature);
	}
	/*else if (pAttrib->NameTStr().compare("group")==0)
	{
	if(feature==0)
	throw std::string("type must be set before group");
	feature->set_group(pAttrib->ValueStr());
	}*/
	else{
	throw pAttrib->NameTStr()+" is not a valid scenario_feature type";
	}
	}
	}
	}
}


void parseSDFP(SDFPComponent *sdfpComp,TiXmlNode* xmlNode) throw (std::string)
{
	TiXmlNode* pChild;
	TiXmlAttribute* pAttrib;
	//search for an sdfp element to parse
	for ( pChild = xmlNode->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("scenario_feature_group")==0)
		{
			ScenarioFeatureGroup *featureGroup=new ScenarioFeatureGroup();
			for ( pAttrib = pChild->ToElement()->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
			{
				if(pAttrib->NameTStr().compare("type")==0)
				{
					featureGroup->set_featureGroupType(ScenarioFeatureGroupType::stringToFeatureGroupType(pAttrib->ValueStr()));
				}
				else if(pAttrib->NameTStr().compare("name")==0)
				{
					featureGroup->set_name(pAttrib->ValueStr());
				}
				else{
					throw pAttrib->NameTStr()+" is not a scenario_feature_group type";
				}
			}
			parseScenarioFeatureGroup(featureGroup,pChild);
			sdfpComp->addScenarioFeatureGroup(featureGroup);
		}
	}
}

SDFPComponent * SDFPParser::genSDFPFromFile(std::string filename) throw (std::string)
{
	SDFPComponent * sdfpComp=new SDFPComponent;
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
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("sfdp")==0){
			parseSDFP(sdfpComp,pChild);
			break;
		}
	}
	return sdfpComp;
}
