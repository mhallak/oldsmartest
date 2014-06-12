/*
 * EnvironmentGenerator.cpp
 *
 *  Created on: Feb 25, 2014
 *      Author: userws1
 */

#include "Generators/Gazebo/GazeboEnvironmentGenerator.h"
#include "Generators/Gazebo/TerrainAnalyzer.h"
#include "SFV/SFVComponent.h"
#include "SFV/SFVObject.h"
#include "SFV/SFVTerrain.h"
#include "utils/TinyXmlDef.h"
#include "Resource/ResourceHandler.h"
#include <sstream>
#include <stdlib.h>
#include <sdf/sdf.hh>

GazeboEnvironmentGenerator::GazeboEnvironmentGenerator() {
	m_terrainAnalyzer=new TerrainAnalyzer();
	 m_objectCount=0;
}

GazeboEnvironmentGenerator::~GazeboEnvironmentGenerator() {
	// TODO Auto-generated destructor stub
}

void GazeboEnvironmentGenerator::spawnObject(SFVObject* sfvObj,TiXmlElement * element)
{
	TiXmlElement * include = new TiXmlElement( "include" );
	element->LinkEndChild(include);
	TiXmlElement * url = new TiXmlElement( "uri" );
	TiXmlText * url_text = new TiXmlText(std::string("model://")+ResourceHandler::getInstance().getObjectById(sfvObj->getType()));
	url->LinkEndChild(url_text);
	include->LinkEndChild(url);
	TiXmlElement * pose = new TiXmlElement( "pose" );
	std::stringstream ss;
	float x,y,z;
	m_terrainAnalyzer->getXYZCoord(sfvObj->getX(),sfvObj->getY(),x,y,z);

	ss<<x <<" " << y <<" "<< z+sfvObj->getZ() << " ";
	ss<<sfvObj->getRoll() <<" " << sfvObj->getPitch() <<" "<< sfvObj->getYaw();
	TiXmlText * pose_text = new TiXmlText(ss.str());
	ss.str("");
	pose->LinkEndChild(pose_text);
	include->LinkEndChild(pose);
	TiXmlElement * scale = new TiXmlElement( "scale" );

	ss<<sfvObj->getScale() <<" " << sfvObj->getScale() <<" "<< sfvObj->getScale();
	TiXmlText * scale_text = new TiXmlText(ss.str());
	ss.str("");
	scale->LinkEndChild(scale_text);
	include->LinkEndChild(scale);
	TiXmlElement * name = new TiXmlElement( "name" );
	include->LinkEndChild(name);
	ss.str("");
	ss<< "object";
	ss<<m_objectCount;
	name->LinkEndChild(new TiXmlText(ss.str()));
	m_objectCount++;
}

void GazeboEnvironmentGenerator::spawnTerrain(SFVTerrain* sfvTerrain,TiXmlElement * element)
{
	TiXmlElement * include = new TiXmlElement( "include" );
	element->LinkEndChild(include);
	TiXmlElement * url = new TiXmlElement( "uri" );
	TiXmlText * url_text = new TiXmlText(std::string("model://")+ResourceHandler::getInstance().getTerrainById(sfvTerrain->getTerrainId()));
	url->LinkEndChild(url_text);
	include->LinkEndChild(url);
}

void GazeboEnvironmentGenerator::spawnPlatformPose(SFVPlatformPose* sfvPlatformPose,TiXmlElement * element)
{
	TiXmlElement * include = new TiXmlElement( "include" );
	element->LinkEndChild(include);
	TiXmlElement * url = new TiXmlElement( "uri" );
	TiXmlText * url_text = new TiXmlText(std::string("model://")+ResourceHandler::getInstance().getPlatformModel());
	url->LinkEndChild(url_text);
	include->LinkEndChild(url);
	TiXmlElement * pose = new TiXmlElement( "pose" );
	std::stringstream ss;
	float x,y,z, azi;
	m_terrainAnalyzer->getXYZCoord(sfvPlatformPose->getLocationX(),sfvPlatformPose->getLocationY(),x,y,z);
    azi = sfvPlatformPose->getLocationAzimut();

	z=z+0.5;  // compensation for the wheels height
	ss<<x <<" " << y <<" "<< z << " ";
	ss<<0 <<" " << 0 <<" "<< azi;
	TiXmlText * pose_text = new TiXmlText(ss.str());
	ss.str("");
	pose->LinkEndChild(pose_text);
	include->LinkEndChild(pose);

	TiXmlElement * name = new TiXmlElement( "name" );
	name->LinkEndChild(new TiXmlText("SRVSS_BobCat"));
	include->LinkEndChild(name);
}

void GazeboEnvironmentGenerator::genEnvFromSFV(SFVComponent* sfvComp,std::string filename)
{
	//load terrain
	std::string terrain=ResourceHandler::getInstance().getTerrainById(sfvComp->getTerrains()->at(0)->getTerrainId());
	std::string path = ResourceHandler::getInstance().getModelsPath();

	m_terrainAnalyzer->loadFile(path+"/"+terrain);

	TiXmlDocument doc(filename);
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild(decl);
	TiXmlElement * element = new TiXmlElement( "sdf" );
	element->SetAttribute("version","1.4");
	doc.LinkEndChild(element);
	TiXmlElement * world = new TiXmlElement( "world" );
	world->SetAttribute("name","default");
	element->LinkEndChild(world);


	// addition of sunlight
	TiXmlElement * include = new TiXmlElement( "include" );
	world->LinkEndChild(include);
	TiXmlElement * uri = new TiXmlElement( "uri" );
	TiXmlText * sun_url = new TiXmlText("model://sun");
	uri->LinkEndChild(sun_url);
	include->LinkEndChild(uri);

	// addition of sky to the environment
	TiXmlElement * scene = new TiXmlElement( "scene" );
	world->LinkEndChild(scene);
	TiXmlElement * sky = new TiXmlElement( "sky" );
	scene->LinkEndChild(sky);

	TiXmlElement * time = new TiXmlElement( "time" );
	sky->LinkEndChild(time);
	TiXmlText * time_value = new TiXmlText("10");
	time->LinkEndChild(time_value);

	// addition of clouds
	TiXmlElement * clouds = new TiXmlElement( "clouds" );
	sky->LinkEndChild(clouds);

	TiXmlElement * speed = new TiXmlElement( "speed" );
	clouds->LinkEndChild(speed);
	TiXmlText * speed_value = new TiXmlText("5");
	speed->LinkEndChild(speed_value);

	TiXmlElement * direction = new TiXmlElement( "direction" );
	clouds->LinkEndChild(direction);
	TiXmlText * direction_value = new TiXmlText("1.14");
	direction->LinkEndChild(direction_value);
	TiXmlElement * humidity = new TiXmlElement( "humidity" );
	clouds->LinkEndChild(humidity);
	TiXmlText * humidity_value = new TiXmlText("0.3");
	humidity->LinkEndChild(humidity_value);


	spawnTerrain( sfvComp->getTerrains()->at(0),world);

	spawnPlatformPose(sfvComp->m_platformPoses->at(0),world);

	std::vector<SFVObjects*> *objects=sfvComp->getObjects();
	for(auto it1: *sfvComp->getObjects())
	{
		for(auto it2: *it1->m_objects)
		{
			spawnObject(it2,world);
		}
	}

	doc.SaveFile(filename.c_str());
}

void GazeboEnvironmentGenerator::generate(SFVComponent * sfvcomp)
{
}

