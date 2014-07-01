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

#include "Generators/Gazebo/GazeboScenarioGenerator.h"



std::string SFDP_file_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/SFDP/test.SFDP";
std::string SFVs_destination_folder_path = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/SFV/tests/";
std::string scenarios_destination_folder_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/scenarios/tests/";
std::string resource_file_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/resource/resource_srvssDumy.xml";


int main(int argc, char** argv)
{

	std::cout << " SampelingAlgo is runing !!! " << std::endl;

	std::cout << " SFDP_file_url = " << SFDP_file_url << std::endl;

	SFDPParser SFDPpars;
	SFDPComponent *sfdpComp=SFDPpars.genSFDPFromFile(SFDP_file_url);

	std::vector<SFVComponent *> * SFVs_vec;
	SFVs_vec = sfdpComp->genSFVs(10,SFVs_destination_folder_path,resource_file_url);


    GazeboScenarioGenerator * ScenGen=new GazeboScenarioGenerator();

    SFVComponent *sfvComp = SFVs_vec->at(0);
    ScenGen->GenerateScenario(sfvComp,scenarios_destination_folder_url, resource_file_url);



	return 0;
}
