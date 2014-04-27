/*
 * SRVSSSyncronizer.h
 *
 *  Created on: Apr 24, 2014
 *      Author: userws1
 */

#ifndef SRVSSSYNCRONIZER_H_
#define SRVSSSYNCRONIZER_H_
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <vector>
#include <string>
#include "Executor.h"

class SRVSSSyncronizer {
	Executor* serverExecutor;
	Executor* guiExecutor;
	void runAux(std::vector<std::string> arguments);
	void startServer(std::vector<std::string> args);
	void startGui(std::vector<std::string> args);
	void stopServer();
	void stopGui();
public:
	SRVSSSyncronizer();
	virtual ~SRVSSSyncronizer();
	void runSimulation(std::string sfvfileName);
	void spawnModel(std::string sdffileName,std::string modelname,float x,float y,float z,float yaw);
	void stopSimulation();
};

#endif /* SRVSSSYNCRONIZER_H_ */
