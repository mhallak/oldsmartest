#include "SFDP/SDFPComponent.h"
#include "SFDP/SDFPParser.h"
#include "Resource/ResourceHandler.h"
#include "Generators/Gazebo/GazeboEnvironmentGenerator.h"
#include <string>
#include <stdio.h>
#include <iostream>
#include "Generators/Gazebo/SDFIterator.h"
#include "Generators/Gazebo/GazeboPlatformGenerator.h"
#include "Generators/Gazebo/GazeboMissionGenerator.h"
#include "SRVSSSyncronizer.h"
#define PATH std::string("")


void printUsage()
{
	std::cout << "usage:" <<std:: endl;
	std::cout <<"(1) <srvss> -gen <sdfp file> <sfv output> # will generate a sfv file according to the sfdp input" <<std:: endl;
	std::cout <<"(2) <srvss> -run <sfv output> <destination folder>  #will generate the scenario and launch it" <<std:: endl;
	exit(1);
}
int main(int argc, char** argv)
{
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
		SDFPParser SDFPpars;
			try
			{
				SDFPComponent *sfdpComp=SDFPpars.genSDFPFromFile(PATH+argv[2]);
				SFVComponent *sfvComp=sfdpComp->genSFV();
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
		try
		{
			SFVComponent *sfvComp=new SFVComponent();
			sfvComp->genSFVFromFile(argv[2]);
			sfvComp->genFileFromSFV("testRun.sfv");
			GazeboMissionGenerator * missionGen=new GazeboMissionGenerator();
     		missionGen->generateMission(sfvComp,scenarios_folder_path+"myMission.txt");

			GazeboPlatformGenerator * platGen=new GazeboPlatformGenerator();
			platGen->generatePlatform(sfvComp,scenarios_folder_path+"platform.sdf");

			GazeboEnvironmentGenerator * envGen=new GazeboEnvironmentGenerator();
			envGen->genEnvFromSFV(sfvComp,scenarios_folder_path+"env.world");

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
