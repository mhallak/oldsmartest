/*
 * WorldFileMaker.h
 *
 *  Created on: Jan 30, 2014
 *      Author: userws1
 */

#ifndef MODELFILEMAKER_H_
#define MODELFILEMAKER_H_
#include "tinyxml.h"

class ModelFileMaker {
	TiXmlDocument doc;
	TiXmlElement * modelElement;
	std::string  modelname;

	void outputConfigFile();
public:

	ModelFileMaker(std::string modelName);
	virtual ~ModelFileMaker();
	void addMesh(std::string objectName,std::string stlName,float poseX,float poseY);
	void outputFile(std::string filename);
};

#endif
