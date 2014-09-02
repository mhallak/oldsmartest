/*
 * SchenarioCordinator.h
 *
 *  Created on: Jul 22, 2014
 *      Author: userws1
 */

#ifndef SCENARIOCOORDINATOR_H_
#define SCENARIOCOORDINATOR_H_
#include <Python.h>
#include <string>
#include <sstream>

class ScenarioCoordinator
{
		PyObject* m_pyInstance;
	public:
		ScenarioCoordinator(PyObject* pyInstance);
		virtual ~ScenarioCoordinator();

	    void startRosCore();
	    void startGazeboServer(std::string arguments);
	    void launchGazeboClient();
	    void stopRosCore();
	    void stopGazeboServer();
	    void runNode(std::string name,std::string package,std::string executable,std::string arguments="");
	    void killNode(std::string name);
	    void killAllNodes();
	    void pauseSimulation();
	    void unpauseSimulation();
	    void resetSimulation();

//	    void spawnGazeboEnv(std::string Env_fileName);
	    void setScenarioEnv(std::string Scenarin_folder);
	    void launch_platform_controls(std::string platform_pkg_name , std::string platform_launch_file);



	    template<typename T>
	    void spawnGazeboModel(T *model)
	    {
	    	std::stringstream ss;
	    	ss << model->toXMLElement();
	    	PyObject_CallMethod(m_pyInstance, "spawnGazeboObject","(ss)",model->m_name.c_str(),"<include><uri>model://barrel1</uri><pose>0 0 0 0 0 0</pose><name>object3</name></include>",NULL);
	    }

	    /*
	    void test()
	    {
	    	PyObject_CallMethod(m_pyInstance, "spawnGazeboObject","(ss)","koko"
	    			,"<sdf version='1.4'><model name='cube1'><static>true</static><link name='link'><pose>0 0 0.5 0 0 0</pose><collision name='collision'><geometry><box><size>1 1 1</size></box></geometry></collision><visual name='visual'><geometry><box><size>1 1 1</size></box></geometry><material><script><uri>file://media/materials/scripts/gazebo.material</uri><name>Gazebo/Grey</name></script></material></visual></link></model></sdf>"
	    			,NULL);
	    }
	     */
};

#endif /* SCHENARIOCOORDINATOR_H_ */
