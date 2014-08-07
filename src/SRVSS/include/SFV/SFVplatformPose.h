/*
 * SFVplatformPose.h
 *
 *  Created on: Aug 3, 2014
 *      Author: userws3
 */

#ifndef SFVPLATFORMPOSE_H_
#define SFVPLATFORMPOSE_H_


#include <iostream>
#include <string>

#include "SFV/sfvSubGroup.h"
#include "SFDP/ScenarioFeature.h"
#include "SFV/SFV.h"

class SFVplatformPose : public sfvSubGroup {
private :

	ScenarioFeature * initial_platform_position_on_map_X_axis;
	ScenarioFeature * initial_platform_position_on_map_Y_axis;
	ScenarioFeature * initial_platform_azimut;

	bool was_rolled_flag;

public :
	SFVplatformPose(std::vector<ScenarioFeature *> * ScenarioFeatures_vec, SFV * parent_SFV);
	SFVplatformPose(SFVplatformPose * template_SFVplatformPose);

	bool roll();
	std::map<char,float> * get_PlatInit_xy();

	TiXmlElement * ToXmlElement(int id);

	~SFVplatformPose();

	inline ScenarioFeature * get_InitPlatformPoseX()
		{ return(initial_platform_position_on_map_X_axis); }

	inline ScenarioFeature * get_InitPlatformPoseY()
		{ return(initial_platform_position_on_map_Y_axis); }

	inline ScenarioFeature * get_InitPlatformPoseAzimut()
			{ return(initial_platform_azimut); }

	inline bool get_WasRolledFlag()
		{ return(was_rolled_flag); }

};





#endif /* SFVPLATFORMPOSE_H_ */
