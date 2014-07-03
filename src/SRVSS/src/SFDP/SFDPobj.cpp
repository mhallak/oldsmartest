/*
 * SFDPobj.cpp
 *
 *  Created on: Jul 1, 2014
 *      Author: userws3
 */

#include "SFDP/SFDPobj.h"
#include "SFDP/SFDPParser.h"

#include <string>
#include <vector>

#include <iostream>



SFDPobj::SFDPobj(std::string SFDP_file_url, std::string Resources_file_url, std::string WS_url, int division_level)
{
	my_SFDP_file_url = SFDP_file_url;
	my_Resources_file_url = Resources_file_url;
	my_WS_url = WS_url;
	my_division_level = division_level;
	have_been_run = false;

	my_featureGroups = new std::vector<ScenarioFeatureGroup*>;
	my_sampled_SFVs = new std::vector<SFVComponent *>;
	my_sub_SFDPs = new std::vector<SFDPobj *>;
}


int SFDPobj::ParseMeFromFile(std::string SFDP_file_url)
{
	SFDPParser * SFDPpars = new SFDPParser;
	try {
		my_featureGroups = SFDPpars->genFeatureGroupVectorFromFile(SFDP_file_url);
		}
	catch(std::string err)
		{
		std::cout << err << std::endl;
		return 1;
		}

	return 0;
}

int SFDPobj::PrintMeToFile(std::string SFDP_filename)
{
	TiXmlElement * xml_SFDP = new TiXmlElement( "SFDP" );
	xml_SFDP->SetAttribute("version","1.0");

	for (ScenarioFeatureGroup * group_it : * my_featureGroups )
		{
		xml_SFDP->LinkEndChild(group_it->toXMLElement());
		}

	std::string file_url = my_WS_url+SFDP_filename;
	TiXmlDocument doc(file_url);
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild(decl);

	doc.LinkEndChild(xml_SFDP);
	doc.SaveFile(file_url.c_str());

	std::cout << " printing to file : " << file_url << std::endl;

	return 0;
}



int SFDPobj::GenMySFVs(int samp_num)
{
	SFVComponent * sfvComp;
	std::string file_url;

	int success;
	int success_num=0;
	int sfv_index=1;

	for (int i=1 ; i<=samp_num ; i++ )
	{
		file_url = my_WS_url + "SFV_" + std::to_string(sfv_index);

		sfvComp = genSFVComp();
		if (  sfvComp )
			{
			my_sampled_SFVs->push_back(sfvComp);
			success_num++;
			sfvComp->genFileFromSFV(file_url);
			sfv_index++;
			}
	}

	std::cout << "success in rolling " << success_num << "/" << samp_num << " SFVs " << std::endl;

	if (success_num == samp_num)
		return 1;
	else
		return 0;

}


SFVComponent* SFDPobj::genSFVComp()
{
	SFVComponent * sfvComp = new SFVComponent(my_Resources_file_url);

	for (ScenarioFeatureGroup * group_it : * my_featureGroups )
	{
		std::map<ScenarioFeatureType,DPObject*> *dpMap=new std::map<ScenarioFeatureType,DPObject*>;

		for(ScenarioFeature* feat_it : *(group_it->get_features()) )
		{
			(*dpMap)[feat_it->get_featureType()]=(new DPObject(feat_it));
		}

		sfvComp->addDPObjects( group_it->get_featureGroupType()  ,  new DPGroup(group_it->get_name(),  group_it->get_featureGroupType(),dpMap));
	}

	sfvComp->init();
	if (sfvComp->calc())
		return sfvComp;
	else
		return 0;
}
