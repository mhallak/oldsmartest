/*
 * SDFPParser.h
 *
 *  Created on: Feb 3, 2014
 *      Author: userws1
 */

#ifndef SDFPPARSER_H_
#define SDFPPARSER_H_
#include <string>

#include "SDFPComponent.h"

/**
 * An object generator class.
 * This class parses the SFDP file and generate an SFDP component according to it's data
 */
class SDFPParser {


	void parseSDFPFile(SDFPComponent * sdfpComp);


public:

	/**
	* A constructor.
	*/
	SDFPParser();

	 /**
	* A destructor.
	*/
	virtual ~SDFPParser();

	 /**
	* a base method that loads the given xml file and attempts to parse the sfdp description in the first xml level
	* @param filename a string argument, the path to the xml file
	* @throw string exception in case of bad input
	* @see SDFPComponent
	* @return a SDFPComponent that fits the file description
	*/
	SDFPComponent * genSDFPFromFile(std::string filename) throw (std::string);

};

#endif /* SDFPPARSER_H_ */
