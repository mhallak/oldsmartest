/*
 * GazeboExecutor.h
 *
 *  Created on: Jul 7, 2014
 *      Author: userws3
 */

#ifndef GAZEBOEXECUTOR_H_
#define GAZEBOEXECUTOR_H_

#include <string>
#include "Executor/scenarioLauncher.h"
#include "SFV/SFV.h"
#include "std_msgs/Float32MultiArray.h"


class GazeboExecutor {
	private :

		std::string my_Scenario_folder_url;
		std::string my_Grades_file_url;

		std::string my_pyInterface;

		//double my_scenario_graede;
		std_msgs::Float32MultiArray::ConstPtr  my_scenario_graede;
		bool was_executed_flag;

		ScenarioLauncher *my_launcher;

	public :
		GazeboExecutor(SFV *sfv);
		~GazeboExecutor();

		int RunScenario(int argc, char** argv);
		int PrintResultsToFile();

		inline double get_scenario_grade()
			{	return my_scenario_graede->data[0]; }

		inline std::string get_Scenario_folder_url()
			{	return my_Scenario_folder_url; }

		inline bool get_wasExecutedFlag()
			{	return was_executed_flag;	}


};



#endif /* GAZEBOEXECUTOR_H_ */
