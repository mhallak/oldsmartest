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
#include "SFVLight.h"
#include "SFVTerrain.h"
#include "SFVMassLink.h"
#include "SFVFrictionLink.h"
#include "SFVSensorLink.h"
#include "SFDP/ScenarioFeatureGroup.h"
#include "utils/ParsableInterface.h"

class SFVComponent: public ParsableInterface{
public:
	std::vector<SFVMassLink *>* m_massLinks;
	std::vector<SFVFrictionLink *>* m_frictionLinks;
	std::vector<SFVSensorLink *>* m_sensorLinks;
	std::vector<SFVObject *>* m_objects;
	std::vector<SFVLight *>* m_lights;
	std::vector<SFVTerrain*> * m_terrains;


	SFVComponent();
	virtual ~SFVComponent();

	void addRolledValues(ScenarioFeatureGroup* group,std::vector<RolledValue*>* values);

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
	void genSFVFromFile(std::string filename) throw (std::string);


	TiXmlElement *toXMLElement();
	void fromXMLElement(TiXmlElement * node);
	std::vector<SFVMassLink *>* getMassLinks();
	std::vector<SFVFrictionLink *>* getFrictionLinks();
	std::vector<SFVSensorLink *>* getSensorLinks();
	std::vector<SFVLight*>* getLights();
	std::vector<SFVObject*>* getObjects();
	std::vector<SFVTerrain*> * getTerrains();

	void addTerrain(SFVTerrain* terrain);
};

#endif /* SFVCOMPONENT_H_ */
