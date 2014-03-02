/*
 * SFVParser.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#include "SFV/SFVParser.h"
#include "utils/TinyXmlDef.h"
#include "SFV/SFVComponent.h"
#include "SFV/SFVObject.h"
#include "SFV/SFVLight.h"
#include "SFV/SFVTerrain.h"
#include <stdio.h>
#include <sstream>

SFVParser::SFVParser() {
	// TODO Auto-generated constructor stub

}

SFVParser::~SFVParser() {
	// TODO Auto-generated destructor stub
}



void parseObject(SFVObject *object,TiXmlNode* xmlNode) throw (std::string)
{
	TiXmlNode* pChild;
	TiXmlAttribute* pAttrib;

	for ( pAttrib = xmlNode->ToElement()->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
	{
		if(pAttrib->NameTStr().compare("id")==0)
		{
			object->setId(atoi(pAttrib->ValueStr().c_str()));
		}
	}

	for ( pChild = xmlNode->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("X")==0){
			object->setX(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("Y")==0){
			object->setY(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("Z")==0){
			object->setZ(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("roll")==0){
			object->setRoll(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("pitch")==0){
			object->setPitch(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("yaw")==0){
			object->setYaw(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("scale")==0){
			object->setScale(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("type")==0){
			object->setType(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
	}
}

void parseLight(SFVLight *light,TiXmlNode* xmlNode) throw (std::string)
{
	TiXmlNode* pChild;
	TiXmlAttribute* pAttrib;

	for ( pAttrib = xmlNode->ToElement()->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
	{
		if(pAttrib->NameTStr().compare("id")==0)
		{
			light->setId(atoi(pAttrib->ValueStr().c_str()));
		}
	}

	for ( pChild = xmlNode->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("X")==0){
			light->setX(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("Y")==0){
			light->setY(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("Z")==0){
			light->setZ(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("directionX")==0){
			light->setDirectionX(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("directionY")==0){
			light->setDirectionY(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("cone")==0){
			light->setCone(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("range")==0){
			light->setRange(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("type")==0){
			light->setType(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
	}
}

void parseTerrain(SFVTerrain *terrain,TiXmlNode* xmlNode) throw (std::string)
{
	TiXmlNode* pChild;
	TiXmlAttribute* pAttrib;

	for ( pAttrib = xmlNode->ToElement()->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
	{
		if(pAttrib->NameTStr().compare("id")==0)
		{
			terrain->setId(atoi(pAttrib->ValueStr().c_str()));
		}
	}

	for ( pChild = xmlNode->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("terrainId")==0){
			terrain->setTerrainId(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
	}
}


void parseSFV(SFVComponent *sfvComp,TiXmlNode* xmlNode) throw (std::string)
{
	TiXmlNode* pChild;
	TiXmlAttribute* pAttrib;
	//search for an sdfp element to parse
	for ( pChild = xmlNode->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("terrain")==0)
		{
			SFVTerrain *terrain = new SFVTerrain;
			parseTerrain(terrain,pChild);
			sfvComp->setTerrain(terrain);
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("object")==0)
		{
			SFVObject *object = new SFVObject;
			parseObject(object,pChild);
			sfvComp->getObjects()->push_back(object);
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("light")==0)
		{
			SFVLight *light = new SFVLight;
			parseLight(light,pChild);
			sfvComp->getLights()->push_back(light);
		}
	}
}


SFVComponent* SFVParser::genSFVFromFile(std::string filename)
		throw (std::string)
{

	SFVComponent * sfvComp=new SFVComponent;
	TiXmlDocument doc(filename);
	if (!doc.LoadFile())
	{
		std::string error("Failed to load file \"");
		error+=filename;
		error+="\"\n";
		throw error;
	}
	TiXmlNode* pChild;
	//search for an sdfp element to parse
	for ( pChild = doc.FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("sfv")==0){
			parseSFV(sfvComp,pChild);
			break;
		}
	}
	return sfvComp;
}

void SFVParser::genFileFromSFV(std::string filename, SFVComponent* sfvComp)
{
	std::stringstream ss;

	TiXmlDocument doc(filename);
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	TiXmlElement * element = new TiXmlElement( "sfv" );
	element->SetAttribute("version","1.0");
	doc.LinkEndChild(decl);
	doc.LinkEndChild(element);

	//write terrain
	TiXmlElement * terrain= new TiXmlElement( "terrain" );
	ss << sfvComp->getTerrain()->getId();
	terrain->SetAttribute("id",ss.str());
	ss.str("");
	element->LinkEndChild(terrain);
	TiXmlElement * terrainId= new TiXmlElement( "terrainId" );
	ss << sfvComp->getTerrain()->getTerrainId();
	TiXmlText * terrainIdVal= new TiXmlText( ss.str() );
	ss.str("");
	terrainId->LinkEndChild(terrainIdVal);
	terrain->LinkEndChild(terrainId);


	//write objects
	std::vector<SFVObject*> *objects=sfvComp->getObjects();
	for(int i=0;i<objects->size();i++)
	{
		TiXmlElement * object= new TiXmlElement( "object" );
		ss << objects->at(i)->getId();
		object->SetAttribute("id",ss.str());
		ss.str("");
		element->LinkEndChild(object);

		TiXmlElement * objectType= new TiXmlElement( "type" );
		ss << objects->at(i)->getType();
		TiXmlText * objectTypeVal= new TiXmlText( ss.str() );
		ss.str("");
		objectType->LinkEndChild(objectTypeVal);
		object->LinkEndChild(objectType);

		TiXmlElement * objectX= new TiXmlElement( "X" );
		ss << objects->at(i)->getX();
		TiXmlText * objectXVal= new TiXmlText( ss.str() );
		ss.str("");
		objectX->LinkEndChild(objectXVal);
		object->LinkEndChild(objectX);

		TiXmlElement * objectY= new TiXmlElement( "Y" );
		ss << objects->at(i)->getY();
		TiXmlText * objectYVal= new TiXmlText( ss.str() );
		ss.str("");
		objectY->LinkEndChild(objectYVal);
		object->LinkEndChild(objectY);

		TiXmlElement * objectZ= new TiXmlElement( "Z" );
		ss << objects->at(i)->getZ();
		TiXmlText * objectZVal= new TiXmlText( ss.str() );
		ss.str("");
		objectZ->LinkEndChild(objectZVal);
		object->LinkEndChild(objectZ);

		TiXmlElement * objectRoll= new TiXmlElement( "roll" );
		ss << objects->at(i)->getRoll();
		TiXmlText * objectRollVal= new TiXmlText( ss.str() );
		ss.str("");
		objectRoll->LinkEndChild(objectRollVal);
		object->LinkEndChild(objectRoll);

		TiXmlElement * objectPitch= new TiXmlElement( "pitch" );
		ss << objects->at(i)->getPitch();
		TiXmlText * objectPitchVal= new TiXmlText( ss.str() );
		ss.str("");
		objectPitch->LinkEndChild(objectPitchVal);
		object->LinkEndChild(objectPitch);

		TiXmlElement * objectYaw= new TiXmlElement( "yaw" );
		ss << objects->at(i)->getYaw();
		TiXmlText * objectYawVal= new TiXmlText( ss.str() );
		ss.str("");
		objectYaw->LinkEndChild(objectYawVal);
		object->LinkEndChild(objectYaw);

		TiXmlElement * objectScale= new TiXmlElement( "scale" );
		ss << objects->at(i)->getScale();
		TiXmlText * objectScaleVal= new TiXmlText( ss.str() );
		ss.str("");
		objectScale->LinkEndChild(objectScaleVal);
		object->LinkEndChild(objectScale);

	}

	std::vector<SFVLight*> *lights=sfvComp->getLights();
	for(int i=0;i<lights->size();i++)
	{
		TiXmlElement * light= new TiXmlElement( "light" );
		ss << lights->at(i)->getId();
		light->SetAttribute("id",ss.str());
		ss.str("");
		element->LinkEndChild(light);

		TiXmlElement * lightType= new TiXmlElement( "type" );
		ss << lights->at(i)->getType();
		TiXmlText * lightTypeVal= new TiXmlText( ss.str() );
		ss.str("");
		lightType->LinkEndChild(lightTypeVal);
		light->LinkEndChild(lightType);

		TiXmlElement * lightX= new TiXmlElement( "X" );
		ss << lights->at(i)->getX();
		TiXmlText * lightXVal= new TiXmlText( ss.str() );
		ss.str("");
		lightX->LinkEndChild(lightXVal);
		light->LinkEndChild(lightX);

		TiXmlElement * lightY= new TiXmlElement( "Y" );
		ss << lights->at(i)->getY();
		TiXmlText * lightYVal= new TiXmlText( ss.str() );
		ss.str("");
		lightY->LinkEndChild(lightYVal);
		light->LinkEndChild(lightY);

		TiXmlElement * lightZ= new TiXmlElement( "Z" );
		ss << lights->at(i)->getZ();
		TiXmlText * lightZVal= new TiXmlText( ss.str() );
		ss.str("");
		lightZ->LinkEndChild(lightZVal);
		light->LinkEndChild(lightZ);

		TiXmlElement * lightDirectionX= new TiXmlElement( "directionX" );
		ss << lights->at(i)->getDirectionX();
		TiXmlText * lightDirectionXVal= new TiXmlText( ss.str() );
		ss.str("");
		lightDirectionX->LinkEndChild(lightDirectionXVal);
		light->LinkEndChild(lightDirectionX);

		TiXmlElement * lightDirectionY= new TiXmlElement( "directionY" );
		ss << lights->at(i)->getDirectionY();
		TiXmlText * lightDirectionYVal= new TiXmlText( ss.str() );
		ss.str("");
		lightDirectionY->LinkEndChild(lightDirectionYVal);
		light->LinkEndChild(lightDirectionY);

		TiXmlElement * lightCone= new TiXmlElement( "cone" );
		ss << lights->at(i)->getCone();
		TiXmlText * lightConeVal= new TiXmlText( ss.str() );
		ss.str("");
		lightCone->LinkEndChild(lightConeVal);
		light->LinkEndChild(lightCone);

		TiXmlElement * lightRange= new TiXmlElement( "range" );
		ss << lights->at(i)->getRange();
		TiXmlText * lightRangeVal= new TiXmlText( ss.str() );
		ss.str("");
		lightRange->LinkEndChild(lightRangeVal);
		light->LinkEndChild(lightRange);

	}
	doc.SaveFile(filename.c_str());
}
