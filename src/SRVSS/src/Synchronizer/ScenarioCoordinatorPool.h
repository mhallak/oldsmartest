/*
 * SchenarioCordinatorPool.h
 *
 *  Created on: Jul 22, 2014
 *      Author: userws1
 */

#ifndef SCENARIOCOORDINATORPOOL_H_
#define SCENARIOCOORDINATORPOOL_H_
#include "ScenarioCoordinator.h"
#include "ScenarioCoordinatorPoolDestroyer.h"
#include <vector>
#include <string>


class ScenarioCoordinatorPool
{
	protected :

		friend class ScenarioCoordinatorPoolDestroyer;
		virtual ~ScenarioCoordinatorPool();

	private:
		PyObject *pName, *pModule, *pDict,
	             *pClass;

		std::vector<ScenarioCoordinator*>* _coordinators;

		ScenarioCoordinatorPool();

		static ScenarioCoordinatorPoolDestroyer _destroyer;
		static ScenarioCoordinatorPool *_instance;



	public:
	static ScenarioCoordinatorPool *Instance();
		ScenarioCoordinator * genCoordinator(
								int gazebo_port,
									int ros_port,
										std::string gazebo_host="http://127.0.0.1",
											std::string ros_host="http://127.0.0.1");
};
#endif /* SCHENARIOCORDINATORPOOL_H_ */


