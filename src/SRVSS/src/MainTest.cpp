#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

#include "SFDP/ScenarioFeature.h"
#include "SFDP/ScenarioFeatureGroup.h"


#include "SFDP/SFDPobj.h"
#include "SFV/sfvSubGroup.h"


#include "SFV/SFV.h"

#include "SFV/SFVmass_link.h"
#include "SFV/SFVobjScattering.h"

#include "Generators/Gazebo/GazeboScenarioGenerator.h"

#include "Synchronizer/ScenarioCoordinatorPool.h"

#include "Synchronizer/scenarioLauncher.h"

#define PATH std::string("")

int main(int argc, char** argv)
{
	std::cout << " Test Main is runing !!! " << std::endl;

	if(std::string(argv[1]).compare("-genSCEN")==0)
		{
			std::cout << " -genSFV is runing !!! " << std::endl;

			std::string SFDP_file_path = PATH+argv[2];
			std::string scenario_folder_path = PATH + argv[3];
			std::string resources_file_path = PATH + argv[4];

			SFDPobj * sfdp_root;
			sfdp_root = new SFDPobj(SFDP_file_path,resources_file_path,scenario_folder_path,0);

			if (! sfdp_root->ParseMeFromXMLFile())
			{
				std::cout << "\033[1;31m Failed parse SFDP from file \033[0m " << std::endl;
				return 0;
			}


char c;
ScenarioLauncher *launcher = new ScenarioLauncher();
for (int i=1 ; i<=3 ; i++)
	{
			SFV * sfv = new SFV(sfdp_root);
			if (! sfv->roll() )
				{
				std::cout << "\033[1;31m Fail to roll SFV !!! \033[0m" << std::endl;
 				return (0);
				}

			sfv->printToXML(scenario_folder_path+"/test.SFV");

			GazeboScenarioGenerator * ScenGen = new GazeboScenarioGenerator(sfv, scenario_folder_path);
			ScenGen->GenerateScenario();

			std::cout << " I am here !!! " << std::endl;


			launcher->start_launcher();

			launcher->setScenarioEnv(scenario_folder_path);
			std::cout << "\033[1;31m Scenario Env_Variables are loaded !!! \033[0m" << std::endl;

			launcher->startGazeboServer(scenario_folder_path);
			std::cout << "\033[1;31m GazeboServer is loaded !!! \033[0m" << std::endl;

			launcher->launchGazeboClient();
			std::cout << "\033[1;31m GazeboClient is loaded !!! \033[0m" << std::endl;

			launcher->launchPlatformControls();
			std::cout << "\033[1;31m Platform is loaded !!! \033[0m" << std::endl;

			launcher->launchWPdriver(scenario_folder_path);
			std::cout << "\033[1;31m WP driver is loaded !!! \03re3[0m" << std::endl;

			launcher->launchTFbroadcaster();
			std::cout << "\033[1;31m TF publishing is loaded !!! \033[0m" << std::endl;

			launcher->launchRecorder(scenario_folder_path);
			std::cout << "\033[1;31m Recorder is loaded !!! \033[0m" << std::endl;


			std::cin >>c;

			launcher->stop_launcher();
	}

launcher->~ScenarioLauncher();

		}

	return 0;
}
