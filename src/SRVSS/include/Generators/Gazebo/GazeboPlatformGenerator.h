/*
 * GazeboPlatformGenerator.h
 *
 *  Created on: Mar 27, 2014
 *      Author: userws1
 */

#ifndef GAZEBOPLATFORMGENERATOR_H_
#define GAZEBOPLATFORMGENERATOR_H_

#include <Generators/GeneratorInterface.h>

class GazeboPlatformGenerator : public GeneratorInterface{
public:
	GazeboPlatformGenerator();
	virtual ~GazeboPlatformGenerator();
	void generatePlatform(SFVComponent * sfvcomp,std::string filename);
	void generate(SFVComponent * sfvcomp);
};

#endif /* GAZEBOPLATFORMGENERATOR_H_ */
