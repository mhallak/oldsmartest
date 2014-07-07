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
		std::string my_Algorithm_Under_Test_launch_file_url;
		std::string my_Greader_launch_file_url;

		std::string my_Scenario_folder_url;
		double my_scenario_graede;

	public :
		GazeboExecutor(std::string Algorithm_Under_Test_launch_file_url, std::string Greader_launch_file_url, std::string Scenario_folder_url);
		~GazeboExecutor();

		int RunScenario();

		inline double get_scenario_grade()
			{	return my_scenario_graede; }

		inline std::string get_Scenario_folder_url()
			{	return my_Scenario_folder_url; }

		inline std::string get_Algorithm_Under_Test_launch_file_url()
			{	return my_Algorithm_Under_Test_launch_file_url; }

		inline std::string get_Greader_launch_file_url()
			{	return my_Greader_launch_file_url; }

};



#endif /* GAZEBOEXECUTOR_H_ */
