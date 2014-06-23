/*
 * GazeboPlatformGenerator.h
 *
 *  Created on: Mar 27, 2014
 *      Author: userws1
 */

#ifndef GAZEBOPLATFORMGENERATOR_H_
#define GAZEBOPLATFORMGENERATOR_H_

#include <Generators/PlatformGenerator.h>

class GazeboPlatformGenerator : public PlatformGenerator{
public:
	GazeboPlatformGenerator();
	virtual ~GazeboPlatformGenerator();
	void generatePlatform(SFVComponent * sfvcomp,std::string filename, std::string resources_file_path);
	void generate(SFVComponent * sfvcomp);
};

#endif /* GAZEBOPLATFORMGENERATOR_H_ */
