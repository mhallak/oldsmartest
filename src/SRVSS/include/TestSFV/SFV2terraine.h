/*
 * SFV2terraine.h
 *
 *  Created on: Jul 31, 2014
 *      Author: userws3
 */

#ifndef SFV2TERRAINE_H_
#define SFV2TERRAINE_H_


#include <iostream>
#include <string>

#include "TestSFV/sfvSubGroup.h"
#include "SFDP/ScenarioFeature.h"


class SFV2terraine : public sfvSubGroup {
private :

	ScenarioFeature * topographic_map_index;

	bool was_rolled_flag;

public :
	SFV2terraine(std::vector<ScenarioFeature *> * ScenarioFeatures_vec);
	SFV2terraine(SFV2terraine * template_SFV2terraine);

	void roll();

	~SFV2terraine();

	inline ScenarioFeature * get_TopographicMapIndex()
		{ return(topographic_map_index); }

	inline bool get_WasRolledFlag()
		{ return(was_rolled_flag); }

};




#endif /* SFV2TERRAINE_H_ */
