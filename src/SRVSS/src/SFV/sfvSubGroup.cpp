/*
 * sfvSubGroup.cpp
 *
 *  Created on: Aug 6, 2014
 *      Author: userws3
 */

#include <map>

#include "SFV/sfvSubGroup.h"
#include "SFDP/ScenarioFeature.h"
#include "SFDP/ScenarioFeatureType.h"


void sfvSubGroup::initSubGroupFeatures(std::vector<ScenarioFeature *> * ScenarioFeatures_vec)
{

	for (auto& feature : *my_features_map)
		{
	     *(feature.second) = 0;
		}


	for (ScenarioFeature * feature_it : * ScenarioFeatures_vec )
		{
		if ( my_features_map->find(feature_it->get_featureType()) != my_features_map->end() )
			{
			*(my_features_map->at(feature_it->get_featureType())) = new ScenarioFeature(feature_it);
			}
		}


	for (auto& feature : *my_features_map)
		{
	     if (*(feature.second) == 0)
	      {
	    	 std::cout << "\033[1;31m The " << feature.first << " was no fully defined \033[0m" << std::endl;
	    	 break;
	      }
		}
}


void sfvSubGroup::cloneSubGroupFeatures(sfvSubGroup * template_group)
{
	for (auto& feature : *(template_group->get_FeaturesMap()) )
		{
	     *(my_features_map->at(feature.first)) = new ScenarioFeature(*(feature.second));
		}

	for (auto& feature : *my_features_map)
		{
	     if (*(feature.second) == 0)
	      {
	    	 std::cout << "\033[1;31m The " << feature.first << " was no fully defined while cloning \033[0m" << std::endl;
	    	 break;
	      }
		}
}


void sfvSubGroup::rollSubGroupfeatures()
{
	for (auto& feature : *my_features_map)
		{
		 (*(feature.second))->roll();
		}
}


void sfvSubGroup::resetSubGroupfeatures()
{
	for (auto& feature : *my_features_map)
		{
		*(feature.second) = new ScenarioFeature(*(feature.second));
		}
}


TiXmlElement * sfvSubGroup::SubGroupfeaturesToXmlElement(int id)
{
	TiXmlElement * xml_sub_group = new TiXmlElement(get_Type().str());
	xml_sub_group->SetAttribute("ID",std::to_string(id));
	xml_sub_group->SetAttribute("name", my_name);

	for (auto& feature : *my_features_map)
		{
		xml_sub_group->LinkEndChild((*(feature.second))->toSFV_XMLElement());
		}

	return(xml_sub_group);
}

