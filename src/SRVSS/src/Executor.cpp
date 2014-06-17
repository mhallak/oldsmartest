/*
 * Executor.cpp
 *
 *  Created on: Apr 27, 2014
 *      Author: userws1
 */

#include "Executor.h"
#include <boost/tokenizer.hpp>


Executor::Executor(std::string command)
{
	std::cout<< command <<std::endl;
	sig_killed=false;
	killed=false;

	boost::char_separator<char> sep(" ");
	boost::tokenizer<boost::char_separator<char> > tokens(command, sep);


	argvs = new char*[std::distance(tokens.begin(),tokens.end())+1];
	int i=0;
	for ( boost::tokenizer<boost::char_separator<char> >::iterator it = tokens.begin();
			 it != tokens.end();
			 ++it)
	{
		argvs[i]= const_cast<char*>((*it).c_str());
		i++;
	}
	argvs[i]= static_cast<char*>(NULL);
}

Executor::~Executor()
{
	// TODO Auto-generated destructor stub
}

void Executor::executeCommand()
{
	pid1=fork();
	if (pid1 == 0)
	{
		std::cout<< "cout:child proccess activated"<<std::endl;
		execvp(argvs[0],argvs);
		std::cout<< "cout:child proccess ended"<<std::endl;
		//exit(0);
	}
}

void Executor::killProgram()
{
	kill(pid1, SIGTERM);
}
