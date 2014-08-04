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
#include "SFV/SFV.h"


class SFVterraine : public sfvSubGroup {
private :

	ScenarioFeature * topographic_map_index;

	bool was_rolled_flag;

public :
	SFVterraine(std::vector<ScenarioFeature *> * ScenarioFeatures_vec, SFV * parent_SFV);
	SFVterraine(SFVterraine * template_SFVterraine);

	bool roll();

	TiXmlElement * ToXmlElement(int id);

	~SFVterraine();

	inline ScenarioFeature * get_TopographicMapIndex()
		{ return(topographic_map_index); }

	inline bool get_WasRolledFlag()
		{ return(was_rolled_flag); }

};




#endif /* SFVTERRAINE_H_ */
