/*
 * ResourceHandler.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#include "Resource/ResourceHandler.h"
#include "utils/TinyXmlDef.h"

void parseResource(TiXmlNode* node,std::map<std::string,std::map<int,std::string> *>* resourceMap)
{
	TiXmlNode* pChild;
	for ( pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		TiXmlAttribute* id=pChild->ToElement()->FirstAttribute();
		TiXmlText * text=pChild->FirstChild()->ToText();
		resourceMap->at(pChild->ValueStr())->insert(std::pair<int,std::string>(atoi(id->Value()),text->ValueStr()));
	}
}


ResourceHandler::ResourceHandler() {

	m_resourceMap=new std::map<std::string,std::map<int,std::string> *>;
	m_resourceMap->insert(std::pair<std::string,std::map<int,std::string> *>(std::string("terrain"),new std::map<int,std::string>));
	m_resourceMap->insert(std::pair<std::string,std::map<int,std::string> *>(std::string("object"),new std::map<int,std::string>));
	m_resourceMap->insert(std::pair<std::string,std::map<int,std::string> *>(std::string("light"),new std::map<int,std::string>));

	TiXmlDocument doc("/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/resource/resource.xml");

		if (!doc.LoadFile())
		{
			std::string error("Failed to load file \"");
			error+="resources/resource.xml";
			error+="\"\n";
			throw error;
		}
		TiXmlNode* pChild;
		TiXmlAttribute* pAttrib;;
		//search for an sdfp element to parse
		for ( pChild = doc.FirstChild(); pChild != 0; pChild = pChild->NextSibling())
		{
			if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("resource")==0){
				for ( pAttrib = pChild->ToElement()->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
				{
					if(pAttrib->NameTStr().compare("dirPath")==0)
					{
						m_modelsPath=pAttrib->ValueStr();
					}
					else if(pAttrib->NameTStr().compare("platform")==0)
					{
						m_platformModel=pAttrib->ValueStr();
						m_platformPath=m_modelsPath+"/"+pAttrib->ValueStr()+"/model.sdf";
					}
				}
				parseResource(pChild,m_resourceMap);
				break;
			}
		}
}

ResourceHandler::~ResourceHandler() {

	for (std::map<std::string,std::map<int,std::string> *>::iterator it=m_resourceMap->begin();
																			it!=m_resourceMap->end();
																								++it)
	{
		delete it->second;
	}
	delete m_resourceMap;
}


std::string ResourceHandler::getResource(std::string name,int id)
{
	return m_resourceMap->at(name)->at(id);
}

std::string ResourceHandler::getTerrainById(int id) {
	return getResource(std::string("terrain"),id);
}

std::string ResourceHandler::getObjectById(int id) {
	return getResource(std::string("object"),id);
}

std::string ResourceHandler::getLightById(int id) {
	return getResource(std::string("light"),id);
}

const std::string& ResourceHandler::getModelsPath() const {
	return m_modelsPath;
}

const std::string& ResourceHandler::getPlatformPath() const {
	return m_platformPath;
}

const std::string& ResourceHandler::getPlatformModel() const {
	return m_platformModel;
}
