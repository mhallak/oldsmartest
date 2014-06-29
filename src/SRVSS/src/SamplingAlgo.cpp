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



std::string SFDP_file_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/SFDP/test.SFDP";
std::string SFV_destination_folder_path = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/SFV/tests/";
std::string scenarios_folder_path = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/scenarios/";
std::string resource_file_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/resource/resource_srvssDumy.xml";


int main(int argc, char** argv)
{

	std::cout << " SampelingAlgo is runing !!! " << std::endl;

	std::cout << " SFDP_file_url = " << SFDP_file_url << std::endl;

	SFDPParser SFDPpars;
	SFDPComponent *sfdpComp=SFDPpars.genSFDPFromFile(SFDP_file_url);

	std::vector<int> sfv_successul_rollings;

	int num_of_rolling = 10;
	int success_rollings = 0;
	std::cout << " ############ starting rolling " << num_of_rolling << " SFVs" << std::endl;
	for (int scenario_i = 1 ; scenario_i<=10 ; scenario_i++)
		{

		std::cout << " ######## generating scenario no " << scenario_i << std::endl;

		SFVComponent * sfvComp=sfdpComp->genSFV(resource_file_url);
		sfvComp->init();

		bool sfv_roll_success = sfvComp->calc();

		if (sfv_roll_success)
			{
			sfvComp->genFileFromSFV(SFV_destination_folder_path + "testSFV_" + std::to_string(scenario_i) + ".sfv");
			success_rollings += 1;
			sfv_successul_rollings.push_back(scenario_i);
			}
		std::cout << " ######## rolling of scenario no : " << scenario_i << " success = " << sfv_roll_success << std::endl;
			}
	std::cout << " ########## success in rolling " << success_rollings << "/" << num_of_rolling << " SFVs" << std::endl;


    for (int  it : sfv_successul_rollings)
    {
    	std::cout << it << std::endl;
    }


			/*
			GazeboMissionGenerator * missionGen=new GazeboMissionGenerator();
     		missionGen->generateMission(sfvComp,scenarios_folder_path+"/myMission.txt", resources_file_path);
     		missionGen->generateMission_ROBIL2(sfvComp,scenarios_folder_path+"/myMission_robil2", resources_file_path);

			GazeboPlatformGenerator * platGen=new GazeboPlatformGenerator();
			platGen->generatePlatform(sfvComp,scenarios_folder_path+"/platform.sdf", resources_file_path);

			GazeboEnvironmentGenerator * envGen=new GazeboEnvironmentGenerator();
			envGen->genEnvFromSFV(sfvComp,scenarios_folder_path+"/env.world", resources_file_path);
          */

	return 0;
}
