/*
 * MaterialFileMaker.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: userws1
 */

#include "MaterialFileMaker.h"

MaterialFileMaker::MaterialFileMaker(std::string filename) {
	myfile.open(filename.c_str());

}

void MaterialFileMaker::addMaterial(std::string modelName,
		std::string materialName, std::string texture) {

	myfile<< "material "<< modelName << "/" <<materialName <<"\n";
	myfile<< "{\n";
	myfile<< "	receive_shadows on\n";
	myfile<< "	technique\n";
	myfile<< "	{\n";
	myfile<< "		pass\n";
	myfile<< "		{\n";
	myfile<< "			texture_unit\n";
	myfile<< "			{\n";
	myfile<< "				texture "<< texture <<"\n";
	myfile<< "				filtering anistropic\n";
	myfile<< "				max_anisotropy 16\n";
	myfile<< "				scale 1 1\n";
	myfile<< "			}\n";
	myfile<< "		}\n";
	myfile<< "	}\n";
	myfile<< "}\n";
	myfile<< "\n";

}

void MaterialFileMaker::outputFile()
{
	myfile.close();
}

MaterialFileMaker::~MaterialFileMaker() {
	// TODO Auto-generated destructor stub
}

