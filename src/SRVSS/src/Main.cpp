#include "SFDP/SDFPComponent.h"
#include "SFDP/SDFPParser.h"
#include "Resource/ResourceHandler.h"
#include "Generators/Gazebo/GazeboEnvironmentGenerator.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include "Generators/Gazebo/GazeboPlatformGenerator.h"
#include "Generators/Gazebo/GazeboMissionGenerator.h"
#include "SRVSSSyncronizer.h"
#include "Executor.h"
#define PATH std::string("")


void printUsage()
{
	std::cout << "usage:" <<std:: endl;
	std::cout <<"(1) <srvss> -gen <sdfp file> <sfv output> <resousc file> # will generate a sfv file according to the sfdp and resource files input " <<std:: endl;
	std::cout <<"(2) <srvss> -run <sfv output> <destination folder> <resousc file> # will generate the scenario and launch it" <<std:: endl;
	exit(1);
}
int main(int argc, char** argv)
{
	//Executor * exe=new Executor("rosrun gazebo_ros gazebo");
	//exe->executeCommand();
	while(1)
	{
		//std::cout<< " executing "<<std::endl;
	}
	if(argc<2)
	{
		std::cout << "ERROR : not enough parameters" <<std:: endl;
		printUsage();
	}else{
		if(std::string(argv[1]).compare("-gen")==0){
			if(argc<4){
				std::cout << "ERROR : not enough parameters" <<std:: endl;
				printUsage();
			}
		}else if(std::string(argv[1]).compare("-run")==0){
			if(argc<3){
				std::cout << "ERROR : not enough parameters" <<std:: endl;
				printUsage();
			}
		}else{
			std::cout << "ERROR : not a valid option" <<std:: endl;
			printUsage();
		}
	}


	if(std::string(argv[1]).compare("-gen")==0)
	{
		std::string resources_file_path = PATH + argv[4];
		SDFPParser SDFPpars;
			try
			{
				SDFPComponent *sfdpComp=SDFPpars.genSDFPFromFile(PATH+argv[2]);
				SFVComponent *sfvComp=sfdpComp->genSFV(resources_file_path);
				sfvComp->init();
				sfvComp->calc();
				sfvComp->genFileFromSFV(argv[3]);
			}
			catch(std::string &err)
			{
					std::cout<<err<<std::endl;
			}
	}

	if(std::string(argv[1]).compare("-run")==0)
	{
		SDFPParser SDFPpars;
		std::string scenarios_folder_path = PATH + argv[3];
		std::string resources_file_path = PATH + argv[4];
		try
		{
			SFVComponent *sfvComp=new SFVComponent(resources_file_path);
			sfvComp->genSFVFromFile(argv[2]);
			sfvComp->genFileFromSFV("testRun.sfv");
			GazeboMissionGenerator * missionGen=new GazeboMissionGenerator();
     		missionGen->generateMission(sfvComp,scenarios_folder_path+"/myMission.txt", resources_file_path);
     		missionGen->generateMission_ROBIL2(sfvComp,scenarios_folder_path+"/myMission_robil2", resources_file_path);

			GazeboPlatformGenerator * platGen=new GazeboPlatformGenerator();
			platGen->generatePlatform(sfvComp,scenarios_folder_path+"/platform.sdf", resources_file_path);

			GazeboEnvironmentGenerator * envGen=new GazeboEnvironmentGenerator();
			envGen->genEnvFromSFV(sfvComp,scenarios_folder_path+"/env.world", resources_file_path);

	//		SRVSSSyncronizer * sync=new SRVSSSyncronizer();
	//		sync->runSimulation("env.world");
	//		sync->spawnModel("platform.sdf",missionGen->getLastPlatformName(),missionGen->getLastXPose(),missionGen->getLastYPose(),missionGen->getLastZPose(),missionGen->getLastYawPose());
		}
		catch(std::string &err)
		{
			std::cout<<err<<std::endl;
		}
	}

	return 0;
}
