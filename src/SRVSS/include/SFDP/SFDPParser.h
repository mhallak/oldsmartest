/*
 * SFDPParser.h
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#ifndef SFDPPARSER_H_
#define SFDPPARSER_H_

#include <string>
#include <vector>

#include "SFDPComponent.h"
#include "SFDPobj.h"

#include "ScenarioFeatureGroup.h"

/**
 * An object generator class.
 * This class parses the SFDP file and generate an SFDP component according to it's data
 */
class SFDPParser {


	void parseSFDPFile(SFDPComponent * sdfpComp);


public:

	/**
	* A constructor.
	*/
	SFDPParser();

	 /**
	* A destructor.
	*/
	virtual ~SFDPParser();

	 /**
	* a base method that loads the given xml file and attempts to parse the sfdp description in the first xml level
	* @param filename a string argument, the path to the xml file
	* @throw string exception in case of bad input
	* @see SFDPComponent
	* @return a SFDPComponent that fits the file description
	*/
	SFDPComponent * genSFDPFromFile(std::string filename) throw (std::string);


	std::vector <ScenarioFeatureGroup *> * genFeatureGroupVectorFromFile(std::string filename)  throw (std::string);

};

#endif /* SFDPPARSER_H_ */
