/*
 * SFVplatformPose.cpp
 *
 *  Created on: Aug 3, 2014
 *      Author: userws3
 */


#include <iostream>
#include "SFV/SFVplatformPose.h"
#include "SFV/SFVterraine.h"

#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeatureType.h"

#include "Resource/ResourceHandler.h"
#include "Generators/Gazebo/TerrainAnalyzer.h"

SFVplatformPose::SFVplatformPose(std::vector<ScenarioFeature *> * ScenarioFeatures_vec, SFV * parent_SFV): sfvSubGroup(ScenarioFeatureGroupType::platform_pose, parent_SFV)
{

	initial_platform_position_on_map_X_axis = 0;
	initial_platform_position_on_map_Y_axis = 0;
	initial_platform_azimut = 0;

	for (ScenarioFeature * feature_it : * ScenarioFeatures_vec )
	{
	 switch (feature_it->get_featureType().value())
	 	 {
	 	 case(ScenarioFeatureType::initial_platform_position_on_map_X_axis) :
		initial_platform_position_on_map_X_axis = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::initial_platform_position_on_map_Y_axis) :
		initial_platform_position_on_map_Y_axis = new ScenarioFeature(feature_it);
	 		break;
	 	 case(ScenarioFeatureType::initial_platform_azimut_on_map) :
		initial_platform_azimut = new ScenarioFeature(feature_it);
	 		break;
	 	 }
	 }

	was_rolled_flag = false;

	if ( (initial_platform_position_on_map_X_axis==0) || (initial_platform_position_on_map_Y_axis==0) || (initial_platform_azimut==0) )
		{
		std::cout << "\033[1;31m The Initial Platform Pose was no fully defined \033[0m" << std::endl;
		}
}


SFVplatformPose::SFVplatformPose(SFVplatformPose * template_SFVplatformPose): sfvSubGroup(template_SFVplatformPose->get_Type(),template_SFVplatformPose->get_ParentSFV())
{

	initial_platform_position_on_map_X_axis = new ScenarioFeature(template_SFVplatformPose->get_InitPlatformPoseX());
	initial_platform_position_on_map_Y_axis = new ScenarioFeature(template_SFVplatformPose->get_InitPlatformPoseY());
	initial_platform_azimut = new ScenarioFeature(template_SFVplatformPose->get_InitPlatformPoseAzimut());

	was_rolled_flag = false;
}


bool SFVplatformPose::roll()
{
	if (was_rolled_flag)
	{
		std::cout << "\033[1;31m I already was rolled (I am Initial Platform Pose) \033[0m"<< std::endl;
		return(false);
	}
	else
	{
		int roll_attemps_limit = 3;
		int roll_attemp=1;
		while (roll_attemp <= roll_attemps_limit)
		{
			initial_platform_position_on_map_X_axis->roll();
			initial_platform_position_on_map_Y_axis->roll();
			initial_platform_azimut->roll();

		if (get_ParentSFV()->rules_check())
			{
			was_rolled_flag = true;
			std::cout << "\033[1;32m Succeed to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			return(true);
			}
		else
			{
			initial_platform_position_on_map_X_axis = new ScenarioFeature(this->get_InitPlatformPoseX());
			initial_platform_position_on_map_Y_axis = new ScenarioFeature(this->get_InitPlatformPoseY());
			initial_platform_azimut = new ScenarioFeature(this->get_InitPlatformPoseAzimut());
			std::cout << "\033[1;35m fail to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			}
		roll_attemp++;
		}
	return(false);
	}
}


std::map<char,float> * SFVplatformPose::get_PlatInit_xy()
{
	SFV * sfv = get_ParentSFV();
	if(! sfv->get_WasRolledFlag())
	{
		std::cout << " can't calculate Platform Initial (x,y) as the SFV wasn't fully rolled " << std::endl;
		return 0;
	}

	std::map<char,float> * Palt_xy = new std::map<char,float>;

	SFVplatformPose *sfv_platPose = ((std::vector<SFVplatformPose*> *)sfv->get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType::platform_pose))->at(0);
	SFVterraine *sfv_terraine = ((std::vector<SFVterraine*> *)sfv->get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType::map))->at(0);

	//load terrain
	std::string terrain_name=ResourceHandler::getInstance(sfv->get_ResourceFile()).getTerrainById(sfv_terraine->get_TopographicMapIndex()->get_WasRolledFlag());
	std::string teraine_file_url = ResourceHandler::getInstance(sfv->get_ResourceFile()).getWorldModelsFolderURL();
	TerrainAnalyzer* terrainA=new TerrainAnalyzer();
	terrainA->loadFile(teraine_file_url+"/"+terrain_name);

	//get platform initial position
	float plat_init_x , plat_init_y, plat_init_z ;
	terrainA->getXYZCoord(sfv_platPose->get_InitPlatformPoseX()->get_RolledValue(),sfv_platPose->get_InitPlatformPoseY()->get_RolledValue(),plat_init_x, plat_init_y ,plat_init_z);

	Palt_xy->insert(std::pair<char,float>('x',plat_init_x) );
	Palt_xy->insert(std::pair<char,float>('y',plat_init_y) );
	return(Palt_xy);
}


TiXmlElement * SFVplatformPose::ToXmlElement(int id)
{
	if (! was_rolled_flag)
	{
		std::cout << "\033[1;31m can not make XML element for SFVplatformPose because it wasn't rolled yet \033[0m"<< std::endl;
		return(0);
	}
	else
	{
		TiXmlElement * xml_sub_group = new TiXmlElement(get_Type().str());
		xml_sub_group->SetAttribute("ID",std::to_string(id));

		xml_sub_group->LinkEndChild(initial_platform_position_on_map_X_axis->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(initial_platform_position_on_map_Y_axis->toSFV_XMLElement());
		xml_sub_group->LinkEndChild(initial_platform_azimut->toSFV_XMLElement());

		return(xml_sub_group);
	}
}

SFVplatformPose::~SFVplatformPose()
{

}




