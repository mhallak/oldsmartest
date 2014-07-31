/*
 * SFV2.h
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */

#ifndef SFV2_H_
#define SFV2_H_

#include <iostream>
#include <vector>

#include "SFDP/SFDPobj.h"
#include "SFDP/ScenarioFeatureGroupType.h"
#include "TestSFV/sfvSubGroup.h"


class SFV2 : public sfvSubGroup {
	private :
		std::vector<sfvSubGroup *> * my_sfvSubGroups;

		bool was_rolled_flag;

	public:
		SFV2(SFDPobj * SFDP);

		void roll();


		~SFV2();


		inline std::vector<sfvSubGroup *> * get_sfvSubGroups()
			{ if (! my_sfvSubGroups->empty() ) { return my_sfvSubGroups; }
				  else { std::cout << "\033[1;31m SFV SubGroups vector is empty \033[0m" << std::endl; return(0); } }


		std::vector<sfvSubGroup*> * get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType GroupType);


		inline bool get_WasRolledFlag()
			{ return(was_rolled_flag); }

};





#endif /* SFV2_H_ */
