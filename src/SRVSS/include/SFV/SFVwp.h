/*
 * SFVwp.h
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */

#ifndef SFVWP_H_
#define SFVWP_H_

#include <tinyxml.h>

#include "SFV/sfvSubGroup.h"

#include "SFDP/ScenarioFeature.h"
#include "SFV/SFV.h"


class SFVwp : public sfvSubGroup  {
private :
	ScenarioFeature * my_relative_angle;
	ScenarioFeature * my_relative_distance;
	bool was_rolled_flag;

public :
	SFVwp(std::vector<ScenarioFeature *> * ScenarioFeatures_vec, SFV * parent_SFV);
	SFVwp(SFVwp * template_SFVwp);

	bool roll();
	std::map<char,float> * get_WPxy(SFV *sfv);

	TiXmlElement * ToXmlElement(int id);


	~SFVwp();

	inline ScenarioFeature * get_RalativeAngel()
		{ return(my_relative_angle); }

	inline ScenarioFeature * get_RalativeDistance()
		{ return(my_relative_distance); }

	inline bool get_WasRolledFlag()
		{ return(was_rolled_flag); }



};




#endif /* SFVWP_H_ */
