/*
 * SFVpath.h
 *
 *  Created on: Jul 30, 2014
 *      Author: userws3
 */

#ifndef SFV2PATH_H_
#define SFV2PATH_H_

#include <vector>

#include "SFDP/ScenarioFeature.h"
#include "TestSFV/SFVwp.h"

class SFV2path : public sfvSubGroup  {
private :
	ScenarioFeature * my_number_of_wp;
	SFVwp * my_wp_template;
	std::vector <SFVwp *> * my_PathWPs;

	bool was_rolled_flag;

public :
	SFV2path(std::vector<ScenarioFeature *> * ScenarioFeatures_vec);
	SFV2path(SFV2path * template_SFVpath);

	void roll();


	~SFV2path();


	inline ScenarioFeature * get_NumberOfWPs()
		{ return(my_number_of_wp); }

	inline std::vector<SFVwp *> * get_PathWPs()
		{ if (! my_PathWPs->empty() ) { return my_PathWPs; }
		  else { std::cout << "\033[1;31m Path WPs vector is empty \033[0m" << std::endl; return(0); } }

	inline SFVwp * get_WpTemplate()
		{ return(my_wp_template); }

	inline bool get_WasRolledFlag()
		{ return(was_rolled_flag); }

};



#endif /* SFV2PATH_H_ */
