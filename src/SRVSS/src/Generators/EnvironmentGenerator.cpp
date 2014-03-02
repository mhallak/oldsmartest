/*
 * EnvironmentGenerator.cpp
 *
 *  Created on: Feb 25, 2014
 *      Author: userws1
 */

#include "Generators/EnvironmentGenerator.h"
#include "Generators/TerrainAnalyzer.h"
#include "SFV/SFVComponent.h"
#include "SFV/SFVObject.h"
#include "SFV/SFVTerrain.h"
#include "utils/TinyXmlDef.h"
#include "Resource/ResourceHandler.h"
#include <sstream>
#include <stdlib.h>
EnvironmentGenerator::EnvironmentGenerator() {
	m_terrainAnalyzer=new TerrainAnalyzer();
	 m_objectCount=0;
}

EnvironmentGenerator::~EnvironmentGenerator() {
	// TODO Auto-generated destructor stub
}

void EnvironmentGenerator::spawnObject(SFVObject* sfvObj,TiXmlElement * element)
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

void EnvironmentGenerator::spawnTerrain(SFVTerrain* sfvTerrain,TiXmlElement * element)
{
	TiXmlElement * include = new TiXmlElement( "include" );
	element->LinkEndChild(include);
	TiXmlElement * url = new TiXmlElement( "uri" );
	TiXmlText * url_text = new TiXmlText(std::string("model://")+ResourceHandler::getInstance().getTerrainById(sfvTerrain->getTerrainId()));
	url->LinkEndChild(url_text);
	include->LinkEndChild(url);
}

void EnvironmentGenerator::genEnvFromSFV(SFVComponent* sfvComp,std::string filename)
{
	//load terrain
	std::string terrain=ResourceHandler::getInstance().getTerrainById(sfvComp->getTerrain()->getTerrainId());
	std::string path = ResourceHandler::getInstance().getResourcePath();

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

	spawnTerrain( sfvComp->getTerrain(),world);

	std::vector<SFVObject*> *objects=sfvComp->getObjects();
	for(int i=0;i<objects->size();i++)
	{
		spawnObject(objects->at(i),world);
	}

	doc.SaveFile(filename.c_str());
}
