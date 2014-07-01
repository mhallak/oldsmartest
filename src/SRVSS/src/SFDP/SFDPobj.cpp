/*
 * SFDPobj.cpp
 *
 *  Created on: Jul 1, 2014
 *      Author: userws3
 */

#include "SFDP/SFDPobj.h"
#include "SFDP/SFDPParser.h"

#include <string>
#include <vector>

#include <iostream>

SFDPobj::SFDPobj(std::string SFDP_file_url, std::string Resources_file_url, std::string WS_url, int division_level)
{
	my_SFDP_file_url = SFDP_file_url;
	my_Resources_file_url = Resources_file_url;
	my_WS_url = WS_url;
	my_division_level = division_level;
	have_been_run = false;

	my_featureGroups = new std::vector<ScenarioFeatureGroup*>;

	SFDPParser * SFDPpars = new SFDPParser;
	my_featureGroups = SFDPpars->genFeatureGroupVectorFromFile(my_SFDP_file_url);

	std::cout << " I am !! " << std::endl;

	for(ScenarioFeatureGroup * it : * my_featureGroups)
	{
	std::cout << it->get_featureGroupType() << std::endl;
	}
}









