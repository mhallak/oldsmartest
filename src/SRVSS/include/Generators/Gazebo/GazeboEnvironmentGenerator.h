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
#include <Generators/GeneratorInterface.h>
#include <Generators/Gazebo/TerrainAnalyzer.h>

class GazeboEnvironmentGenerator : public GeneratorInterface {
	TerrainAnalyzer* m_terrainAnalyzer;
	int m_objectCount;
	int m_ObstacleOnPathCounter;
	int m_WpMarkCounter;

	void spawnObjects(SFVComponent* sfvComp, TiXmlElement * element, std::string resources_file_path);

	void spawnObstacleOnPath(SFVComponent* sfvComp,TiXmlElement * element, std::string resources_file_path);


	void spawnTerrain(SFVTerrain* sfvTerrain,TiXmlElement * element, std::string resources_file_path);
	void spawnPlatformPose(SFVPlatformPose* sfvPlatformPose,TiXmlElement * element, std::string resources_file_path);
	void spawnPathWpMarks(SFVComponent* sfvComp,TiXmlElement * element);



public:

	GazeboEnvironmentGenerator();
	virtual ~GazeboEnvironmentGenerator();

	void genEnvFromSFV(SFVComponent * sfvComp,std::string filename, std::string resources_file_path);
	void generate(SFVComponent * sfvcomp, std::string scenario_folder_url, std::string resource_file_url);
};

#endif /* GAZEBOENVIRONMENTGENERATOR_H_ */
