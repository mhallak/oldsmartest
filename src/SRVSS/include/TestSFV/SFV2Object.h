/*
 * SFV2Object.h
 *
 *  Created on: Jul 31, 2014
 *      Author: userws3
 */

#ifndef SFV2OBJECT_H_
#define SFV2OBJECT_H_


#include "TestSFV/sfvSubGroup.h"
#include "SFDP/ScenarioFeature.h"


class SFV2Object : public sfvSubGroup  {
private :
	ScenarioFeature * my_object_type;
	ScenarioFeature * my_scaling_factor;
	ScenarioFeature * my_location_on_the_X_axis;
	ScenarioFeature * my_location_on_the_Y_axis;
	ScenarioFeature * my_location_on_the_Z_axis;
	ScenarioFeature * my_location_Roll;
	ScenarioFeature * my_location_Pitch;
	ScenarioFeature * my_location_Yaw;

	bool was_rolled_flag;

public :
	SFV2Object(std::vector<ScenarioFeature *> * ScenarioFeatures_vec);
	SFV2Object(SFV2Object * template_SFV2Object);

	void roll();

	~SFV2Object();


	inline ScenarioFeature * get_ObjectType()
		{ return(my_object_type); }

	inline ScenarioFeature * get_ScalingFactor()
		{ return(my_scaling_factor); }

	inline ScenarioFeature * get_LocationOnTheXaxis()
		{ return(my_location_on_the_X_axis); }

	inline ScenarioFeature * get_LocationOnTheYaxis()
		{ return(my_location_on_the_Y_axis); }

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



#endif /* SFV2OBJECT_H_ */
