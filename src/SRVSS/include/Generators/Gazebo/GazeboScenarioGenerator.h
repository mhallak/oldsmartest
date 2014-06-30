/*
 * GazeboScenarioGenerator.h
 *
 *  Created on: Jun 30, 2014
 *      Author: userws3
 */

#ifndef GAZEBOSCENARIOGENERATOR_H_
#define GAZEBOSCENARIOGENERATOR_H_

#include <Generators/GeneratorInterface.h>

class GazeboScenarioGenerator {

public:
	std::vector<GeneratorInterface *> * generators_vec;
	int GenerateScenario(SFVComponent* sfvComp, std::string scenario_folder_url, std::string resource_file_url);


	GazeboScenarioGenerator();
	inline virtual ~GazeboScenarioGenerator() {};

};



#endif /* GAZEBOSCENARIOGENERATOR_H_ */
