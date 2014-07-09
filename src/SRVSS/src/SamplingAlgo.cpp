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

#define PATH std::string("")

//const std::string SFDP_file_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/work_space/root.SFDP";
//const std::string SFVs_destination_folder_path = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/work_space/";
//const std::string scenarios_destination_folder_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/work_space/";
//const std::string resource_file_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/resource/resource_srvssDumy.xml";



void printUsage()
{
	std::cout << "usage:" <<std:: endl;
	std::cout <<"(1) <srvss> -genSFV <sdfp file> <sfv output> <resousc file> # will generate a sfv file according to the sfdp and resource files input " <<std:: endl;
	std::cout <<"(2) <srvss> -genSCEN <sfv output> <destination folder> <resousc file> # will generate the scenario and launch it" <<std:: endl;
	exit(1);
}


int main(int argc, char** argv)
{

	std::cout << " SampelingAlgo is runing !!! " << std::endl;


	if(std::string(argv[1]).compare("-genSFV")==0)
		{
			std::cout << " -genSFV is runing !!! " << std::endl;

			std::string SFDP_file_path = PATH+argv[2];
			std::string sfv_file_destanation_path = PATH + argv[3];
			std::string resources_file_path = PATH + argv[4];

			SFDPobj * sfdp_root = new SFDPobj(SFDP_file_path,resources_file_path,sfv_file_destanation_path,0);

			if (! sfdp_root->ParseMeFromXMLFile())
			{
				std::cout << " failed parse SFDP from file " << std::endl;
				return 0;
			}

			SFVComponent *sfvComp = sfdp_root->genSFVComp();
			if (! sfvComp )
			{
				std::cout << " rolling of SFV have failed " << std::endl;
				return 0;
			}

			sfvComp->genFileFromSFV(sfv_file_destanation_path);
			return 1;
		}



	if(std::string(argv[1]).compare("-genSCEN")==0)
		{
			std::cout << " -genSCEN is runing !!! " << std::endl;

			std::string sfv_file_path = PATH+argv[2];
			std::string scenarios_folder_path = PATH + argv[3];
			std::string resources_file_path = PATH + argv[4];

			SFVComponent *sfvComp=new SFVComponent(resources_file_path);
			sfvComp->genSFVFromFile(sfv_file_path);
			sfvComp->genFileFromSFV("testRun.sfv");

			GazeboScenarioGenerator * ScenGen = new GazeboScenarioGenerator(sfvComp, scenarios_folder_path, resources_file_path);
			ScenGen->GenerateScenario();

			return 1;
		}


	return 0;

}
