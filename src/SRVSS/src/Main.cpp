#include <iostream>
#include <stdio.h>

#include <string>

#include "SFDP/SFDPobj.h"
#include "Generators/Gazebo/GazeboScenarioGenerator.h"

#include "Generators/Gazebo/GazeboScenarioGenerator.h"
#include "Synchronizer/ScenarioCoordinatorPool.h"


//for tests
#include "SFV/SFVComponent.h"
#include "SFV/SFVObject.h"
//

#define PATH std::string("")

void printUsage()
{
	std::cout << "usage:" <<std:: endl;
	std::cout <<"(1) <srvss> -genSFV <sdfp file> <sfv output> <resousc file> # will generate a sfv file according to the sfdp and resource files input " <<std:: endl;
	std::cout <<"(2) <srvss> -genSCEN <sfv output> <destination folder> <resousc file> # will generate the scenario and launch it" <<std:: endl;
	exit(1);
}

int main(int argc, char** argv)
{

	std::cout << " Main is runing !!! " << std::endl;

	if(std::string(argv[1]).compare("-help")==0)
		{
		printUsage();
		}

	if(std::string(argv[1]).compare("-genSFV")==0)
		{
			std::cout << " -genSFV is runing !!! " << std::endl;

			std::string SFDP_file_path = PATH+argv[2];
			std::string sfv_file_destanation_path = PATH + argv[3];
			std::string resources_file_path = PATH + argv[4];

			SFDPobj * sfdp_root;
			sfdp_root = new SFDPobj(SFDP_file_path,resources_file_path,sfv_file_destanation_path,0);

			if (! sfdp_root->ParseMeFromXMLFile())
			{
				std::cout << "\033[1;31m Failed parse SFDP from file \033[0m " << std::endl;
				return 0;
			}

			SFVComponent *sfvComp = sfdp_root->genSFVComp();
			if (! sfvComp )
			{
				std::cout << "\033[1;31m rolling of SFV have failed \033[0m" << std::endl;
				return 0;
			}
			sfvComp->genFileFromSFV(sfv_file_destanation_path);

			return 0;
		}

	if(std::string(argv[1]).compare("-genSCEN")==0)
		{

			std::cout << " -genSCEN is runing !!! " << std::endl;

			std::string sfv_file_path = PATH+argv[2];
			std::string scenarios_folder_path = PATH + argv[3];
			std::string resources_file_path = PATH + argv[4];

			SFV *sfv = new SFVComponent(resources_file_path);
			sfvComp->genSFVFromFile(sfv_file_path);
			sfvComp->genFileFromSFV("testRun.sfv");

			GazeboScenarioGenerator * ScenGen = new GazeboScenarioGenerator(sfvComp, scenarios_folder_path, resources_file_path);
			ScenGen->GenerateScenario();


			/*
			ScenarioCoordinator* cord =ScenarioCoordinatorPool::Instance()->genCoordinator(8992,8993);
			std::cout << " pool done!!! " << std::endl;

			cord->startRosCore();
			std::cout << " core done!!! " << std::endl;

			cord->startGazeboServer();
			std::cout << " server done!!! " << std::endl;

			cord->launchGazeboClient();

			for (SFVObjects* objs_it : *(sfvComp->getObjects()) )
			{
				for (SFVObject* sfvObj : *objs_it->m_objects)
			     {
			    	 std::cout << "obj->m_name = " << sfvObj->m_name << std::endl;
				 cord->spawnGazeboModel<SFVObject>(sfvObj);
			char c;
			std::cin >>c;
 			     }
			}
*/
			return 0;
		}


	return 0;
}
