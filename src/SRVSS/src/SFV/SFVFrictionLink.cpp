/*
 * SFVFrictionLink.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#include "SFV/SFVFrictionLink.h"

SFVFrictionLink::SFVFrictionLink() {
	// TODO Auto-generated constructor stub

}

double SFVFrictionLink::getFrictionDeviation() const {
	return m_frictionDeviation;
}

void SFVFrictionLink::setFrictionDeviation(double frictionDeviation) {
	m_frictionDeviation = frictionDeviation;
}

int SFVFrictionLink::getId() const {
	return m_id;
}

const std::string& SFVFrictionLink::getLinkName() const {
	return m_link_name;
}

void SFVFrictionLink::setLinkName(const std::string& linkName) {
	m_link_name = linkName;
}

void SFVFrictionLink::setId(int id) {
	m_id = id;
}

void SFVFrictionLink::setRolledValue(RolledValue * value)
{
	switch(value->getType()._type)
	{
		case ScenarioFeatureType::friction_link_friction_deviation:
			setFrictionDeviation(value->getValue());
	}
}
SFVFrictionLink::~SFVFrictionLink() {
	// TODO Auto-generated destructor stub
}

TiXmlElement * SFVFrictionLink::toXMLElement()
{
	std::stringstream ss;
	TiXmlElement * friction_link= new TiXmlElement( "friction_link" );
	ss << getId();
	friction_link->SetAttribute("id",ss.str());
	friction_link->SetAttribute("name",getLinkName());
	ss.str("");

	TiXmlElement * friction_linkFrictionDeviation= new TiXmlElement( "frictionDeviation" );
	ss << getFrictionDeviation();
	TiXmlText * friction_linkFrictionDeviationVal= new TiXmlText( ss.str() );
	ss.str("");
	friction_linkFrictionDeviation->LinkEndChild(friction_linkFrictionDeviationVal);
	friction_link->LinkEndChild(friction_linkFrictionDeviation);

	return friction_link;
}

void SFVFrictionLink::fromXMLElement(TiXmlElement * xmlElement)
{
	TiXmlNode* pChild;
	TiXmlAttribute* pAttrib;

	for ( pAttrib = xmlElement->ToElement()->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
	{
		if(pAttrib->NameTStr().compare("id")==0)
		{
			setId(atoi(pAttrib->ValueStr().c_str()));
		}
		if(pAttrib->NameTStr().compare("name")==0)
		{
			setLinkName(pAttrib->ValueStr());
		}

	}

	for ( pChild = xmlElement->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("frictionDeviation")==0){
			setFrictionDeviation(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
	}
}
