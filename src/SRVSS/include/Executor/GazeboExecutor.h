/*
 * GazeboExecutor.h
 *
 *  Created on: Jul 7, 2014
 *      Author: userws3
 */

#ifndef GAZEBOEXECUTOR_H_
#define GAZEBOEXECUTOR_H_

#include <string>

class GazeboExecutor {
	private :

		std::string my_Scenario_folder_url;
		std::string my_Grades_file_url;
		double my_scenario_graede;
		bool was_executed_flag;

	public :
		GazeboExecutor(std::string Scenario_folder_url);
		~GazeboExecutor();

		int RunScenario(int argc, char** argv);
		int PrintResultsToFile();

		inline double get_scenario_grade()
			{	return my_scenario_graede; }

		inline std::string get_Scenario_folder_url()
			{	return my_Scenario_folder_url; }

		inline bool get_wasExecutedFlag()
			{	return was_executed_flag;	}

		inline double get_ScenarioGraede()
			{	return my_scenario_graede; }
};



#endif /* GAZEBOEXECUTOR_H_ */
