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
#include <string>

#include "SFDP/ScenarioFeatureGroupType.h"
#include "SFV/sfvSubGroup.h"

#include "SFDP/SFDPobj.h"

#include "Rules/Rule.h"


class SFDPobj;
class sfvSubGroup;

class SFV {
	private :
		std::vector<sfvSubGroup *> * my_sfvSubGroups;

		std::string my_resource_file_url;

		SFDPobj * my_SFDP;
		bool was_rolled_flag;

		std::vector<Rule *> * my_rules;

	public:
		SFV(SFDPobj * SFDP);
		SFV(std::string SFV_file_name);

		bool roll();
		bool rules_check();

		int printToXML(std::string sfv_file_url);

		~SFV();


		inline std::vector<sfvSubGroup *> * get_sfvSubGroups()
			{ if (! my_sfvSubGroups->empty() ) { return my_sfvSubGroups; }
				  else { std::cout << "\033[1;31m SFV SubGroups vector is empty \033[0m" << std::endl; return(0); } }


		inline std::string get_ResourceFile()
			{ return(my_resource_file_url); }

		inline SFDPobj * get_SFDP()
			{
			if (my_SFDP == 0) { std::cout << " the is no SFDP perent defined for this SFV, it probably was created from file " << std::endl; return(0); }
			else { return(my_SFDP); }
			}

		std::vector<sfvSubGroup*> * get_SubGroupsBayFeatureGroupType(ScenarioFeatureGroupType GroupType);

		void PopulationOf_mysfvSubGroups();

		template <class T>
		void PopulationOf_mysfvSubGroups1(ScenarioFeatureGroupType::optional scenarioFeatureType , T fatures_data);

		inline bool get_WasRolledFlag()
			{ return(was_rolled_flag); }

};





#endif /* SFV_H_ */
