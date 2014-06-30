/*
 * GeneratorInterface.h
 *
 *  Created on: Mar 26, 2014
 *      Author: userws1
 */

#ifndef GENERATORINTERFACE_H_
#define GENERATORINTERFACE_H_
#include <SFV/SFVComponent.h>

class GeneratorInterface{
public:
	inline virtual ~GeneratorInterface(){}
	virtual void generate(SFVComponent* sfvComp, std::string scenario_folder_url, std::string resource_file_url)=0;
};

#endif /* GENERATORINTERFACE_H_ */
