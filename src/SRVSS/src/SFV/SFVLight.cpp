/*
 * SFVLight.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#include "SFV/SFVLight.h"

SFVLight::SFVLight():
m_Id(0),
m_Type(0),
m_X(0),
m_Y(0),
m_Z(0),
m_DirectionX(0),
m_DirectionY(0),
m_Cone(0),
m_Range(0)
{

}

double SFVLight::getCone() const {
	return m_Cone;
}

void SFVLight::setCone(double cone) {
	m_Cone = cone;
}

double SFVLight::getDirectionX() const {
	return m_DirectionX;
}

void SFVLight::setDirectionX(double directionX) {
	m_DirectionX = directionX;
}

double SFVLight::getDirectionY() const {
	return m_DirectionY;
}

void SFVLight::setDirectionY(double directionY) {
	m_DirectionY = directionY;
}

int SFVLight::getId() const {
	return m_Id;
}

void SFVLight::setId(int id) {
	m_Id = id;
}

double SFVLight::getRange() const {
	return m_Range;
}

void SFVLight::setRange(double range) {
	m_Range = range;
}

int SFVLight::getType() const {
	return m_Type;
}

void SFVLight::setType(int type) {
	m_Type = type;
}

double SFVLight::getX() const {
	return m_X;
}

void SFVLight::setX(double x) {
	m_X = x;
}

double SFVLight::getY() const {
	return m_Y;
}

void SFVLight::setY(double y) {
	m_Y = y;
}

double SFVLight::getZ() const {
	return m_Z;
}

void SFVLight::setZ(double z) {
	m_Z = z;
}

void SFVLight::setRolledValue(RolledValue * value)
{
	if(value->getType()._type==ScenarioFeatureType::light_source_i_type)
	{
		setType(value->getValue());
	}
	else if(value->getType()._type== ScenarioFeatureType::light_source_i_location_on_the_X_axis)
	{
		setX(value->getValue());
	}
	else if(value->getType()._type== ScenarioFeatureType::light_source_i_location_on_the_Y_axis)
	{
		setY(value->getValue());
	}
	else if(value->getType()._type== ScenarioFeatureType::light_source_i_location_on_the_Z_axis)
	{
		setZ(value->getValue());
	}
	else if(value->getType()._type== ScenarioFeatureType::light_source_i_range)
	{
		setRange(value->getValue());
	}
	else if(value->getType()._type== ScenarioFeatureType::light_source_i_direction_on_X_axis)
	{
		setDirectionX(value->getValue());
	}
	else if(value->getType()._type== ScenarioFeatureType::light_source_i_direction_on_Y_axis)
	{
		setDirectionY(value->getValue());
	}
	else if(value->getType()._type== ScenarioFeatureType::light_source_i_light_cone)
	{
		setCone(value->getValue());
	}

}


TiXmlElement * SFVLight::toXMLElement()
{
	std::stringstream ss;
	TiXmlElement * light= new TiXmlElement( "light" );
	ss << getId();
	light->SetAttribute("id",ss.str());
	ss.str("");

	TiXmlElement * lightType= new TiXmlElement( "type" );
	ss << getType();
	TiXmlText * lightTypeVal= new TiXmlText( ss.str() );
	ss.str("");
	lightType->LinkEndChild(lightTypeVal);
	light->LinkEndChild(lightType);

	TiXmlElement * lightX= new TiXmlElement( "X" );
	ss << getX();
	TiXmlText * lightXVal= new TiXmlText( ss.str() );
	ss.str("");
	lightX->LinkEndChild(lightXVal);
	light->LinkEndChild(lightX);

	TiXmlElement * lightY= new TiXmlElement( "Y" );
	ss << getY();
	TiXmlText * lightYVal= new TiXmlText( ss.str() );
	ss.str("");
	lightY->LinkEndChild(lightYVal);
	light->LinkEndChild(lightY);

	TiXmlElement * lightZ= new TiXmlElement( "Z" );
	ss << getZ();
	TiXmlText * lightZVal= new TiXmlText( ss.str() );
	ss.str("");
	lightZ->LinkEndChild(lightZVal);
	light->LinkEndChild(lightZ);

	TiXmlElement * lightDirectionX= new TiXmlElement( "directionX" );
	ss << getDirectionX();
	TiXmlText * lightDirectionXVal= new TiXmlText( ss.str() );
	ss.str("");
	lightDirectionX->LinkEndChild(lightDirectionXVal);
	light->LinkEndChild(lightDirectionX);

	TiXmlElement * lightDirectionY= new TiXmlElement( "directionY" );
	ss << getDirectionY();
	TiXmlText * lightDirectionYVal= new TiXmlText( ss.str() );
	ss.str("");
	lightDirectionY->LinkEndChild(lightDirectionYVal);
	light->LinkEndChild(lightDirectionY);

	TiXmlElement * lightCone= new TiXmlElement( "cone" );
	ss << getCone();
	TiXmlText * lightConeVal= new TiXmlText( ss.str() );
	ss.str("");
	lightCone->LinkEndChild(lightConeVal);
	light->LinkEndChild(lightCone);

	TiXmlElement * lightRange= new TiXmlElement( "range" );
	ss << getRange();
	TiXmlText * lightRangeVal= new TiXmlText( ss.str() );
	ss.str("");
	lightRange->LinkEndChild(lightRangeVal);
	light->LinkEndChild(lightRange);

	return light;
}

void SFVLight::fromXMLElement(TiXmlElement * xmlElement)
{
	TiXmlNode* pChild;
	TiXmlAttribute* pAttrib;

	for ( pAttrib = xmlElement->ToElement()->FirstAttribute(); pAttrib != 0; pAttrib = pAttrib->Next())
	{
		if(pAttrib->NameTStr().compare("id")==0)
		{
			setId(atoi(pAttrib->ValueStr().c_str()));
		}
	}

	for ( pChild = xmlElement->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("X")==0){
			setX(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("Y")==0){
			setY(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("Z")==0){
			setZ(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("directionX")==0){
			setDirectionX(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("directionY")==0){
			setDirectionY(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("cone")==0){
			setCone(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("range")==0){
			setRange(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("type")==0){
			setType(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
	}
}
SFVLight::~SFVLight() {
	// TODO Auto-generated destructor stub
}

