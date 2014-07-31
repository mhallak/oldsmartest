/*
 * SFVobjScattering.cpp
 *
 *  Created on: Jul 31, 2014
 *      Author: userws3
 */


#include <iostream>
#include "SFV/SFVobjScattering.h"
#include "SFV/SFVObject.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeature.h"


SFVobjScattering::SFVobjScattering(std::vector<ScenarioFeature *> * ScenarioFeatures_vec): sfvSubGroup(ScenarioFeatureGroupType::objects)
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

		my_object_template = new SFVObject(ScenarioFeatures_vec);
		my_Objects = new std::vector<SFVObject *>;

		was_rolled_flag = false;

		if ( (my_num_of_objects==0) || (my_object_template==0) )
			{
			std::cout << "\033[1;31m The Objects Scattering was no fully defined \033[0m" << std::endl;
			}
}

SFVobjScattering::SFVobjScattering(SFVobjScattering * template_SFVobjScattering): sfvSubGroup(ScenarioFeatureGroupType::objects)
{
	my_num_of_objects = new ScenarioFeature(template_SFVobjScattering->get_NumberOfObjects());
	my_object_template = new SFVObject(template_SFVobjScattering->get_ObjectTemplate());

	my_Objects = new std::vector<SFVObject *>;
	for (SFVObject * obj_it : * template_SFVobjScattering->get_Objects())
	 	 {
		my_Objects->push_back(new SFVObject(obj_it));
	 	 }

	was_rolled_flag = false;
}

void SFVobjScattering::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Objects Scattering) \033[0m"<< std::endl;
	}
	else
	{
		my_num_of_objects->roll();
		SFVObject * obj_i;
		for (int i=1 ; i<=my_num_of_objects->get_RolledValue(); i++)
			{
			obj_i = new SFVObject(my_object_template);
			obj_i->roll();
			my_Objects->push_back(obj_i);
			}
		was_rolled_flag = true;
	}
}

SFVobjScattering::~SFVobjScattering()
{

}
