/*
 * Executor.h
 *
 *  Created on: Apr 27, 2014
 *      Author: userws1
 */

#ifndef EXECUTOR_H_
#define EXECUTOR_H_
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <vector>
#include <string>

class Executor {

	bool sig_killed;
	int status1, status2;
	pid_t  pid1, pid2;
	bool killed;
	char **argvs;
public:
	Executor(std::string command);
	virtual ~Executor();
	void executeCommand();
	void killProgram();
};

#endif /* EXECUTOR_H_ */
