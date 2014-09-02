/*
 * SchenarioCordinator.cpp
 *
 *  Created on: Jul 22, 2014
 *      Author: userws1
 */

#include "ScenarioCoordinator.h"


ScenarioCoordinator::ScenarioCoordinator(PyObject* pyInstance):
																m_pyInstance(pyInstance){}


void ScenarioCoordinator::startRosCore()
{
	PyObject_CallMethod(m_pyInstance, "startRosCore",  NULL);
}

/*
void ScenarioCoordinator::startGazeboServer(std::string arguments)
{
	PyObject_CallMethod(m_pyInstance, "startGazeboServer", "(s)", arguments.c_str() ,NULL);
}
*/

void ScenarioCoordinator::startGazeboServer(std::string arguments)
{
	PyObject_CallMethod(m_pyInstance, "runGazeboServer", "(s)", arguments.c_str() ,NULL);
}

void ScenarioCoordinator::launchGazeboClient()
{
	PyObject_CallMethod(m_pyInstance, "launchGazeboClient",  NULL);
}

void ScenarioCoordinator::stopRosCore()
{
	PyObject_CallMethod(m_pyInstance, "stopRosCore",  NULL);
}

void ScenarioCoordinator::stopGazeboServer()
{
	PyObject_CallMethod(m_pyInstance, "stopGazeboServer",  NULL);
}

void ScenarioCoordinator::runNode(std::string name,std::string package,std::string executable,std::string arguments)
{
	PyObject_CallMethod(m_pyInstance, "runNode","(ssss)",name.c_str(),package.c_str(),executable.c_str(),arguments.c_str(),  NULL);
}

void ScenarioCoordinator::killNode(std::string name)
{
	PyObject_CallMethod(m_pyInstance, "killNode","(s)",name.c_str(),  NULL);
}

void ScenarioCoordinator::killAllNodes()
{
	PyObject_CallMethod(m_pyInstance, "killAllNodes",  NULL);
}

ScenarioCoordinator::~ScenarioCoordinator()
{
	killAllNodes();
	stopGazeboServer();
	stopRosCore();
}

void ScenarioCoordinator::pauseSimulation()
{
	PyObject_CallMethod(m_pyInstance, "pauseSimulation",  NULL);
}

void ScenarioCoordinator::unpauseSimulation()
{
	PyObject_CallMethod(m_pyInstance, "unpauseSimulation",  NULL);
}

void ScenarioCoordinator::resetSimulation()
{
	PyObject_CallMethod(m_pyInstance, "unpauseSimulation",  NULL);
}

void ScenarioCoordinator::setScenarioEnv(std::string Scenarin_folder)
{
	PyObject_CallMethod(m_pyInstance, "setScenarioEnv", "(s)", Scenarin_folder.c_str() , NULL);
}


void ScenarioCoordinator::launch_platform_controls(std::string platform_pkg_name , std::string platform_launch_file)
{
	PyObject_CallMethod(m_pyInstance, "launch_platform_controls", "(ss)", platform_pkg_name.c_str() , platform_launch_file.c_str() , NULL);
}


/*
void ScenarioCoordinator::spawnGazeboEnv(std::string Env_fileName)
{
	PyObject_CallMethod(m_pyInstance, "loadEnvFile", "(s)" ,  Env_fileName.c_str() , NULL);
}
*/

