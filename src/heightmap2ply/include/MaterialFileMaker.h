/*
 * MaterialFileMaker.h
 *
 *  Created on: Feb 27, 2014
 *      Author: userws1
 */

#ifndef MATERIALFILEMAKER_H_
#define MATERIALFILEMAKER_H_
#include <fstream>

class MaterialFileMaker {
	 std::ofstream myfile;
public:
	MaterialFileMaker(std::string filename);

	void addMaterial(std::string modelName,std::string materialName,std::string texture);
	void outputFile();
	virtual ~MaterialFileMaker();
};

#endif /* MATERIALFILEMAKER_H_ */
