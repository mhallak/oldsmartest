/*
 * SFVPlatformPose.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: userws1
 */

#include "SFV/SFVPlatformPose.h"

SFVPlatformPose::SFVPlatformPose():
m_Id(0),
m_locationX(0),
m_locationY(0),
m_locationAzimut(0)
{
	// TODO Auto-generated constructor stub

}

SFVPlatformPose::~SFVPlatformPose() {
	// TODO Auto-generated destructor stub
}

int SFVPlatformPose::getId() const {
	return m_Id;
}

void SFVPlatformPose::setId(int id) {
	m_Id = id;
}

double SFVPlatformPose::getLocationAzimut() const {
	return m_locationAzimut;
}

void SFVPlatformPose::setLocationAzimut(double locationAzimut) {
	m_locationAzimut = locationAzimut;
}

double SFVPlatformPose::getLocationX() const {
	return m_locationX;
}

void SFVPlatformPose::setLocationX(double locationX) {
	m_locationX = locationX;
}

double SFVPlatformPose::getLocationY() const {
	return m_locationY;
}

void SFVPlatformPose::setLocationY(double locationY) {
	m_locationY = locationY;
}

const std::string& SFVPlatformPose::getPlatformName() const {
	return m_platform_name;
}

void SFVPlatformPose::setPlatformName(const std::string& platformName) {
	m_platform_name = platformName;
}


void SFVPlatformPose::setRolledValue(RolledValue * value)
{
	switch(value->getType()._type)
	{
	case ScenarioFeatureType::initial_platform_position_on_map_X_axis:
		setLocationX(value->getValue());
		break;
	case ScenarioFeatureType::initial_platform_position_on_map_Y_axis:
		setLocationY(value->getValue());
		break;
	case ScenarioFeatureType::initial_platform_azimut_on_map:
		setLocationAzimut(value->getValue());
		break;
	}
}


TiXmlElement * SFVPlatformPose::toXMLElement()
{
	std::stringstream ss;
	TiXmlElement * platform_pose= new TiXmlElement( "platform_pose" );
	ss << getId();
	platform_pose->SetAttribute("id",ss.str());
	platform_pose->SetAttribute("name",getPlatformName());
	ss.str("");

	TiXmlElement * platform_poseX= new TiXmlElement( "X" );
	ss << getLocationX();
	TiXmlText * platform_poseXVal= new TiXmlText( ss.str() );
	ss.str("");
	platform_poseX->LinkEndChild(platform_poseXVal);
	platform_pose->LinkEndChild(platform_poseX);

	TiXmlElement * platform_poseY= new TiXmlElement( "Y" );
	ss << getLocationY();
	TiXmlText * platform_poseYVal= new TiXmlText( ss.str() );
	ss.str("");
	platform_poseY->LinkEndChild(platform_poseYVal);
	platform_pose->LinkEndChild(platform_poseY);

	TiXmlElement * platform_poseAzimut= new TiXmlElement( "Azimut" );
	ss << getLocationAzimut();
	TiXmlText * platform_poseAzimutVal= new TiXmlText( ss.str() );
	ss.str("");
	platform_poseAzimut->LinkEndChild(platform_poseAzimutVal);
	platform_pose->LinkEndChild(platform_poseAzimut);

	return platform_pose;
}

void SFVPlatformPose::fromXMLElement(TiXmlElement * xmlElement)
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
			setPlatformName(pAttrib->ValueStr());
		}
	}

	for ( pChild = xmlElement->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
	{
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("X")==0){
			setLocationX(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("Y")==0){
			setLocationY(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("Azimut")==0){
			setLocationAzimut(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
	}
}

