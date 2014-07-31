/*
 * SFV2objScattering.h
 *
 *  Created on: Jul 31, 2014
 *      Author: userws3
 */

#ifndef SFV2OBJSCATTERING_H_
#define SFV2OBJSCATTERING_H_


#include <vector>

#include "SFDP/ScenarioFeature.h"
#include "TestSFV/SFV2Object.h"

class SFV2objScattering : public sfvSubGroup  {
private :
	ScenarioFeature * my_num_of_objects;
	SFV2Object * my_object_template;
	std::vector <SFV2Object *> * my_Objects;

	bool was_rolled_flag;

public :
	SFV2objScattering(std::vector<ScenarioFeature *> * ScenarioFeatures_vec);
	SFV2objScattering(SFV2objScattering * template_SFV2objScattering);

	void roll();


	~SFV2objScattering();


	inline ScenarioFeature * get_NumberOfObjects()
		{ return(my_num_of_objects); }

	inline std::vector<SFV2Object *> * get_Objects()
		{ if (! my_Objects->empty() ) { return my_Objects; }
		  else { std::cout << "\033[1;31m Objects vector is empty \033[0m" << std::endl; return(0); } }

	inline SFV2Object * get_ObjectTemplate()
		{ return(my_object_template); }

	inline bool get_WasRolledFlag()
		{ return(was_rolled_flag); }

};


#endif /* SFV2OBJSCATTERING_H_ */
