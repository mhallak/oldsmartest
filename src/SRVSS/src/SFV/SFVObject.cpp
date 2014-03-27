/*
 * SFVObject.cpp
 *
 *  Created on: Feb 24, 2014
 *      Author: userws1
 */

#include "SFV/SFVObject.h"

SFVObject::SFVObject():
m_Id(0),
m_Type(0),
m_X(0),
m_Y(0),
m_Z(0),
m_Roll(0),
m_Pitch(0),
m_Yaw(0),
m_Scale(0)
{
}

double SFVObject::getPitch() const {
	return m_Pitch;
}

void SFVObject::setPitch(double pitch) {
	m_Pitch = pitch;
}

double SFVObject::getRoll() const {
	return m_Roll;
}

void SFVObject::setRoll(double roll) {
	m_Roll = roll;
}

double SFVObject::getScale() const {
	return m_Scale;
}

void SFVObject::setScale(double scale) {
	m_Scale = scale;
}

int SFVObject::getType() const {
	return m_Type;
}

void SFVObject::setType(int type) {
	m_Type = type;
}

double SFVObject::getX() const {
	return m_X;
}

void SFVObject::setX(double x) {
	m_X = x;
}

double SFVObject::getY() const {
	return m_Y;
}

void SFVObject::setY(double y) {
	m_Y = y;
}

double SFVObject::getYaw() const {
	return m_Yaw;
}

void SFVObject::setYaw(double yaw) {
	m_Yaw = yaw;
}

double SFVObject::getZ() const {
	return m_Z;
}

int SFVObject::getId() const {
	return m_Id;
}

void SFVObject::setId(int id) {
	m_Id = id;
}

void SFVObject::setZ(double z) {
	m_Z = z;
}

void SFVObject::setRolledValue(RolledValue * value)
{
	switch(value->getType()._type)
	{
	case ScenarioFeatureType::object_i_type:
		setType(value->getValue());
		break;
	case ScenarioFeatureType::object_i_scaling_factor:
		setScale(value->getValue());
		break;
	case ScenarioFeatureType::object_i_location_on_the_X_axis:
		setX(value->getValue());
		break;
	case ScenarioFeatureType::object_i_location_on_the_Y_axis:
		setY(value->getValue());
		break;
	case ScenarioFeatureType::object_i_location_on_the_Z_axis:
		setZ(value->getValue());
		break;
	case ScenarioFeatureType::object_i_location_Roll:
		setRoll(value->getValue());
		break;
	case ScenarioFeatureType::object_i_location_Pitch:
		setPitch(value->getValue());
		break;
	case ScenarioFeatureType::object_i_location_Yaw:
		setYaw(value->getValue());
		break;
	}
}


TiXmlElement * SFVObject::toXMLElement()
{
	std::stringstream ss;
	TiXmlElement * object= new TiXmlElement( "object" );
	ss << getId();
	object->SetAttribute("id",ss.str());
	ss.str("");

	TiXmlElement * objectType= new TiXmlElement( "type" );
	ss << getType();
	TiXmlText * objectTypeVal= new TiXmlText( ss.str() );
	ss.str("");
	objectType->LinkEndChild(objectTypeVal);
	object->LinkEndChild(objectType);

	TiXmlElement * objectX= new TiXmlElement( "X" );
	ss << getX();
	TiXmlText * objectXVal= new TiXmlText( ss.str() );
	ss.str("");
	objectX->LinkEndChild(objectXVal);
	object->LinkEndChild(objectX);

	TiXmlElement * objectY= new TiXmlElement( "Y" );
	ss << getY();
	TiXmlText * objectYVal= new TiXmlText( ss.str() );
	ss.str("");
	objectY->LinkEndChild(objectYVal);
	object->LinkEndChild(objectY);

	TiXmlElement * objectZ= new TiXmlElement( "Z" );
	ss << getZ();
	TiXmlText * objectZVal= new TiXmlText( ss.str() );
	ss.str("");
	objectZ->LinkEndChild(objectZVal);
	object->LinkEndChild(objectZ);

	TiXmlElement * objectRoll= new TiXmlElement( "roll" );
	ss << getRoll();
	TiXmlText * objectRollVal= new TiXmlText( ss.str() );
	ss.str("");
	objectRoll->LinkEndChild(objectRollVal);
	object->LinkEndChild(objectRoll);

	TiXmlElement * objectPitch= new TiXmlElement( "pitch" );
	ss << getPitch();
	TiXmlText * objectPitchVal= new TiXmlText( ss.str() );
	ss.str("");
	objectPitch->LinkEndChild(objectPitchVal);
	object->LinkEndChild(objectPitch);

	TiXmlElement * objectYaw= new TiXmlElement( "yaw" );
	ss << getYaw();
	TiXmlText * objectYawVal= new TiXmlText( ss.str() );
	ss.str("");
	objectYaw->LinkEndChild(objectYawVal);
	object->LinkEndChild(objectYaw);

	TiXmlElement * objectScale= new TiXmlElement( "scale" );
	ss << getScale();
	TiXmlText * objectScaleVal= new TiXmlText( ss.str() );
	ss.str("");
	objectScale->LinkEndChild(objectScaleVal);
	object->LinkEndChild(objectScale);

	return object;
}

void SFVObject::fromXMLElement(TiXmlElement * xmlElement)
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
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("roll")==0){
			setRoll(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("pitch")==0){
			setPitch(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("yaw")==0){
			setYaw(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("scale")==0){
			setScale(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("type")==0){
			setType(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
	}
}


SFVObject::~SFVObject()
{
}

