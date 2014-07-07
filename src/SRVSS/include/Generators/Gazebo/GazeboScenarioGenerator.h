/*
 * GazeboScenarioGenerator.h
 *
 *  Created on: Jun 30, 2014
 *      Author: userws3
 */

#ifndef GAZEBOSCENARIOGENERATOR_H_
#define GAZEBOSCENARIOGENERATOR_H_

#include <Generators/GeneratorInterface.h>

class GazeboScenarioGenerator
{

	private :
		SFVComponent* my_sfvComp;
		std::string my_scenario_folder_url;
		std::string my_resource_file_url;

		std::vector<GeneratorInterface *> * generators_vec;

	public:

		GazeboScenarioGenerator(SFVComponent* sfvComp, std::string scenario_folder_url, std::string resource_file_url);
		inline virtual ~GazeboScenarioGenerator() {};

		int GenerateScenario();
};



#endif /* GAZEBOSCENARIOGENERATOR_H_ */
