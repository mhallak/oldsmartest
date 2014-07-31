/*
 * SFVterraine.h
 *
 *  Created on: Jul 31, 2014
 *      Author: userws3
 */

#ifndef SFVTERRAINE_H_
#define SFVTERRAINE_H_


#include <iostream>
#include <string>

#include "SFV/sfvSubGroup.h"
#include "SFDP/ScenarioFeature.h"


class SFVterraine : public sfvSubGroup {
private :

	ScenarioFeature * topographic_map_index;

	bool was_rolled_flag;

public :
	SFVterraine(std::vector<ScenarioFeature *> * ScenarioFeatures_vec);
	SFVterraine(SFVterraine * template_SFVterraine);

	void roll();

	~SFVterraine();

	inline ScenarioFeature * get_TopographicMapIndex()
		{ return(topographic_map_index); }

	inline bool get_WasRolledFlag()
		{ return(was_rolled_flag); }

};




#endif /* SFVTERRAINE_H_ */
