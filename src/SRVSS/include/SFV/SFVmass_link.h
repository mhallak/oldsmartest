/*
 * SFVmass_link.h
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */

#ifndef SFVMASS_LINK_H_
#define SFVMASS_LINK_H_

#include <iostream>
#include <string>

#include "SFV/sfvSubGroup.h"
#include "SFDP/ScenarioFeature.h"


class SFVmass_link : public sfvSubGroup {
private :

	std::string my_MassLinkName;

	ScenarioFeature * mass_deviation;
	ScenarioFeature * inertia_deviation_Ixx_component;
	ScenarioFeature * inertia_deviation_Iyy_component;
	ScenarioFeature * inertia_deviation_Izz_component;
	ScenarioFeature * location_deviation_X;
	ScenarioFeature * location_deviation_Y;
	ScenarioFeature * location_deviation_Z;
	ScenarioFeature * location_deviation_Roll;
	ScenarioFeature * location_deviation_Pitch;
	ScenarioFeature * location_deviation_Yaw;

	bool was_rolled_flag;

public :
	SFVmass_link(std::string MassLinkName ,std::vector<ScenarioFeature *> * ScenarioFeatures_vec);
	SFVmass_link(SFVmass_link * template_SFVmass_link);

	void roll();

	~SFVmass_link();

	inline std::string get_Name()
		{ return(my_MassLinkName); }


	inline ScenarioFeature * get_MassDeviation()
		{ return(mass_deviation); }

	inline ScenarioFeature * get_InertiaDeviationIxxComponent()
		{ return(inertia_deviation_Ixx_component); }

	inline ScenarioFeature * get_InertiaDeviationIyyComponent()
		{ return(inertia_deviation_Iyy_component); }

	inline ScenarioFeature * get_InertiaDeviationIzzComponent()
		{ return(inertia_deviation_Izz_component); }

	inline ScenarioFeature * get_LocationDeviationX()
		{ return(location_deviation_X); }

	inline ScenarioFeature * get_LocationDeviationY()
		{ return(location_deviation_Y); }

	inline ScenarioFeature * get_LocationDeviationZ()
		{ return(location_deviation_Z); }

	inline ScenarioFeature * get_LocationDeviationRoll()
		{ return(location_deviation_Roll); }

	inline ScenarioFeature * get_LocationDeviationPitch()
		{ return(location_deviation_Pitch); }

	inline ScenarioFeature * get_LocationDeviationYaw()
		{ return(location_deviation_Yaw); }


	inline bool get_WasRolledFlag()
		{ return(was_rolled_flag); }


};



#endif /* SFVMASS_LINK_H_ */
