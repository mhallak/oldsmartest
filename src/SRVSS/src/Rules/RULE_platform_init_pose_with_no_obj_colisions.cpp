/*
 * RULE_platform_init_pose_with_no_obj_colisions.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: userws3
 */


#include "Rules/RULE_platform_init_pose_with_no_obj_colisions.h"
#include "SFV/SFVComponent.h"
#include "Resource/ResourceHandler.h"
#include "Generators/Gazebo/TerrainAnalyzer.h"
#include <math.h>

#include <iostream>


Rule_platform_init_pose_with_no_obj_colisions::Rule_platform_init_pose_with_no_obj_colisions() {
	// TODO Auto-generated constructor stub
}

Rule_platform_init_pose_with_no_obj_colisions::~Rule_platform_init_pose_with_no_obj_colisions() {
	// TODO Auto-generated destructor stub
}


bool Rule_platform_init_pose_with_no_obj_colisions::isRuleValid(SFVComponent *sfvComp)
{
		std::cout << " !! checking Rule_platform_init_pose_with_no_obj_colisions  --- ";

		std::vector<SFVPlatformPose*> *platformPoses_vec = sfvComp->getPlatformPoses();
		SFVPlatformPose * platformPose = platformPoses_vec->at(0);
		if (! platformPose->was_rolled)
			{
			std::cout << " platform initial position hasn't been rolled yet, so the rule have no meaning for now  - return true" << std::endl;
			return true;
			}

		std::vector<SFVObjects*> * Objects_vec = sfvComp->getObjects();
		SFVObjects * objects = Objects_vec->at(0);
		if (! objects->was_rolled)
			{
			std::cout << " no Object was rolled yet, so the rule has no meaning for now  - return true" << std::endl;
			return true;
			}

		std::vector<SFVTerrain *> *terrain_vec = sfvComp->getTerrains();
		SFVTerrain * terrain = terrain_vec->at(0);
		if (! terrain->was_rolled)
			{
			std::cout << " terrain hasn't been rolled yet, so the rule can't be evaluated - return false" << std::endl;
			return false; // terrain is needed for translation of percents to distance
			}

		//load terrain
		std::string terrain_name=ResourceHandler::getInstance(sfvComp->m_resource_file_path).getTerrainById(terrain->getTerrainId());
		std::string teraine_file_url = ResourceHandler::getInstance(sfvComp->m_resource_file_path).getModelsPath();
		TerrainAnalyzer* terrainA=new TerrainAnalyzer();
		terrainA->loadFile(teraine_file_url+"/"+terrain_name);

		//get platform initial position
		float plat_init_x , plat_init_y, plat_init_z;
		terrainA->getXYZCoord(platformPose->getLocationX(),platformPose->getLocationY(),plat_init_x, plat_init_y ,plat_init_z);

		for (SFVObject *obj : *(objects->m_objects) )
			{
			// TODO platform and objects orientation shall be also taken to consideration

				float obj_x, obj_y, obj_z;
				terrainA->getXYZCoord(obj->getX(),obj->getY(),obj_x, obj_y ,obj_z);

				float dx = plat_init_x - obj_x;
				float dy = plat_init_y - obj_y;

				float dis = std::sqrt(std::pow(dx,2) + std::pow(dy,2));

				if(dis <= 2.5)
				{
					std::cout << " object at obj_x="<< obj_x <<" obj_y=" << obj_y << " is closer than 2.5m to the platform at plat_x="<< plat_init_x <<" plat_y=" << plat_init_y <<" - return false" << std::endl;
					return false; // obj is closer than 5m to the platform
				}
			}
		std::cout << " all the obj are in distance of more than 5m from the bobcat - return true" << std::endl;
		return true; // all the obj are in distance of more than 5m from the bobcat
}








