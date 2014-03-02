/*
 * SFVParser.h
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#ifndef SFVPARSER_H_
#define SFVPARSER_H_
#include <string>
class SFVComponent;

class SFVParser {
public:
	SFVParser();
	virtual ~SFVParser();

	 /**
	* a base method that loads the given xml file and attempts to parse the sfv description in the first xml level
	* @param filename a string argument, the path to the xml file
	* @throw string exception in case of bad input
	* @see SFVComponent
	* @return a SFVComponent that fits the file description
	*/
	SFVComponent * genSFVFromFile(std::string filename) throw (std::string);

	 /**
	* a base method that writes an xml file that fits the SFVComponent description
	* @param filename a string argument, the path to the xml file
	* @param sfvComp the SFVComponent to parse
	* @see SFVComponent
	* @return a SFVComponent that fits the file description
	*/
	void genFileFromSFV(std::string filename,SFVComponent * sfvComp);
};

#endif /* SFVPARSER_H_ */
