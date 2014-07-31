/*
 * SFV2.cpp
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */

#include "TestSFV/SFV2.h"
#include "SFDP/SFDPobj.h"
#include "TestSFV/sfvSubGroup.h"
#include "TestSFV/SFV2path.h"
#include "TestSFV/SFV2mass_link.h"
#include "TestSFV/SFV2terraine.h"
#include "SFDP/ScenarioFeatureGroup.h"


SFV2::SFV2(SFDPobj * SFDP): sfvSubGroup(ScenarioFeatureGroupType::SFV)
{
	my_sfvSubGroups = new std::vector<sfvSubGroup *>;

	for (ScenarioFeatureGroup * featureGroup_it : * SFDP->get_FeatureGroups() )
	{
	 switch (featureGroup_it->get_featureGroupType().value())
	 	 {
	 	 case(ScenarioFeatureGroupType::waypoints) :
			my_sfvSubGroups->push_back( new SFV2path(featureGroup_it->get_features()) );
	 		break;

	 	 case(ScenarioFeatureGroupType::mass_link_i) :
			my_sfvSubGroups->push_back( new SFV2mass_link(featureGroup_it->get_name(),featureGroup_it->get_features() ) );
	 		break;

	 	 case(ScenarioFeatureGroupType::map) :
			my_sfvSubGroups->push_back( new SFV2terraine(featureGroup_it->get_features() ) );
	 		break;
	 	 }
	 }

	was_rolled_flag = false;
}


std::vector<sfvSubGroup *> * SFV2::get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType GroupType)
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



void SFV2::roll()
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




SFV2::~SFV2()
{

}

