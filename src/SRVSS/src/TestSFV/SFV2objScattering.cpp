/*
 * SFV2objScattering.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: userws3
 */


#include <iostream>
#include "TestSFV/SFV2objScattering.h"
#include "TestSFV/SFV2Object.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeature.h"


SFV2objScattering::SFV2objScattering(std::vector<ScenarioFeature *> * ScenarioFeatures_vec): sfvSubGroup(ScenarioFeatureGroupType::objects)
{
		my_num_of_objects = 0;
		my_object_template = 0;

		for (ScenarioFeature * feature_it : * ScenarioFeatures_vec )
		{
		 switch (feature_it->get_featureType().value())
		 	 {
		 	 case(ScenarioFeatureType::number_of_objects) :
				my_num_of_objects = new ScenarioFeature(feature_it);
		 		break;
		 	 }
		}

		my_object_template = new SFV2Object(ScenarioFeatures_vec);
		my_Objects = new std::vector<SFV2Object *>;

		was_rolled_flag = false;

		if ( (my_num_of_objects==0) || (my_object_template==0) )
			{
			std::cout << "\033[1;31m The Objects Scattering was no fully defined \033[0m" << std::endl;
			}
}

SFV2objScattering::SFV2objScattering(SFV2objScattering * template_SFV2objScattering): sfvSubGroup(ScenarioFeatureGroupType::objects)
{
	my_num_of_objects = new ScenarioFeature(template_SFV2objScattering->get_NumberOfObjects());
	my_object_template = new SFV2Object(template_SFV2objScattering->get_ObjectTemplate());

	my_Objects = new std::vector<SFV2Object *>;
	for (SFV2Object * obj_it : * template_SFV2objScattering->get_Objects())
	 	 {
		my_Objects->push_back(new SFV2Object(obj_it));
	 	 }

	was_rolled_flag = false;
}

void SFV2objScattering::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Objects Scattering) \033[0m"<< std::endl;
	}
	else
	{
		my_num_of_objects->roll();
		SFV2Object * obj_i;
		for (int i=1 ; i<=my_num_of_objects->get_RolledValue(); i++)
			{
			obj_i = new SFV2Object(my_object_template);
			obj_i->roll();
			my_Objects->push_back(obj_i);
			}
		was_rolled_flag = true;
	}
}

SFV2objScattering::~SFV2objScattering()
{

}
