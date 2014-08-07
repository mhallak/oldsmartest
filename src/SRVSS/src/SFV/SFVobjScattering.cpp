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


SFVobjScattering::SFVobjScattering(std::vector<ScenarioFeature *> * ScenarioFeatures_vec,  SFV * parent_SFV): sfvSubGroup(ScenarioFeatureGroupType::objects, parent_SFV)
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


		my_object_template = new SFVObject(ScenarioFeatures_vec, parent_SFV);

		my_Objects = new std::vector<SFVObject *>;

		was_rolled_flag = false;

		if ( (my_num_of_objects==0) || (my_object_template==0) )
			{
			std::cout << "\033[1;31m The Objects Scattering was no fully defined \033[0m" << std::endl;
			}
}

SFVobjScattering::SFVobjScattering(SFVobjScattering * template_SFVobjScattering): sfvSubGroup(template_SFVobjScattering->get_Type(),template_SFVobjScattering->get_ParentSFV())
{
	my_num_of_objects = new ScenarioFeature(template_SFVobjScattering->get_NumberOfObjects());
	my_object_template = new SFVObject(template_SFVobjScattering->get_ObjectTemplate());

	my_Objects = new std::vector<SFVObject *>;

	was_rolled_flag = false;
}



bool SFVobjScattering::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Objects Scattering) \033[0m"<< std::endl;
		return(false);
	}
	else
	{
		int roll_attemps_limit = 3;
		int roll_attemp=1;
		bool roll_fail_flag=false;
		my_Objects = new std::vector<SFVObject *>;

		while (roll_attemp <= roll_attemps_limit)
		{
			my_num_of_objects->roll();
			SFVObject * obj_i;
			for (int i=1 ; i<=my_num_of_objects->get_RolledValue(); i++)
				{
				obj_i = new SFVObject(my_object_template);
				if (obj_i->roll())
					{
					my_Objects->push_back(obj_i);
					}
				else
					{
					roll_fail_flag=true;
					break;
					}
				}

		if (roll_fail_flag)
			{
			my_num_of_objects = new ScenarioFeature(this->get_NumberOfObjects());
			my_Objects = new std::vector<SFVObject *>;
			std::cout << "\033[1;35m fail to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			}
		else
			{
			was_rolled_flag = true;
			std::cout << "\033[1;32m Succeed to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			return(true);
			}
		roll_attemp++;
		}
	return(false);
	}
}


TiXmlElement * SFVobjScattering::ToXmlElement(int id)
{
	if (! was_rolled_flag)
	{
		std::cout << "\033[1;31m can not make XML element for SFVobjScattering because it wasn't rolled yet \033[0m"<< std::endl;
		return(0);
	}
	else
	{
		TiXmlElement * xml_sub_group = new TiXmlElement(get_Type().str());
		xml_sub_group->SetAttribute("ID",std::to_string(id));

		int id=1;
		for (SFVObject * obj_it : * get_Objects())
		{
			xml_sub_group->LinkEndChild(obj_it->ToXmlElement(id));
			id++;
		}

		return(xml_sub_group);
	}
}

SFVobjScattering::~SFVobjScattering()
{

}
