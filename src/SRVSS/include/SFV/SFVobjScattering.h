/*
 * SFVobjScattering.h
 *
 *  Created on: Jul 31, 2014
 *      Author: userws3
 */

#ifndef SFVOBJSCATTERING_H_
#define SFVOBJSCATTERING_H_


#include <vector>

#include "SFDP/ScenarioFeature.h"
#include "SFV/SFVObject.h"
#include "SFV/SFV.h"


class SFVobjScattering : public sfvSubGroup  {
private :
	ScenarioFeature * my_num_of_objects;
	SFVObject * my_object_template;
	std::vector <SFVObject *> * my_Objects;

	bool was_rolled_flag;

public :
	SFVobjScattering(std::vector<ScenarioFeature *> * ScenarioFeatures_vec, SFV * parent_SFV);
	SFVobjScattering(SFVobjScattering * template_SFVobjScattering);

	bool roll();
	TiXmlElement * ToXmlElement(int id);

	~SFVobjScattering();


	inline ScenarioFeature * get_NumberOfObjects()
		{ return(my_num_of_objects); }

	inline std::vector<SFVObject *> * get_Objects()
		{ if (! my_Objects->empty() ) { return my_Objects; }
		  else { std::cout << "\033[1;31m Objects vector is empty \033[0m" << std::endl; return(0); } }

	inline SFVObject * get_ObjectTemplate()
		{ return(my_object_template); }

	inline bool get_WasRolledFlag()
		{ return(was_rolled_flag); }

};


#endif /* SFVOBJSCATTERING_H_ */
