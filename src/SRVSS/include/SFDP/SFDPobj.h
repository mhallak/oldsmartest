/*
 * SFDPobj.h
 *
 *  Created on: Jul 1, 2014
 *      Author: userws3
 */

#ifndef SFDPOBJ_H_
#define SFDPOBJ_H_

#include <string>
#include <vector>
#include <map>

#include "SFDP/ScenarioFeatureGroup.h"
#include "SFDP/ScenarioFeatureType.h"
#include "ScenarioFeatureDistributionType.h"

#include "SFV/SFVComponent.h"


class SFDPobj {
	private :
		std::vector<ScenarioFeatureGroup*> * my_featureGroups; // stores the SFDP

		std::string my_SFDP_file_url;
		std::string my_Resources_file_url;
		std::string my_WS_url;     					  // all output files will be created in this folder
		int my_division_level;

		std::vector<SFVComponent *> * my_sampled_SFVs;   // vector of sampled SFVs

		bool have_been_run;								// Flag to show that the Grades have been calculated
		float my_Grade_mean;    		 				// Grade refers to the my_sampled_SFVs
		float my_Grade_std;

		std::vector<SFDPobj *> * my_sub_SFDPs;			// vector of sub SFDPs

	public :

		SFDPobj(std::string SFDP_file_url, std::string Resources_file_url, std::string WS_url, int division_level);
		~SFDPobj();

		int ParseMeFromFile(std::string SFDP_file_url);
		int PrintMeToFile(std::string File_name);

		SFDPobj * ShrinkMe(ScenarioFeatureType * FeatureToShrink, float new_upper_bound_percents, float new_lower_bound_percents);
		std::vector<SFDPobj *> * SplitkMe(ScenarioFeatureType * FeatureToSplit, float split_percents);


		SFVComponent* genSFVComp();
		int GenMySFVs(int samp_num);
		int RunMySFVs();

		inline std::string get_SFDP_file_url()
			{ return my_SFDP_file_url; }

		inline std::string get_Resources_file_url()
			{ return my_Resources_file_url; }

		inline std::string get_WS_url()
			{ return my_WS_url; }

		inline int get_division_level()
			{ return my_division_level; }

		inline float get_Garade_mean()
			{ if (have_been_run) return my_Grade_mean; else return 0; }

		inline float get_Garade_std()
			{ if (have_been_run) return my_Grade_std; else return 0; }

		inline std::vector<ScenarioFeatureGroup*> * get_FeatureGroups()
			{if (! my_featureGroups->empty() ) return my_featureGroups; else return 0; }

		inline std::vector<SFVComponent *> * get_Sampled_SFVs()
			{if (! my_sampled_SFVs->empty() ) return my_sampled_SFVs; else return 0; }

		inline std::vector<SFDPobj *> * get_Sub_SFDPs()
			{if (! my_sub_SFDPs->empty() ) return my_sub_SFDPs; else return 0; }

};


#endif /* SFDPOBJ_H_ */