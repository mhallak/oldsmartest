#include "SFDP/SDFPComponent.h"
#include "SFDP/SDFPParser.h"
#include "Resource/ResourceHandler.h"
#include "Generators/Gazebo/GazeboEnvironmentGenerator.h"
#include <string>
#include <stdio.h>
#include <iostream>

int main(int argc, char** argv)
{
	SDFPParser SDFPpars;
	try{
		SDFPComponent *sfdpComp=SDFPpars.genSDFPFromFile("template.SFDP");
		SFVComponent *sfvComp=sfdpComp->rollDice();
		sfvComp->genFileFromSFV("test.sfv");
		SFVComponent *sfvComp2=new SFVComponent();
		sfvComp2->genSFVFromFile("test.sfv");
		sfvComp2->genFileFromSFV("test2.sfv");
		GazeboEnvironmentGenerator * envGen=new GazeboEnvironmentGenerator();
		envGen->genEnvFromSFV(sfvComp,"env.world");
		delete sfdpComp;
		delete sfvComp;
	}catch(std::string &err)
	{
		std::cout<<err<<std::endl;
	}


	return 0;
}
