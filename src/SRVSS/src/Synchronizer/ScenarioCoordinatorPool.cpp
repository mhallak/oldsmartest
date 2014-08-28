/*
 * SchenarioCordinatorPool.cpp
 *
 *  Created on: Jul 22, 2014
 *      Author: userws1
 */

#include "ScenarioCoordinatorPool.h"
#include <Python.h>
#include "stdlib.h"
#include <sstream>
ScenarioCoordinatorPool *ScenarioCoordinatorPool::_instance = 0;
ScenarioCoordinatorPoolDestroyer ScenarioCoordinatorPool::_destroyer;
ScenarioCoordinatorPool::ScenarioCoordinatorPool()
{
	_coordinators=new std::vector<ScenarioCoordinator*>;

	Py_Initialize();
	char *g="";
	PySys_SetArgv(1, &g);
	// Build the name object
	pName = PyString_FromString("cordinator");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference
	pDict = PyModule_GetDict(pModule);

	// Build the name of a callable class
	pClass = PyDict_GetItemString(pDict, "SimCordinator");
}

ScenarioCoordinator * ScenarioCoordinatorPool::genCoordinator(int gazebo_port,int ros_port,std::string gazebo_host ,std::string ros_host)
{
	PyObject* pArgs = PyTuple_New(4);
	std::stringstream ss;
	ss<< gazebo_port;
	PyTuple_SetItem(pArgs,0,PyString_FromString(ss.str().c_str()));
	ss.str("");
	ss<<ros_port;
	PyTuple_SetItem(pArgs,1,PyString_FromString(ss.str().c_str()));
	PyTuple_SetItem(pArgs,2,PyString_FromString(gazebo_host.c_str()));
	PyTuple_SetItem(pArgs,3,PyString_FromString(ros_host.c_str()));

	PyObject *pInstance;
	 // Create an instance of the class
	if (PyCallable_Check(pClass))
	{
	  pInstance = PyObject_CallObject(pClass,pArgs);
	}
	_coordinators->push_back(new ScenarioCoordinator(pInstance));
	return _coordinators->back();
}


ScenarioCoordinatorPool *ScenarioCoordinatorPool::Instance() {
	if (!_instance) {
		_instance = new ScenarioCoordinatorPool;
		_destroyer.SetDoomed(_instance);
	}
	return _instance;
}

ScenarioCoordinatorPool::~ScenarioCoordinatorPool()
{

}

