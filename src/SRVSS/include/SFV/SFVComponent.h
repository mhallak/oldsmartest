/*
 * SFVComponent.h
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#ifndef SFVCOMPONENT_H_
#define SFVCOMPONENT_H_
#include <vector>

class SFVObject;
class SFVLight;
class SFVTerrain;
class ScenarioFeatureType;
class SFVComponent {
public:

	std::vector<SFVObject *>* m_objects;
	std::vector<SFVLight *>* m_lights;
	SFVTerrain * m_terrain;


	SFVComponent();
	virtual ~SFVComponent();

	void addRolledValue(ScenarioFeatureType type,double rolledValue,int rolledID);

	std::vector<SFVLight*>* getLights();
	std::vector<SFVObject*>* getObjects();
	SFVTerrain* getTerrain();

	void setTerrain(SFVTerrain* terrain);
};

#endif /* SFVCOMPONENT_H_ */
