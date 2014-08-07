/*
 * SFVsensor_link.h
 *
 *  Created on: Aug 5, 2014
 *      Author: userws3
 */

#ifndef SFVSENSOR_LINK_H_
#define SFVSENSOR_LINK_H_


#include <iostream>
#include <string>

#include "SFV/sfvSubGroup.h"
#include "SFDP/ScenarioFeature.h"
#include "SFV/SFV.h"

class SFVsensor_link : public sfvSubGroup {
private :

	std::string my_SensorLinkName;

	ScenarioFeature * location_deviationX;
	ScenarioFeature * location_deviationY;
	ScenarioFeature * location_deviationZ;
	ScenarioFeature * location_deviationRoll;
	ScenarioFeature * location_deviationPitch;
	ScenarioFeature * location_deviationYaw;

	bool was_rolled_flag;

public :
	SFVsensor_link(std::string FrictionLinkName ,std::vector<ScenarioFeature *> * ScenarioFeatures_vec,  SFV * parent_SFV);
	SFVsensor_link(SFVsensor_link * template_SFVsensor_link);

	bool roll();
	TiXmlElement * ToXmlElement(int id);

	~SFVsensor_link();

	inline std::string get_Name()
		{ return(my_SensorLinkName); }

	inline ScenarioFeature * get_LocationDeviationX()
		{ return(location_deviationX); }

	inline ScenarioFeature * get_LocationDeviationY()
		{ return(location_deviationY); }

	inline ScenarioFeature * get_LocationDeviationZ()
		{ return(location_deviationZ); }

	inline ScenarioFeature * get_LocationDeviationRoll()
		{ return(location_deviationRoll); }

	inline ScenarioFeature * get_LocationDeviationPitch()
		{ return(location_deviationPitch); }

	inline ScenarioFeature * get_LocationDeviationYaw()
		{ return(location_deviationYaw); }

	inline bool get_WasRolledFlag()
		{ return(was_rolled_flag); }

};


#endif /* SFVSENSOR_LINK_H_ */
