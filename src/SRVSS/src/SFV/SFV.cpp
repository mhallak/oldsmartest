/*
 * SFV.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */

#include "SFV/SFV.h"
//#include "SFDP/SFDPobj.h"
#include "SFV/sfvSubGroup.h"
#include "SFV/SFVpath.h"
#include "SFV/SFVmass_link.h"
#include "SFV/SFVterraine.h"
#include "SFV/SFVobjScattering.h"

#include "SFDP/ScenarioFeatureGroup.h"


SFV::SFV() : sfvSubGroup(ScenarioFeatureGroupType::SFV)
{}

/*
SFV::SFV(SFDPobj * SFDP): sfvSubGroup(ScenarioFeatureGroupType::SFV)
{
	my_sfvSubGroups = new std::vector<sfvSubGroup *>;

	for (ScenarioFeatureGroup * featureGroup_it : * SFDP->get_FeatureGroups() )
	{
	 switch (featureGroup_it->get_featureGroupType().value())
	 	 {
	 	 case(ScenarioFeatureGroupType::waypoints) :
			my_sfvSubGroups->push_back( new SFVpath(featureGroup_it->get_features()) );
	 		break;

	 	 case(ScenarioFeatureGroupType::mass_link_i) :
			my_sfvSubGroups->push_back( new SFVmass_link(featureGroup_it->get_name(),featureGroup_it->get_features() ) );
	 		break;

	 	 case(ScenarioFeatureGroupType::map) :
			my_sfvSubGroups->push_back( new SFVterraine(featureGroup_it->get_features() ) );
	 		break;

	 	 case(ScenarioFeatureGroupType::objects) :
			my_sfvSubGroups->push_back( new SFVobjScattering(featureGroup_it->get_features() ) );
	 	 	break;
	 	 }
 	 }

	was_rolled_flag = false;
}
*/

std::vector<sfvSubGroup *> * SFV::get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType GroupType)
{
	std::vector<sfvSubGroup *> * Vec = new std::vector<sfvSubGroup *>;

	for (sfvSubGroup * subGroup_it : * my_sfvSubGroups)
		{
		if (subGroup_it->get_Type().value() == GroupType.value())
			{
			Vec->push_back(subGroup_it);
			}
		}
	return(Vec);
}



void SFV::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am SFV) \033[0m"<< std::endl;
	}
	else
	{
		for (sfvSubGroup * subGroup_it : * my_sfvSubGroups)
			{
			subGroup_it->roll();
			}
		was_rolled_flag = true;
	}
}




SFV::~SFV()
{

}

