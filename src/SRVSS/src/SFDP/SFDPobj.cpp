/*
 * SFDPobj.cpp
 *
 *  Created on: Jul 1, 2014
 *      Author: userws3
 */

#include "SFDP/SFDPobj.h"
#include "SFV/SFV.h"
#include "Generators/Gazebo/GazeboScenarioGenerator.h"
#include "Executor/GazeboExecutor.h"

#include <string>
#include <vector>

#include <iostream>

#include <boost/filesystem.hpp>

#include <cmath> //sqrt()

#include <tinyxml.h>
#include "utils/TinyXmlDef.h"



SFDPobj::SFDPobj(std::string SFDP_file_url, std::string Resources_file_url, std::string WS_url, int division_level)
{
	my_SFDP_file_url = SFDP_file_url;
	my_Resources_file_url = Resources_file_url;
	my_WS_url = WS_url;
	my_Grades_file_url = WS_url + "Grades.xml";
	my_division_level = division_level;
	have_been_run = false;

	my_featureGroups = new std::vector<ScenarioFeatureGroup*>;
	my_sampled_SFVs = new std::vector<SFV *>;
	my_sub_SFDPs = new std::vector<SFDPobj *>;
}


int SFDPobj::ParseMeFromXMLFile()
{
	TiXmlDocument *XMLfile = new TiXmlDocument(my_SFDP_file_url);
	if (!XMLfile->LoadFile())
	{
		std::cout << "\033[1;31m Failed to load file = " << my_SFDP_file_url << " it might not exist or be not valid XML \033[0m" << std::endl;
		return 0;
	}

	TiXmlNode* XMLfile_Child;
	for ( XMLfile_Child = XMLfile->FirstChild() ; XMLfile_Child != 0; XMLfile_Child = XMLfile_Child->NextSibling())
	{
		if ( (XMLfile_Child->Type()==XML_ELEMENT) && (XMLfile_Child->ValueStr().compare("sfdp")==0) )
		{
			break;
		}
	}

	if (XMLfile_Child == 0)
	{
		std::cout << "\033[1;31m Failed to parse SFDP file = " << my_SFDP_file_url << " it has no SFDP element \033[0m" << std::endl;
		return 0;
	}

	TiXmlNode* SFDP_Child;
	for ( SFDP_Child = XMLfile_Child->FirstChild() ; SFDP_Child != 0; SFDP_Child = SFDP_Child->NextSibling())
		{
			ScenarioFeatureGroup *featureGroup=new ScenarioFeatureGroup();
			if ( featureGroup->parseScenarioFeatureGroupFromXML(SFDP_Child) )
				{
				my_featureGroups->push_back(featureGroup);
				}
			else
				{
				std::cout << "\033[1;31m Failed to parse SFDP file = " << my_SFDP_file_url  << " one or more of it's Scenario Feature Groups is not valid \033[0m" << std::endl;
				return 0;
				}
		}
	return 1;
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
	my_sampled_SFVs = new std::vector<SFV *>;

	SFV * sfv_temp;
	std::string file_url;

	int success;
	int success_num=0;
	int sfv_index=1;

	for (int i=1 ; i<=samp_num ; i++ )
	{

		std::string folder_url = my_WS_url + "/sampl_" + std::to_string(sfv_index);
		file_url = folder_url + "/scen.SFV";


		boost::filesystem::remove_all(folder_url);
		if(! boost::filesystem::create_directory(folder_url))
			{
			std::cout << "\033[1;31m failed to create folder for sfv_" << sfv_index << "\033[0m"<< std::endl;
			break;
			}

		sfv_temp = new SFV(this);
		if ( ! sfv_temp )
			{
			std::cout << "\033[1;31m failed to Generate sfv_ " << sfv_index << "\033[0m" <<std::endl;
			break;
			}

		if (! sfv_temp->roll() )
			{
			std::cout << "\033[1;31m failed to Roll sfv_ " << sfv_index << "\033[0m" <<std::endl;
			break;
			}

			my_sampled_SFVs->push_back(sfv_temp);
			success_num++;
			sfv_temp->printToXML(file_url);
			sfv_index++;
	}

	std::cout << "success in rolling " << success_num << "/" << samp_num << " SFVs " << std::endl;

	if (success_num == samp_num)
		return 1;
	else
		return 0;
}




int SFDPobj::RunMySFVs()
{
	GazeboScenarioGenerator * ScenGen;
	GazeboExecutor * ScenExe;

	std::string folder_url;
	int sfv_index=1;

	std::vector <float> grades;
	float grad;

	for (SFV * sfv_it : * my_sampled_SFVs )
	{
		folder_url = my_WS_url + "/sampl_" + std::to_string(sfv_index);

		if(! boost::filesystem::is_directory(folder_url))
			{
			std::cout << "\033[1;31m failed to locate folder of sampl_" << std::to_string(sfv_index) << "\033[1;31m" << std::endl;
			break;
			}

		ScenGen = new GazeboScenarioGenerator(sfv_it, folder_url);
		ScenGen->GenerateScenario();

		ScenExe = new GazeboExecutor("AUT_url","Grader_url",my_WS_url);
		ScenExe->RunScenario();

		grad = ScenExe->get_scenario_grade();
		grades.push_back(grad);
		std::cout << " grade of scenario " << sfv_index << " = " << grad << std::endl;

     	sfv_index++;
	}


	float sum = 0;
	float sum_of_squers = 0;
	for (float scen_grad : grades)
		{
		sum = sum + scen_grad;
		sum_of_squers = sum_of_squers + scen_grad*scen_grad;
		}

	my_Grade_mean = sum/sfv_index;												  // E(x) = sum(x)/n
	my_Grade_std = sqrt(sum_of_squers/sfv_index - my_Grade_mean*my_Grade_mean);   // Var(x) = E(x^2) - [E(x)]^2


	have_been_run = true;

    PrintMyResultsToFile();

	return 1;

}



int SFDPobj::PrintMyResultsToFile()
{
	if (! have_been_run)
	{
		std::cout << " \033[1;31m can't print results file because the SFVs havn't been run yet \033[0m" << std::endl;
		return 0;
	}

	TiXmlDocument doc(my_Grades_file_url);
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild(decl);

	TiXmlElement * xml_results = new TiXmlElement( "Scenario_results" );
	xml_results->SetAttribute("version","1.0");
	doc.LinkEndChild(xml_results);

	std::stringstream temp_ss;

	temp_ss.str("");
	temp_ss << my_Grade_mean;
	TiXmlElement * xml_mean = new TiXmlElement( "grades_mean" );
	TiXmlText * mean_val= new TiXmlText( temp_ss.str() );
	xml_mean->LinkEndChild(mean_val);
	doc.LinkEndChild(xml_mean);

	temp_ss.str("");
	temp_ss << my_Grade_std;
	TiXmlElement * xml_std = new TiXmlElement( "grades_std" );
	TiXmlText * std_val= new TiXmlText( temp_ss.str() );
	xml_std->LinkEndChild(std_val);
	doc.LinkEndChild(xml_std);

	doc.SaveFile(my_Grades_file_url.c_str());
	std::cout << " printing Grades to file : " << my_Grades_file_url << std::endl;

	return 1;
}



ScenarioFeature * SFDPobj::finedScenrioFeature(ScenarioFeatureGroupType GroupType, std::string GroupName, ScenarioFeatureType FeatureToLocate)
{
	for ( ScenarioFeatureGroup * group_it : * my_featureGroups )
		{
			if ( (group_it->get_featureGroupType() == GroupType) && (group_it->get_name() == GroupName) )
			{
				for (ScenarioFeature * feature_it : *(group_it->get_features()) )
				{
					if (feature_it->get_featureType() == FeatureToLocate)
					{
						return feature_it;
					}
				}
			}
		}
	std::cout << "\033[1;31m could not find GroupTipe " << GroupType << " = " << GroupName << " with feature " << FeatureToLocate << "\033[0m"<< std::endl;
	return 0;
}



int SFDPobj::SplitMe(ScenarioFeatureGroupType GroupTipe, std::string GroupName ,ScenarioFeatureType FeatureToSplit, float split_percents)
{
	SFDPobj * sub_sfdp1;
	SFDPobj * sub_sfdp2;

	std::string sub_sfdp_1_WS_url = my_WS_url + "sub_sfdp1/";
	std::string sub_sfdp_2_WS_url = my_WS_url + "sub_sfdp2/";

	boost::filesystem::remove_all(sub_sfdp_1_WS_url);
	boost::filesystem::remove_all(sub_sfdp_2_WS_url);

	boost::filesystem::create_directory(sub_sfdp_1_WS_url);
	boost::filesystem::create_directory(sub_sfdp_2_WS_url);


	if( ( boost::filesystem::create_directory(sub_sfdp_1_WS_url)) && ( boost::filesystem::create_directory(sub_sfdp_2_WS_url))  )
		{
		std::cout << "\033[1;31m vfailed to create folder for sub_sfdp_1_WS_url and/or sub_sfdp_2_WS_url at : " << std::endl;
		std::cout << sub_sfdp_1_WS_url << "\n" << sub_sfdp_2_WS_url << "\033[0m"<< std::endl;
		return 0;
		}


	sub_sfdp1 = new SFDPobj(sub_sfdp_1_WS_url+"sub_sfdp",my_Resources_file_url,sub_sfdp_1_WS_url,my_division_level+1);
	sub_sfdp1->set_FeatureGroups(this->get_FeatureGroups());

	sub_sfdp2 = new SFDPobj(sub_sfdp_2_WS_url+"sub_sfdp",my_Resources_file_url,sub_sfdp_2_WS_url,my_division_level+1);
	sub_sfdp2->set_FeatureGroups(this->get_FeatureGroups());

	ScenarioFeature * feature_sourse = this->finedScenrioFeature(GroupTipe,GroupName,FeatureToSplit);
	ScenarioFeature * feature_1 = sub_sfdp1->finedScenrioFeature(GroupTipe,GroupName,FeatureToSplit);
	ScenarioFeature * feature_2 = sub_sfdp2->finedScenrioFeature(GroupTipe,GroupName,FeatureToSplit);

	if ( (! feature_sourse) ||  (! feature_1) ||  (! feature_2) )
		{
			std::cout << "\033[1;31m  could not split because feature to split wasn't found \033[0m" << std::endl;
			return 0;
		}


	if ( feature_sourse->get_distType() == ScenarioFeatureDistributionType::uniform_continuous )
		{
			float range = feature_sourse->get_dist_param_2() - feature_sourse->get_dist_param_1();
			float new_bound = feature_sourse->get_dist_param_1() + split_percents * range;
			feature_1->set_dist_param_2(new_bound);				feature_2->set_dist_param_1(new_bound);
		}

	if ( feature_sourse->get_distType() == ScenarioFeatureDistributionType::uniform_discrete )
		{
			float range = feature_sourse->get_dist_param_2() - feature_sourse->get_dist_param_1();
			float new_bound = (int) (feature_sourse->get_dist_param_1() + split_percents * range);
			feature_1->set_dist_param_2(new_bound);
			feature_2->set_dist_param_1(new_bound);
		}

	if ( feature_sourse->get_distType() == ScenarioFeatureDistributionType::normal_continuous )
		{
			float mu = feature_sourse->get_dist_param_1();
			float sigma = feature_sourse->get_dist_param_2();

			feature_1->set_dist_param_1(mu-sigma);
			feature_1->set_dist_param_2(sigma/2);

			feature_2->set_dist_param_1(mu+sigma);
			feature_2->set_dist_param_2(sigma/2);
		}

	my_sub_SFDPs->push_back(sub_sfdp1);
	my_sub_SFDPs->push_back(sub_sfdp2);

	sub_sfdp1->PrintMeToFile();
	sub_sfdp2->PrintMeToFile();

	return 1;
}


int SFDPobj::ExploreMe()
{
	if ( my_division_level > division_limit )
	{
		std::cout << "the division level reached the Division Limit " << std::endl;
		return 0;
	}

	if (! GenMySFVs(5) )
	{
		std::cout << "\033[1;31m the generation of SFVs have failed \033[0m" << std::endl;
		return 0;
	}

	RunMySFVs();

	if (my_division_level <= 2)
	{
		if (my_Grade_std > 0.25)
			{
				SplitMe(ScenarioFeatureGroupType::objects, "objects" ,ScenarioFeatureType::object_i_location_on_the_X_axis, 0.5);
				for (SFDPobj * sub_SFDP_it : * my_sub_SFDPs)
					{
						sub_SFDP_it->ExploreMe();
					}
			}
	}

	return 1;
}


