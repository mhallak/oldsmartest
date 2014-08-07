/*
 * SFVobstacaleOnPath.cpp
 *
 *  Created on: Aug 5, 2014
 *      Author: userws3
 */



#include <iostream>
#include <vector>
#include "SFV/SFV.h"
#include "SFV/SFVobstacleOnPath.h"
#include "SFV/SFVplatformPose.h"
#include "SFV/SFVpath.h"

#include "SFDP/ScenarioFeatureType.h"
#include "SFDP/ScenarioFeature.h"
#include "SFDP/ScenarioFeatureGroup.h"


void SFVObstacleOnPath::initFeaturesMap()
{
	std::map<ScenarioFeatureType ,ScenarioFeature** > * my_features_map = get_FeaturesMap();

    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::obstacle_on_path_i_type, & my_obstacle_type ) );
    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::obstacle_on_path_i_scaling_factor, & my_scaling_factor));

    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::obstacle_on_path_i_location_along_the_path, & my_location_along_the_path));
    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::obstacle_on_path_i_location_perpendicular_to_the_path, & my_location_perpendicular_to_the_path));
    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::obstacle_on_path_i_location_on_the_Z_axis, & my_location_on_the_Z_axis));

    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::obstacle_on_path_i_location_Roll,  & my_location_Roll));
    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::obstacle_on_path_i_location_Pitch, & my_location_Pitch));
    my_features_map->insert(std::pair<ScenarioFeatureType,ScenarioFeature**>(ScenarioFeatureType::obstacle_on_path_i_location_Yaw, & my_location_Yaw));
}



SFVObstacleOnPath::SFVObstacleOnPath(std::vector<ScenarioFeature *> * ScenarioFeatures_vec, SFV * parent_SFV): sfvSubGroup(ScenarioFeatureGroupType::obstacle_on_path, parent_SFV)
{
	initFeaturesMap();
	initSubGroupFeatures(ScenarioFeatures_vec);
	set_WasRolledFlag(false);
}


SFVObstacleOnPath::SFVObstacleOnPath(SFVObstacleOnPath * template_subGroup):  sfvSubGroup(template_subGroup->get_Type(), template_subGroup->get_ParentSFV())
{
	initFeaturesMap();
	cloneSubGroupFeatures(template_subGroup);
	set_WasRolledFlag(false);
}


bool SFVObstacleOnPath::roll()
{
	if (get_WasRolledFlag())
	{
		std::cout << "\033[1;31m I already was rolled (I am Object) \033[0m"<< std::endl;
		return(false);
	}
	else
	{
		int roll_attemps_limit = 3;
		int roll_attemp=1;
		while (roll_attemp <= roll_attemps_limit)
		{
			rollSubGroupfeatures();

		if (get_ParentSFV()->rules_check())
			{
			set_WasRolledFlag(true);
			return(true);
			std::cout << "\033[1;32m Succeed to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			}
		else
			{
			resetSubGroupfeatures();
			std::cout << "\033[1;35m fail to roll " << this->get_Type() << " attempt = " << roll_attemp << " / " << roll_attemps_limit << "\033[0m"<< std::endl;
			}
		roll_attemp++;
		}
	return(false);
	}
}




TiXmlElement * SFVObstacleOnPath::ToXmlElement(int id)
{
	if (! get_WasRolledFlag())
	{
		std::cout << "\033[1;31m can not make XML element for SFVObject because it wasn't rolled yet \033[0m"<< std::endl;
		return(0);
	}
	else
	{
		return(SubGroupfeaturesToXmlElement(id));
	}
}



std::map<char,float> * SFVObstacleOnPath::get_Obstacle_xy()
{
	SFV * sfv = get_ParentSFV();
	if(! sfv)
	{
		std::cout << " can't calculate WP_xy as the SFV wasn't fully rolled " << std::endl;
		return 0;
	}

	std::map<char,float> * Obs_xy = new std::map<char,float>;

	SFVplatformPose *sfv_platPose = ((std::vector<SFVplatformPose*> *)sfv->get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType::platform_pose))->at(0);
	SFVpath *sfv_path = ((std::vector<SFVpath*> *)sfv->get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType::Path))->at(0);

	double plat_x=sfv_platPose->get_PlatInit_xy()->at('x');
	double plat_y=sfv_platPose->get_PlatInit_xy()->at('y');
	double plat_init_azi = sfv_platPose->get_InitPlatformPoseAzimut()->get_RolledValue();


	double path_length = sfv_path->get_PathLength();
	double alo = this->get_LocationAlongThePath()->get_RolledValue();
	double per = this->get_LocationmyPerpendicularToPath()->get_RolledValue();
	double alo_path_pos = alo * path_length;
	//std::cout <<  "alo = " << alo <<  "  per = " << per << std::endl;

	double alon_path_dis = 0, azi = plat_init_azi, dis = 0, x=plat_x, y=plat_y, next_x=plat_x, next_y=plat_y;
	for (SFVwp *wp_it : *(sfv_path->get_PathWPs()) )
		{
		dis = wp_it->get_RalativeDistance()->get_RolledValue();
		next_x = wp_it->get_WPxy()->at('x');
		next_y = wp_it->get_WPxy()->at('y');

		if ( (alon_path_dis + dis) < alo_path_pos  )
			{
				alon_path_dis = alon_path_dis + dis;
				x = next_x;
				y = next_y;
				//std::cout <<  "wp_x = " << x <<  "  wp_y = " << y << std::endl;
			}
		else
			{
			break;
			}
		}

		double rem_alo = ((alo - alon_path_dis/path_length)*path_length)/dis;
		double obs_x = x + rem_alo * (next_x - x) - per*(next_y - y)/dis;
		double obs_y = y + rem_alo * (next_y - y) + per*(next_x - x)/dis;

		// std::cout <<  "obs_x = " << obs_x <<  "  obs_y = " << obs_y << std::endl;

		std::map<char,float> * Obstacle_xy = new std::map<char,float>;
		Obstacle_xy->insert(std::pair<char,float>('x',obs_x) );
		Obstacle_xy->insert(std::pair<char,float>('y',obs_y) );
		return(Obstacle_xy);
}


SFVObstacleOnPath::~SFVObstacleOnPath()
{

}



