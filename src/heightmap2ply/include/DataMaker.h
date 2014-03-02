/*
 * DataMaker.h
 *
 *  Created on: Feb 27, 2014
 *      Author: userws1
 */

#ifndef DATAMAKER_H_
#define DATAMAKER_H_
#include <tinyxml.h>
#include <string>

class DataMaker {
	TiXmlDocument doc;
	TiXmlElement* elem;
public:
	DataMaker();
	void addData(std::string data,std::string value);
	void output(std::string filename);
	virtual ~DataMaker();
};

#endif /* DATAMAKER_H_ */
