/*
 * SFVComponent.h
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#ifndef SFVCOMPONENT_H_
#define SFVCOMPONENT_H_
#include <vector>

#include "SFVObject.h"
#include "SFVObstacleOnPath.h"
#include "SFVLight.h"
#include "SFVTerrain.h"
#include "SFVMassLink.h"
#include "SFVFrictionLink.h"
#include "SFVSensorLink.h"
#include "SFVPlatformPose.h"
#include "SFVWaypoint.h"
#include "SFVPath.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "utils/ParsableInterface.h"
#include "SFV/SFVGeneric.h"
#include "SFV/DPGroup.h"
#include "Rules/Rule.h"
#include <map>




typedef SFVGeneric<SFVLight,ScenarioFeatureType::number_of_light_sources> SFVLights;
typedef SFVGeneric<SFVObject,ScenarioFeatureType::number_of_objects> SFVObjects;
typedef SFVGeneric<SFVWaypoint,ScenarioFeatureType::number_of_way_points> SFVWaypoints;
typedef SFVGeneric<SFVObstacleOnPath,ScenarioFeatureType::number_of_obstacles_on_path> SFVObstaclesOnPath;



class SFVComponent: public ParsableInterface{

	template<class T> void fromXMLElementAUX(std::string text,TiXmlElement * node,std::vector<T*> * vec);
	template<class T> void initAUX(ScenarioFeatureGroupType type,std::vector<T*> * vec);
	template<class T> void rollAUX(std::vector<T*> * vec,bool & state);

public:

	std::map<ScenarioFeatureGroupType,std::vector<DPGroup*>*> * m_DPObjectMap;
	std::vector<SFVObjects *> *m_objects;
	std::vector<SFVObstaclesOnPath *> *m_obstaclesOnPath;
	std::vector<SFVLights *> * m_lights;
	std::vector<SFVMassLink *>* m_massLinks;
	std::vector<SFVFrictionLink *>* m_frictionLinks;
	std::vector<SFVSensorLink *>* m_sensorLinks;
	std::vector<SFVTerrain*> * m_terrains;
	std::vector<SFVPlatformPose*> * m_platformPoses;
	std::vector<SFVPath *> * m_paths;
	std::vector<Rule*> * m_rules;

	std::string m_resource_file_path;

	bool calc();
	bool checkRules();
	void init();
	SFVComponent(std::string resource_file_path);
	virtual ~SFVComponent();

	void addDPObjects(ScenarioFeatureGroupType groupType,DPGroup* values);


	 /**
	* a base method that writes an xml file that fits the SFVComponent description
	* @param filename a string argument, the path to the xml file
	* @see SFVComponent
	* @return a SFVComponent that fits the file description
	*/
	void genFileFromSFV(std::string filename);


	 /**
	* a base method that loads the given xml file and attempts to parse the sfv description in the first xml level
	* @param filename a string argument, the path to the xml file
	* @throw string exception in case of bad input
	* @see SFVComponent
	*/
	int genSFVFromFile(std::string filename) throw (std::string);


	TiXmlElement *toXMLElement();
	void fromXMLElement(TiXmlElement * node);

	std::vector<SFVMassLink *>* getMassLinks();
	std::vector<SFVFrictionLink *>* getFrictionLinks();
	std::vector<SFVSensorLink *>* getSensorLinks();
	std::vector<SFVLights*>* getLights();
	std::vector<SFVObjects*>* getObjects();
	std::vector<SFVObstaclesOnPath*>* getObstaclesOnPath();
	std::vector<SFVTerrain*> * getTerrains();
	std::vector<SFVPlatformPose*> * getPlatformPoses();
	std::vector<SFVPath*> * getPaths();

	void addTerrain(SFVTerrain* terrain);
};

#endif /* SFVCOMPONENT_H_ */
