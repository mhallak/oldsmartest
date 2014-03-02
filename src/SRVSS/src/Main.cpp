#include "SFDP/SDFPComponent.h"
#include "SFDP/SDFPParser.h"
#include "SFV/SFVParser.h"
#include "Resource/ResourceHandler.h"
#include "Generators/EnvironmentGenerator.h"
#include <string>
#include <stdio.h>
#include <iostream>

int main(int argc, char** argv)
{
	SDFPParser SDFPpars;
	SFVParser SFVpars;
	try{
		SDFPComponent *sfdpComp=SDFPpars.genSDFPFromFile("template.SFDP");
		SFVComponent *sfvComp=sfdpComp->rollDice();
		SFVpars.genFileFromSFV("test.sfv",sfvComp);
		SFVComponent *sfvComp2=SFVpars.genSFVFromFile("test.sfv");
		SFVpars.genFileFromSFV("test2.sfv",sfvComp2);
		EnvironmentGenerator * envGen=new EnvironmentGenerator();
		envGen->genEnvFromSFV(sfvComp,"env.world");
		delete sfdpComp;
		delete sfvComp;
	}catch(std::string &err)
	{
		std::cout<<err<<std::endl;
	}


	return 0;
}
