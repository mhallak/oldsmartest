/*
 * SFV.h
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */

#ifndef SFV_H_
#define SFV_H_

#include <iostream>
#include <vector>

//#include "SFDP/SFDPobj.h"
#include "SFDP/ScenarioFeatureGroupType.h"
#include "SFV/sfvSubGroup.h"


class SFV : public sfvSubGroup {
	private :
		std::vector<sfvSubGroup *> * my_sfvSubGroups;

		bool was_rolled_flag;

	public:
//		SFV(SFDPobj * SFDP);
		SFV();
		void roll();


		~SFV();


		inline std::vector<sfvSubGroup *> * get_sfvSubGroups()
			{ if (! my_sfvSubGroups->empty() ) { return my_sfvSubGroups; }
				  else { std::cout << "\033[1;31m SFV SubGroups vector is empty \033[0m" << std::endl; return(0); } }


		std::vector<sfvSubGroup*> * get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType GroupType);


		inline bool get_WasRolledFlag()
			{ return(was_rolled_flag); }

};





#endif /* SFV_H_ */
