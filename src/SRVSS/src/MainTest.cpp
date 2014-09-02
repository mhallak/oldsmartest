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
#include "Executor/GazeboExecutor.h"

#include "Executor/scenarioLauncher.h"

#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"

#define PATH std::string("")

/*
void scen_grade_Callback(const std_msgs::Float32MultiArray::ConstPtr &msg)
{
	// std::cout << " << msg->data[1]  = " <<  msg->data[1] << std::endl;
}
*/

int main(int argc, char** argv)
{
	std::cout << " Test Main is runing !!! " << std::endl;
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

	if (sfdp_root->GenMySFVs(1) )
	{
	sfdp_root->RunMySFVs(argc,argv);
	}




	return 0;
}
