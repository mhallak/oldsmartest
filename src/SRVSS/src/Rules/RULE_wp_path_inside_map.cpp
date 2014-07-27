/*
 * RULE_WP_path_inside_map.cpp
 *
 *  Created on: Jun 23, 2014
 *      Author: userws3
 */


#include "Rules/RULE_wp_path_inside_map.h"
#include "Resource/ResourceHandler.h"
#include "Generators/Gazebo/TerrainAnalyzer.h"
#include "SFV/SFVComponent.h"
#include "SFV/SFVTerrain.h"

Rule_wp_path_inside_map::Rule_wp_path_inside_map() {
	// TODO Auto-generated constructor stub
}

Rule_wp_path_inside_map::~Rule_wp_path_inside_map() {
	// TODO Auto-generated destructor stub
}


bool Rule_wp_path_inside_map::isRuleValid(SFVComponent *sfvComp)
{
	std::cout << " !! checking Rule_wp_path_inside_map --- " ;

	std::vector<SFVPath *> *path_vec = sfvComp->getPaths();
	SFVPath * wp_path = path_vec->at(0);
	if (! wp_path->was_rolled)
		{
		std::cout << " path first wp hasn't been rolled yet, so the rule has no meaning for now - return true " << std::endl;
		return true;
		}
	else
		{
			std::vector<SFVTerrain *> *terrain_vec = sfvComp->getTerrains();
			SFVTerrain * terrain = terrain_vec->at(0);
			if (! terrain->was_rolled)
				{
				std::cout << " terrain hasn't been rolled yet, so the rule can't be evaluated - return false" << std::endl;
				return false;
				}

			std::vector<SFVPlatformPose*> *platformPoses_vec = sfvComp->getPlatformPoses();
			SFVPlatformPose * platformPose = platformPoses_vec->at(0);
			if (! platformPose->was_rolled)
				{
				std::cout << " platform initial position hasn't been rolled yet, so the rule can't be evaluated - return false" << std::endl;
				return false;
				}


		//load terrain
		std::string terrain_name=ResourceHandler::getInstance(sfvComp->m_resource_file_path).getTerrainById(terrain->getTerrainId());
		std::string teraine_file_url = ResourceHandler::getInstance(sfvComp->m_resource_file_path).getWorldModelsFolderURL();
		TerrainAnalyzer* terrainA=new TerrainAnalyzer();
		terrainA->loadFile(teraine_file_url+"/"+terrain_name);

		//get platform initial position
		float plat_init_x , plat_init_y, plat_init_z , plat_init_azi;
		terrainA->getXYZCoord(platformPose->getLocationX(),platformPose->getLocationY(),plat_init_x, plat_init_y ,plat_init_z);
		plat_init_azi = platformPose->getLocationAzimut();


		//set terrain bounds
		float xMax,yMax,xMin,yMin,temp;
		terrainA->getXYZCoord(0.95,0.95,xMax,yMax,temp);
		terrainA->getXYZCoord(0.05,0.05,xMin,yMin,temp);

		float wp_x=plat_init_x, wp_y=plat_init_y,  wp_azi = plat_init_azi;

		for (SFVWaypoint *wp : *(wp_path->m_objects) )
			{
				wp_azi = wp_azi + wp->getRelativeAngle();
				wp_x = wp_x + wp->getWpIDistanceI()*cos(wp_azi);
				wp_y = wp_y + wp->getWpIDistanceI()*sin(wp_azi);

				if(wp_x<xMin || wp_y<yMin || wp_x>xMax || wp_y>yMax)
				{
					std::cout << " last wp : wp_x="<< wp_x <<" wp_y=" << wp_y << " is outside map bounds min_x="<< xMin <<" max_x=" << xMax <<" min_y="<< yMin <<" max_y=" << yMax << " - return false" << std::endl;
					return false; // last wp was outside map bounds
				}
			}
		std::cout << " all path wp are inside map bounds - return true" << std::endl;
		return true; // all the wp are inside map bounds
		}
}








