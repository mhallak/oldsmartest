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



			SFV * sfv = new SFV(sfdp_root);
			if (sfv->roll() )
				{
				sfv->printToXML(scenario_folder_path+"/test.SFV");





			SFV * sfv2 = new SFV(scenario_folder_path+"/test.SFV");

			sfv2->printToXML(scenario_folder_path+"/test2.SFV");


				GazeboScenarioGenerator * ScenGen = new GazeboScenarioGenerator(sfv2, scenario_folder_path);
				ScenGen->GenerateScenario();

			}


			//SFVpath * testPath = (SFVpath *)(sfv->get_sfvSubGroups()->at(0));

/*
			for (SFV * sfv_it : * sfdp_root->get_Sampled_SFVs())
			{

				for (sfvSubGroup * subGroup_it : * sfv_it->get_sfvSubGroups())
					{
					std::cout << " subGroup_it->get_Type().str() = " << subGroup_it->get_Type().str() << std::endl;
					}




				for (sfvSubGroup * subGroup_it : * sfv_it->get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType::objects) )
				{
					SFVobjScattering *Objs = (SFVobjScattering *)subGroup_it;
					for (SFVObject *obj : *Objs->get_Objects() )
					{
						std::cout << "  obj->get_ObjectType()->get_RolledValue() = " << obj->get_ObjectType()->get_RolledValue() << std::endl;

					}
				}
			}
*/
			return 0;

		}

}
