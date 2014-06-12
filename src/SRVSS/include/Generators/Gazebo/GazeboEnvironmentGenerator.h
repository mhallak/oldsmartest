/*
 * EnvironmentGenerator.h
 *
 *  Created on: Feb 25, 2014
 *      Author: userws1
 */

#ifndef GAZEBOENVIRONMENTGENERATOR_H_
#define GAZEBOENVIRONMENTGENERATOR_H_

#include <string>
#include <utils/TinyXmlDef.h>
#include <Generators/EnvironmentGenerator.h>
#include <Generators/Gazebo/TerrainAnalyzer.h>

class GazeboEnvironmentGenerator : public EnvironmentGenerator {
	TerrainAnalyzer* m_terrainAnalyzer;
	int m_objectCount;
	int m_ObstacleOnPathCounter;
	int m_WpMarkCounter;

	void spawnObject(SFVObject* sfvObj,TiXmlElement * element);

	void spawnObstacleOnPath(SFVComponent* sfvComp,TiXmlElement * element);


	void spawnTerrain(SFVTerrain* sfvTerrain,TiXmlElement * element);
	void spawnPlatformPose(SFVPlatformPose* sfvPlatformPose,TiXmlElement * element);
	void spawnPathWpMarks(SFVComponent* sfvComp,TiXmlElement * element);



public:

	GazeboEnvironmentGenerator();
	virtual ~GazeboEnvironmentGenerator();

	void genEnvFromSFV(SFVComponent * sfvComp,std::string filename);
	void generate(SFVComponent * sfvcomp);
};

#endif /* GAZEBOENVIRONMENTGENERATOR_H_ */
