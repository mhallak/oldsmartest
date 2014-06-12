/*
 * GazeboMissionGenerator.h
 *
 *  Created on: Apr 10, 2014
 *      Author: userws1
 */

#ifndef GAZEBOMISSIONGENERATOR_H_
#define GAZEBOMISSIONGENERATOR_H_
#include <Generators/GeneratorInterface.h>
#include <Generators/Gazebo/TerrainAnalyzer.h>
class GazeboMissionGenerator : public GeneratorInterface{
	TerrainAnalyzer * m_terrainAnalyzer;
	float m_last_x_pose;
	float m_last_y_pose;
	float m_last_z_pose;
	float m_last_yaw_pose;
	std::string m_last_platform_name;
public:
	GazeboMissionGenerator();
	virtual ~GazeboMissionGenerator();
	void generateMission(SFVComponent * sfvcomp,std::string filename);
	void generate(SFVComponent * sfvcomp);
	float getLastXPose() const;
	void setLastXPose(float lastXPose);
	float getLastYPose() const;
	void setLastYPose(float lastYPose);
	float getLastZPose() const;
	void setLastZPose(float lastZPose);
	float getLastYawPose() const;
	void setLastYawPose(float lastYawPose);
	const std::string& getLastPlatformName() const;
	void setLastPlatformName(const std::string& lastPlatformName);
};

#endif /* GAZEBOMISSIONGENERATOR_H_ */
