/*
 * ScenarioCoordinatorPoolDestroyer.cpp
 *
 *  Created on: Jul 23, 2014
 *      Author: userws1
 */
#include "ScenarioCoordinatorPoolDestroyer.h"
#include "ScenarioCoordinatorPool.h"


ScenarioCoordinatorPoolDestroyer::~ScenarioCoordinatorPoolDestroyer()
{
	for(auto cord: *_doomed->_coordinators)
	{
		delete cord;
	}
	Py_DECREF(_doomed->pClass);
	Py_DECREF(_doomed->pDict);
	Py_DECREF(_doomed->pModule);
	Py_DECREF(_doomed->pName);
	  // Finish the Python Interpreter
	Py_Finalize();
	delete _doomed;
}
