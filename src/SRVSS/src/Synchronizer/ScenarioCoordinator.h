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
	    void startGazeboServer();
	    void launchGazeboClient();
	    void stopRosCore();
	    void stopGazeboServer();
	    void runNode(std::string name,std::string package,std::string executable,std::string arguments="");
	    void killNode(std::string name);
	    void killAllNodes();
	    void pauseSimulation();
	    void unpauseSimulation();
	    void resetSimulation();
	    template<typename T>
	    void spawnGazeboModel(T *model)
	    {
	    	std::stringstream ss;
	    	ss << model->toXMLElement();
	    	PyObject_CallMethod(m_pyInstance, "spawnGazeboObject","(ss)",model->m_name.c_str()," <include><uri>model://barrel1</uri><pose>55.8906 60.3694 -0.0652491 0.0544623 -0.0161914 0.0959575</pose><scale>4.34978 4.34978 4.34978</scale><name>object3</name></include>",NULL);
	    }

};

#endif /* SCHENARIOCOORDINATOR_H_ */
