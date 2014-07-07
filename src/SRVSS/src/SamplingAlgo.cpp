#include "SFDP/SFDPComponent.h"
#include "SFDP/SFDPParser.h"
#include "Resource/ResourceHandler.h"
#include "Generators/Gazebo/GazeboEnvironmentGenerator.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include "Generators/Gazebo/GazeboPlatformGenerator.h"
#include "Generators/Gazebo/GazeboMissionGenerator.h"
#include "SRVSSSyncronizer.h"
#include "Executor.h"

#include "SFDP/ScenarioFeatureType.h"

#include "Generators/Gazebo/GazeboScenarioGenerator.h"

#include "SFDP/SFDPobj.h"

std::string SFDP_file_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/SFDP/test.SFDP";
std::string SFVs_destination_folder_path = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/work_space/";
std::string scenarios_destination_folder_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/work_space/";
std::string resource_file_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/resource/resource_srvssDumy.xml";


int main(int argc, char** argv)
{

	std::cout << " SampelingAlgo is runing !!! " << std::endl;

	SFDPobj * sfdp_root = new SFDPobj(SFDP_file_url,resource_file_url,SFVs_destination_folder_path,0);

	if (! sfdp_root->ParseMeFromFile(sfdp_root->get_SFDP_file_url()))
	{

		sfdp_root->ExploreMe();

		/*
		std::cout << sfdp_root->GenMySFVs(5) << std::endl;


		sfdp_root->RunMySFVs();


		float grade_mean = sfdp_root->get_Garade_mean();
		float grade_std = sfdp_root->get_Garade_std();

		std::cout << "grade_mean = " << grade_mean << "  grade_std = " << grade_std << std::endl;

		 */
		//sfdp_root->SplitkMe(ScenarioFeatureType::wp_i_relative_angle,0.5);
	}





	return 0;
}
