/*
 * GazeboExecutor.cpp
 *
 *  Created on: Jul 7, 2014
 *      Author: userws3
 */

#include <string>
#include <iostream>

#include "Executor/GazeboExecutor.h"
#include "Executor/scenarioLauncher.h"

#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"

#include <tinyxml.h>
#include "utils/TinyXmlDef.h"

GazeboExecutor::GazeboExecutor(std::string Scenario_folder_url)
{
	my_Scenario_folder_url = Scenario_folder_url;
	my_Grades_file_url = Scenario_folder_url + "/SFV_execution_grades.xml";
	was_executed_flag = false;
}

double temp_grade;
void scen_grade_Callback(const std_msgs::Float32MultiArray::ConstPtr &msg)
{
	temp_grade = msg->data[0];
}

int GazeboExecutor::RunScenario(int argc, char** argv)
{

	ros::init(argc, argv, "test_node");
	ros::NodeHandle n;
	ros::Subscriber model_states_sub;

	bool end_scen_flag = false;

	ScenarioLauncher *launcher = new ScenarioLauncher();
	launcher->start_launcher();

	launcher->setScenarioEnv(my_Scenario_folder_url);
	std::cout << "\033[1;31m Scenario Env_Variables are loaded !!! \033[0m" << std::endl;

	launcher->startGazeboServer(my_Scenario_folder_url);
	std::cout << "\033[1;31m GazeboServer is loaded !!! \033[0m" << std::endl;

	launcher->launchGazeboClient();
	std::cout << "\033[1;31m GazeboClient is loaded !!! \033[0m" << std::endl;

	launcher->launchPlatformControls();
	std::cout << "\033[1;31m Platform is loaded !!! \033[0m" << std::endl;

	launcher->launchWPdriver(my_Scenario_folder_url);
	std::cout << "\033[1;31m WP driver is loaded !!! \033[0m" << std::endl;

	launcher->launchTFbroadcaster();
	std::cout << "\033[1;31m TF publishing is loaded !!! \033[0m" << std::endl;

	launcher->launchRecorder(my_Scenario_folder_url);
	std::cout << "\033[1;31m Recorder is loaded !!! \033[0m" << std::endl;

	launcher->launchGrader();
	std::cout << "\033[1;31m Grader is loaded !!! \033[0m" << std::endl;

	launcher->GazeboUnPause();
	std::cout << "\033[1;31m Gazebo is Playin !!! \033[0m" << std::endl;

	model_states_sub = n.subscribe("/srvss/greade", 100, scen_grade_Callback);
	ros::Duration scen_max_duration(1*60, 0);
	ros::Time begin_time = ros::Time::now();
	ros::Time now_time = ros::Time::now();
	while ( (! end_scen_flag) && ros::ok() && (now_time - begin_time < scen_max_duration))
		 {
		now_time = ros::Time::now();
		ros::spinOnce();
		 }

	//char c;
	//std::cin >>c;

	my_scenario_graede = temp_grade;
	was_executed_flag = true;
	ros::requestShutdown();
	launcher->stop_launcher();
	launcher->~ScenarioLauncher();


	return 1;
}


int GazeboExecutor::PrintResultsToFile()
{
	if (! was_executed_flag)
	{
		std::cout << " \033[1;31m can't print results file because the SFV havn't been executed yet \033[0m" << std::endl;
		return 0;
	}

	TiXmlDocument doc(my_Grades_file_url);
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild(decl);

	TiXmlElement * xml_results = new TiXmlElement( "SFV_execution_grades" );
	xml_results->SetAttribute("version","1.0");
	doc.LinkEndChild(xml_results);

	std::stringstream temp_ss;

	temp_ss.str("");
	temp_ss << my_scenario_graede;
	TiXmlElement * xml_min_dist = new TiXmlElement( "minimal_distant_grade" );
	TiXmlText * min_dist_val= new TiXmlText( temp_ss.str() );
	xml_min_dist->LinkEndChild(min_dist_val);
	doc.LinkEndChild(xml_min_dist);

	doc.SaveFile(my_Grades_file_url.c_str());
	std::cout << " printing Grades to file : " << my_Grades_file_url << std::endl;

	return 1;
}

