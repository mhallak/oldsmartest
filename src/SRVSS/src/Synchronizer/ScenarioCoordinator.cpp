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

void ScenarioCoordinator::startGazeboServer()
{
	PyObject_CallMethod(m_pyInstance, "startGazeboServer",  NULL);
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


