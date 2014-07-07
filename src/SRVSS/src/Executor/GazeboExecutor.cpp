/*
 * GazeboExecutor.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: userws3
 */

#include <string>

#include <random>
#include <chrono>

#include "Executor/GazeboExecutor.h"


GazeboExecutor::GazeboExecutor(std::string Algorithm_Under_Test_launch_file_url, std::string Greader_launch_file_url, std::string Scenario_folder_url)
{
	my_Scenario_folder_url = Algorithm_Under_Test_launch_file_url;
	my_Greader_launch_file_url = Greader_launch_file_url;
	my_Algorithm_Under_Test_launch_file_url = Scenario_folder_url;
}


int GazeboExecutor::RunScenario()
{
	// construct a trivial random generator engine from a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed);

	std::uniform_real_distribution<double> distribution(0.0,1.0);

	my_scenario_graede = distribution(generator);

	return 1;
}
