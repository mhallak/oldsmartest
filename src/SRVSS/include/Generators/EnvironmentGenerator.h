/*
 * EnvironmentGenerator.h
 *
 *  Created on: Feb 25, 2014
 *      Author: userws1
 */

#ifndef ENVIRONMENTGENERATOR_H_
#define ENVIRONMENTGENERATOR_H_
#include <string>
#include <utils/TinyXmlDef.h>

class SFVComponent;
class TerrainAnalyzer;
class SFVObject;
class SFVTerrain;
class TiXmlElement;
class EnvironmentGenerator {
	TerrainAnalyzer* m_terrainAnalyzer;
	int m_objectCount;

	void spawnObject(SFVObject* sfvObj,TiXmlElement * element);
	void spawnTerrain(SFVTerrain* sfvTerrain,TiXmlElement * element);
public:

	EnvironmentGenerator();
	virtual ~EnvironmentGenerator();

	void genEnvFromSFV(SFVComponent * sfvComp,std::string filename);
};

#endif /* ENVIRONMENTGENERATOR_H_ */
