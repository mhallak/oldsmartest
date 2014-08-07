/*
 * SFVobstacleOnPath.h
 *
 *  Created on: Aug 5, 2014
 *      Author: userws3
 */

#ifndef SFVOBSTACLEONPATH_H_
#define SFVOBSTACLEONPATH_H_

#include <vector>
#include "SFV/SFV.h"

class SFVObstacleOnPath : public sfvSubGroup  {
private :
	ScenarioFeature * my_obstacle_type;
	ScenarioFeature * my_scaling_factor;

	ScenarioFeature * my_location_along_the_path;
	ScenarioFeature * my_location_perpendicular_to_the_path;
	ScenarioFeature * my_location_on_the_Z_axis;

	ScenarioFeature * my_location_Roll;
	ScenarioFeature * my_location_Pitch;
	ScenarioFeature * my_location_Yaw;

	bool was_rolled_flag;

public :
	SFVObstacleOnPath(std::vector<ScenarioFeature *> * ScenarioFeatures_vec, SFV * parent_SFV);
	SFVObstacleOnPath(SFVObstacleOnPath * template_SFVObstacleOnPath);

	bool roll();
	std::map<char,float> * get_Obstacle_xy();

	TiXmlElement * ToXmlElement(int id);

	~SFVObstacleOnPath();


	inline ScenarioFeature * get_ObstacleType()
		{ return(my_obstacle_type); }

	inline ScenarioFeature * get_ScalingFactor()
		{ return(my_scaling_factor); }

	inline ScenarioFeature * get_LocationAlongThePath()
		{ return(my_location_along_the_path); }

	inline ScenarioFeature * get_LocationmyPerpendicularToPath()
		{ return(my_location_perpendicular_to_the_path); }

	inline ScenarioFeature * get_LocationOnTheZaxis()
		{ return(my_location_on_the_Z_axis); }

	inline ScenarioFeature * get_LocationRoll()
		{ return(my_location_Roll); }

	inline ScenarioFeature * get_LocationPitch()
		{ return(my_location_Pitch); }

	inline ScenarioFeature * get_LocationYaw()
		{ return(my_location_Yaw); }


	inline bool get_WasRolledFlag()
		{ return(was_rolled_flag); }

};


#endif /* SFVOBSTACLEONPATH_H_ */
