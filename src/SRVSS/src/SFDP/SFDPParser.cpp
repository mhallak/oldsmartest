/*
 * SDFPParser.cpp
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#include "SFDP/SFDPParser.h"
#include "SFDP/ScenarioFeature.h"

#include "utils/TinyXmlDef.h"
#include <stdio.h>

#include "SFDP/SFDPComponent.h"
#include "SFDP/SFDPobj.h"

#include <tinyxml.h>



SFDPParser::SFDPParser() {

}

SFDPParser::~SFDPParser() {
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
	}

	if(distributionFound && dist_param_1Found && dist_param_2Found)
	{
		feature->set_distributionType(ScenarioFeatureDistributionType::parseString(distribution.c_str()));
		feature->set_dist_param_1(atof(dist_param_1.c_str()));
		feature->set_dist_param_2(atof(dist_param_2.c_str()));
	}
	else
	{
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
				else{
					throw pAttrib->NameTStr()+" is not a valid scenario_feature type";
					}
				}
			}
		}
}


void parseSFDP(SFDPComponent *sdfpComp,TiXmlNode* xmlNode) throw (std::string)
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
					featureGroup->set_featureGroupType(ScenarioFeatureGroupType::parseString(pAttrib->Value()));
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

SFDPComponent * SFDPParser::genSFDPFromFile(std::string filename) throw (std::string)
{
	SFDPComponent * sdfpComp=new SFDPComponent;
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
			parseSFDP(sdfpComp,pChild);
			break;
		}
	}
	return sdfpComp;
}







void parseSFDPobjFeatureGroupsVector(std::vector <ScenarioFeatureGroup *> * ScenarioFeatureGroupsVector ,TiXmlNode* xmlNode)
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
					featureGroup->set_featureGroupType(ScenarioFeatureGroupType::parseString(pAttrib->Value()));
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
			ScenarioFeatureGroupsVector->push_back(featureGroup);
		}
	}
}



std::vector <ScenarioFeatureGroup *> * SFDPParser::genFeatureGroupVectorFromFile(std::string filename)  throw (std::string)
{
	std::vector <ScenarioFeatureGroup *> * ScenarioFeatureGroupsVector = new std::vector <ScenarioFeatureGroup *>;

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
			parseSFDPobjFeatureGroupsVector(ScenarioFeatureGroupsVector,pChild);
			break;
		}
	}
	return ScenarioFeatureGroupsVector;
}

