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
	void generatePlatform(SFVComponent * sfvcomp,std::string filename, std::string resources_file_path);
	void generate(SFVComponent * sfvcomp, std::string scenario_folder_url, std::string resource_file_url);
};

#endif /* GAZEBOPLATFORMGENERATOR_H_ */
