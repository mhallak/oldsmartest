/*
 * SFVBase.cpp
 *
 *  Created on: Jun 8, 2014
 *      Author: userws1
 */
#include "SFV/SFVComponent.h"
#include "SFV/SFVBase.h"
#include "utils/TinyXmlDef.h"
#include <boost/foreach.hpp>

SFVBase::SFVBase(DPGroup * dpGroup):m_dpGroup(dpGroup)
{
	m_name="";
	m_objects=new std::map<ScenarioFeatureType,DPObject*>;
	setStructure();
}

void SFVBase::init(DPGroup * dpGroup)
{
	m_name=dpGroup->m_name;
	for(auto it:*m_objects)
	{
		if( dpGroup->m_objects && dpGroup->m_objects->find(it.first)!=dpGroup->m_objects->end())
			(*m_objects)[it.first]=dpGroup->m_objects->at(it.first)->clone();
	}
}
bool SFVBase::calc(SFVComponent * sfvComp)
{
	bool ans=false;
	std::pair<ScenarioFeatureType,DPObject*> it;
	for(int i=0;i<3 && !ans;i++){
		BOOST_FOREACH(it,*m_objects)
		{
			it.second->calc();
		}
		ans=sfvComp->checkRules();
	}
	return ans;
}


SFVBase::~SFVBase() {
	// TODO Auto-generated destructor stub
}

void SFVBase::setStructure()
{
	m_Id=0;
	m_objectType="BaseObject";
}


TiXmlElement *SFVBase::toXMLElement()
{
	std::stringstream ss;
	TiXmlElement * object= new TiXmlElement( m_objectType );
	ss << m_Id;
	object->SetAttribute("id",ss.str());
	if(m_name.length()>0)
		object->SetAttribute("name",m_name);
	ss.str("");
	for(std::pair<ScenarioFeatureType,DPObject*> temp: *m_objects)
	{
		TiXmlElement * objectType= new TiXmlElement( temp.first.str() );
		ss << temp.second->getResult();
		TiXmlText * objectTypeVal= new TiXmlText( ss.str() );
		ss.str("");
		objectType->LinkEndChild(objectTypeVal);
		object->LinkEndChild(objectType);
	}
	return object;
}

void SFVBase::fromXMLElement(TiXmlElement * xmlElement)
{
	TiXmlNode* pChild;
	TiXmlAttribute* pAttrib;

	// FIX THIS : for now the object will generate its own DP objects
	std::pair<ScenarioFeatureType,DPObject*> it;
	BOOST_FOREACH(it,*m_objects)
	{
		(*m_objects)[it.first]=new DPObject(0);
	}
	/////////////////////////////////////////////////////////////
	for ( pAttrib = xmlElement->ToElement()->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
	{
		if(pAttrib->NameTStr().compare("id")==0)
		{
			m_Id=(atoi(pAttrib->ValueStr().c_str()));
		}
		if(pAttrib->NameTStr().compare("name")==0)
		{
			m_name=pAttrib->ValueStr();
		}
	}

	for ( pChild = xmlElement->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT){
			(*m_objects)[ScenarioFeatureType::parseString(pChild->Value())]->setResult(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
	}
}
