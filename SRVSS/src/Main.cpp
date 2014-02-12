#include "SFDP/SDFPComponent.h"
#include "SFDP/SDFPParser.h"
#include <string>
#include <stdio.h>
#include <iostream>

int main(int argc, char** argv)
{
	SDFPParser pars;
	try{
		SDFPComponent *comp=pars.genSDFPFromFile("template.SFDP");
		comp->rollDice();
	}catch(std::string &err)
	{
		std::cout<<err<<std::endl;
	}

	return 0;
}
