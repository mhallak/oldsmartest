#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

#include "SFDP/ScenarioFeature.h"
#include "SFDP/ScenarioFeatureGroup.h"

//#include "SFDP/SFDPobj.h"

#include "SFV/sfvSubGroup.h"


#include "SFV/SFV.h"

#include "SFV/SFVmass_link.h"
#include "SFV/SFVobjScattering.h"

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

/*			SFDPobj * sfdp_root;
			sfdp_root = new SFDPobj(SFDP_file_path,resources_file_path,sfv_file_destanation_path,0);

			if (! sfdp_root->ParseMeFromXMLFile())
			{
				std::cout << "\033[1;31m Failed parse SFDP from file \033[0m " << std::endl;
				return 0;
			}
*/

	//		SFV * sfv = new SFV(sfdp_root);
			SFV * sfv = new SFV();
			sfv->roll();

			//SFVpath * testPath = (SFVpath *)(sfv->get_sfvSubGroups()->at(0));



			for (sfvSubGroup * subGroup_it : * sfv->get_sfvSubGroups())
			{
			std::cout << " subGroup_it->get_Type().str() = " << subGroup_it->get_Type().str() << std::endl;
			}


			for (sfvSubGroup * subGroup_it : * sfv->get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType::objects) )
			{
			SFVobjScattering *Objs = (SFVobjScattering *)subGroup_it;
			for (SFVObject *obj : *Objs->get_Objects() )
				{
				std::cout << "  obj->get_ObjectType()->get_RolledValue() = " << obj->get_ObjectType()->get_RolledValue() << std::endl;

				}
			}

			return 0;

		}

}
