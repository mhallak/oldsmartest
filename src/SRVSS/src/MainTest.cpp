#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

#include "SFDP/ScenarioFeature.h"
#include "SFDP/ScenarioFeatureGroup.h"

#include "SFDP/SFDPobj.h"

#include "TestSFV/sfvSubGroup.h"

#include "TestSFV/SFVwp.h"
#include "TestSFV/SFV2path.h"
#include "TestSFV/SFV2.h"

#include "TestSFV/SFV2mass_link.h"
#include "TestSFV/SFV2objScattering.h"

#define PATH std::string("")

int main(int argc, char** argv)
{
	std::cout << " Test Main is runing !!! " << std::endl;


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


			SFV2 * sfv = new SFV2(sfdp_root);
			sfv->roll();

			//SFV2path * testPath = (SFV2path *)(sfv->get_sfvSubGroups()->at(0));



			for (sfvSubGroup * subGroup_it : * sfv->get_sfvSubGroups())
			{
			std::cout << " subGroup_it->get_Type().str() = " << subGroup_it->get_Type().str() << std::endl;
			}


			for (sfvSubGroup * subGroup_it : * sfv->get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType::objects) )
			{
			SFV2objScattering *Objs = (SFV2objScattering *)subGroup_it;
			for (SFV2Object *obj : *Objs->get_Objects() )
				{
				std::cout << "  obj->get_ObjectType()->get_RolledValue() = " << obj->get_ObjectType()->get_RolledValue() << std::endl;

				}
			}

			return 0;

		}
}
