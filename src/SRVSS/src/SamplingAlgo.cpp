#include <string>
#include <stdio.h>
#include <iostream>

#include "Generators/Gazebo/GazeboScenarioGenerator.h"

#include "SFDP/SFDPobj.h"


#define PATH std::string("")

const std::string SFDP_file_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/work_space/root.SFDP";
const std::string SFVs_destination_folder_path = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/work_space/";
const std::string scenarios_destination_folder_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/work_space/";
const std::string resource_file_url = "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/resource/resource_srvssDumy.xml";


int main(int argc, char** argv)
{
	std::cout << " Exploration is runing !!! " << std::endl;
	std::string SFDP_file_path = PATH+argv[1];
	std::string scenario_folder_path = PATH + argv[2];
	std::string resources_file_path = PATH + argv[3];

	SFDPobj * sfdp_root;
	sfdp_root = new SFDPobj(SFDP_file_path,resources_file_path,scenario_folder_path,0);
	if (! sfdp_root->ParseMeFromXMLFile())
		{
		std::cout << "\033[1;31m Failed parse SFDP from file \033[0m " << std::endl;
		return 0;
		}


	sfdp_root->ExploreMe(argc,argv);


	char c;
	std::cout << " Exploration finish " << std::endl;
	std::cin >> c;


	return 1;
}
