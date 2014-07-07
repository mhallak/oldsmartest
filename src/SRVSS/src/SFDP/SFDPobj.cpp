/*
 * SFDPobj.cpp
 *
 *  Created on: Jul 1, 2014
 *      Author: userws3
 */

#include "SFDP/SFDPobj.h"
#include "SFDP/SFDPParser.h"
#include "Generators/Gazebo/GazeboScenarioGenerator.h"
#include "Executor/GazeboExecutor.h"

#include <string>
#include <vector>

#include <iostream>

#include <boost/filesystem.hpp>

#include <cmath> //sqrt()



SFDPobj::SFDPobj(std::string SFDP_file_url, std::string Resources_file_url, std::string WS_url, int division_level)
{
	my_SFDP_file_url = SFDP_file_url;
	my_Resources_file_url = Resources_file_url;
	my_WS_url = WS_url;
	my_Grades_file_url = WS_url + "Grades.xml";
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
	GazeboScenarioGenerator * ScenGen;
	GazeboExecutor * ScenExe;

	std::string folder_url;
	int sfv_index=1;

	std::vector <float> grades;
	float grad;

	for (SFVComponent * sfvComp_it : * my_sampled_SFVs )
	{
		folder_url = my_WS_url + "sampl_" + std::to_string(sfv_index) + "/";

		if(! boost::filesystem::is_directory(folder_url))
			{
			std::cout << " failed to locate folder of sampl_" << std::to_string(sfv_index) << std::endl;
			break;
			}

		ScenGen = new GazeboScenarioGenerator(sfvComp_it, folder_url, my_Resources_file_url);
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
		std::cout << " can't print results file because the SFVs havn't been run yet " << std::endl;
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




ScenarioFeature * SFDPobj::finedScenrioFeature(ScenarioFeatureType FeatureToSplit)
{
	for ( ScenarioFeatureGroup * group_it : * my_featureGroups )
		{
			for (ScenarioFeature * feature_it : *(group_it->get_features()) )
			{
				if (feature_it->get_featureType() == FeatureToSplit)
				{
				return feature_it;
				}
			}
		}
	return 0;
}




int SFDPobj::SplitMe(ScenarioFeatureType FeatureToSplit, float split_percents)
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
		std::cout << "failed to create folder for sub_sfdp_1_WS_url and/or sub_sfdp_2_WS_url at : " << std::endl;
		std::cout << sub_sfdp_1_WS_url << "\n" << sub_sfdp_2_WS_url << std::endl;
		return 0;
		}


	sub_sfdp1 = new SFDPobj(sub_sfdp_1_WS_url+"sub_sfdp",my_Resources_file_url,sub_sfdp_1_WS_url,my_division_level+1);
	sub_sfdp1->set_FeatureGroups(this->get_FeatureGroups());

	sub_sfdp2 = new SFDPobj(sub_sfdp_2_WS_url+"sub_sfdp",my_Resources_file_url,sub_sfdp_2_WS_url,my_division_level+1);
	sub_sfdp2->set_FeatureGroups(this->get_FeatureGroups());


	ScenarioFeature * feature_sourse = this->finedScenrioFeature(FeatureToSplit);
	ScenarioFeature * feature_1 = sub_sfdp1->finedScenrioFeature(FeatureToSplit);
	ScenarioFeature * feature_2 = sub_sfdp2->finedScenrioFeature(FeatureToSplit);

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

	GenMySFVs(5);
	RunMySFVs();

	if (my_division_level <= 2)
	{
		if (my_Grade_std > 0.25)
			{
				SplitMe(ScenarioFeatureType::object_i_location_on_the_X_axis, 0.5);
				for (SFDPobj * sub_SFDP_it : * my_sub_SFDPs)
					{
						sub_SFDP_it->ExploreMe();
					}
			}
	}

	return 1;
}


