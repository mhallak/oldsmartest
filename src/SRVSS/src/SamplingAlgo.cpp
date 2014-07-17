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
	std::cout << " SampelingAlgo is runing !!! " << std::endl;

	SFDPobj * sfdp_root = new SFDPobj(SFDP_file_url,resource_file_url,SFVs_destination_folder_path,0);
	if (! sfdp_root->ParseMeFromXMLFile())
		{
			std::cout << " failed parse SFDP from file " << std::endl;
			return 0;
		}

	sfdp_root->ExploreMe();


	/*
	SFVComponent *sfvComp = sfdp_root->genSFVComp();
	if (! sfvComp )
		{
			std::cout << " rolling of SFV have failed " << std::endl;
			return 0;
		}

	sfvComp->genFileFromSFV(SFVs_destination_folder_path+"sfv1.SFV");

	GazeboScenarioGenerator * ScenGen = new GazeboScenarioGenerator(sfvComp, scenarios_destination_folder_url, resource_file_url);
	ScenGen->GenerateScenario();
	*/

	return 1;
}
