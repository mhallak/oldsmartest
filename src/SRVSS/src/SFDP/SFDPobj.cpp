/*
 * SFDPobj.cpp
 *
 *  Created on: Jul 1, 2014
 *      Author: userws3
 */

#include "SFDP/SFDPobj.h"
#include "SFDP/SFDPParser.h"
#include "Generators/Gazebo/GazeboScenarioGenerator.h"


#include <string>
#include <vector>

#include <iostream>

#include <boost/filesystem.hpp>



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

int SFDPobj::PrintMeToFile()
{
	TiXmlElement * xml_SFDP = new TiXmlElement( "SFDP" );
	xml_SFDP->SetAttribute("version","1.0");

	for (ScenarioFeatureGroup * group_it : * my_featureGroups )
		{
		xml_SFDP->LinkEndChild(group_it->toXMLElement());
		}


	TiXmlDocument doc(my_SFDP_file_url);
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild(decl);

	doc.LinkEndChild(xml_SFDP);
	doc.SaveFile(my_SFDP_file_url.c_str());

	std::cout << " printing to file : " << my_SFDP_file_url << std::endl;

	return 0;
}



int SFDPobj::GenMySFVs(int samp_num)
{
	my_sampled_SFVs = new std::vector<SFVComponent *>;

	SFVComponent * sfvComp;
	std::string file_url;

	int success;
	int success_num=0;
	int sfv_index=1;

	for (int i=1 ; i<=samp_num ; i++ )
	{

		std::string folder_url = my_WS_url + "sampl_" + std::to_string(sfv_index);
		file_url = folder_url + "/scen.SFV";


		boost::filesystem::remove_all(folder_url);
		if(! boost::filesystem::create_directory(folder_url))
			{
			std::cout << "failed to create folder for sfv_" << sfv_index << std::endl;
			break;
			}

		sfvComp = genSFVComp();
		if ( ! sfvComp )
			{
			std::cout << "failed to generate sfv_ " << sfv_index << std::endl;
			break;
			}

			my_sampled_SFVs->push_back(sfvComp);
			success_num++;
			sfvComp->genFileFromSFV(file_url);
			sfv_index++;

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


int SFDPobj::RunMySFVs()
{
	GazeboScenarioGenerator * ScenGen=new GazeboScenarioGenerator();

	std::string folder_url;
	int sfv_index=1;

	for (SFVComponent * sfvComp_it : * my_sampled_SFVs )
	{
		folder_url = my_WS_url + "sampl_" + std::to_string(sfv_index) + "/";

		if(! boost::filesystem::is_directory(folder_url))
			{
			std::cout << " failed to locate folder of sampl_" << std::to_string(sfv_index) << std::endl;
			break;
			}

     	ScenGen->GenerateScenario(sfvComp_it, folder_url, my_Resources_file_url);
     	sfv_index++;
	}
}


int SFDPobj::SplitkMe(ScenarioFeatureType FeatureToSplit, float split_percents)
{
	SFDPobj * sub_sfdp1;
	SFDPobj * sub_sfdp2;

	std::string sub_sfdp_1_WS_url = my_WS_url + "sub_sfdp1/";
	sub_sfdp1 = new SFDPobj(sub_sfdp_1_WS_url+"sub_sfdp",my_Resources_file_url,sub_sfdp_1_WS_url,my_division_level+1);
	sub_sfdp1->set_FeatureGroups(this->get_FeatureGroups());


	std::string sub_sfdp_2_WS_url = my_WS_url + "sub_sfdp2";
	sub_sfdp2 = new SFDPobj(sub_sfdp_2_WS_url+"sub_sfdp",my_Resources_file_url,sub_sfdp_2_WS_url,my_division_level+1);
	sub_sfdp2->set_FeatureGroups(this->get_FeatureGroups());



	boost::filesystem::remove_all(sub_sfdp_1_WS_url);
	if(! boost::filesystem::create_directory(sub_sfdp_1_WS_url))
		{
		std::cout << "failed to create folder for sub_sfdp_1_WS_url" << sub_sfdp_1_WS_url << std::endl;
		}
	else
		{
		sub_sfdp1->PrintMeToFile();
		}


	return 1;
}

