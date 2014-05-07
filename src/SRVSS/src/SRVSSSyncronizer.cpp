/*
 * SRVSSSyncronizer.cpp
 *
 *  Created on: Apr 24, 2014
 *      Author: userws1
 */

#include "SRVSSSyncronizer.h"
#include <boost/filesystem.hpp>
#include "gazebo/common/Console.hh"
#include "gazebo/Server.hh"
#include "gazebo/gui/GuiIface.hh"


void SRVSSSyncronizer::startServer(std::vector<std::string> args)
{
	std::stringstream ss;
	//ss<<"gzserver";
	ss<<"/opt/ros/hydro/lib/gazebo_ros/gzserver";
	for(int i=0;i<args.size();i++)
	{
		ss<<" ";
		ss<<args.at(i);
	}
	serverExecutor=new Executor(ss.str());
	serverExecutor->executeCommand();
}

void SRVSSSyncronizer::startGui(std::vector<std::string> args)
{
	std::stringstream ss;
	//ss<<"gzclient";
	ss<<"/opt/ros/hydro/lib/gazebo_ros/gzclient";
	for(int i=0;i<args.size();i++)
	{
		ss<<" ";
		ss<<args.at(i);
	}
	guiExecutor=new Executor(ss.str());
	guiExecutor->executeCommand();
}

void SRVSSSyncronizer::stopServer()
{
	serverExecutor->killProgram();
}
void SRVSSSyncronizer::stopGui()
{
	guiExecutor->killProgram();
}


int RunCommand(const char *strCommand)
{
	int iForkId, iStatus;
	iForkId = vfork();
	if (iForkId == 0)	// This is the child
	{
		sleep(20);
		iStatus = execl("/bin/sh","sh","-c", strCommand, (char*) NULL);
		exit(iStatus);	// We must exit here,
				// or we will have multiple
				// mainlines running...
	}
	else if (iForkId > 0)	// Parent, no error
	{
		iStatus = 0;
	}
	else	// Parent, with error (iForkId == -1)
	{
		iStatus = -1;
	}
	return(iStatus);
}

SRVSSSyncronizer::SRVSSSyncronizer() {
	// TODO Auto-generated constructor stub

}

SRVSSSyncronizer::~SRVSSSyncronizer() {
	// TODO Auto-generated destructor stub
}



void SRVSSSyncronizer::runSimulation(std::string sfvfileName)
{

	boost::filesystem::path p(sfvfileName);
	boost::filesystem::path full_p = boost::filesystem::absolute(p);
	std::vector<std::string> args;
	//args.push_back("quiet");
	args.push_back(full_p.c_str());

	std::stringstream ss;

//	ss<<"roslaunch srvss_pkg srvss_bobcat_world.launch";
//	RunCommand(ss.str().c_str());

//	ss<<"roslaunch srvss_pkg srvss_bobcat_controllers.launch";
//	RunCommand(ss.str().c_str());

//	ss<<"rosrun gazebo_ros gazebo ";
//	std::cout << ss.str() << std::endl;
//	RunCommand(ss.str().c_str());

	startServer(args);
	startGui(args);
}
void stopSimulation()
{

}

void SRVSSSyncronizer::spawnModel(std::string sdffileName,std::string modelname,float x,float y,float z,float yaw)
{
	boost::filesystem::path p(sdffileName);
	boost::filesystem::path full_p = boost::filesystem::absolute(p);
	std::stringstream ss;
	ss<<"rosrun gazebo_ros spawn_model -sdf -file ";
	ss<<full_p.c_str() << " -model "<<modelname << " -x " << x << " -y " << y<< " -z " << z << " -Y " <<yaw;
	std::cout << ss.str() << std::endl;
	RunCommand(ss.str().c_str());
}
