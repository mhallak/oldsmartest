/*
 * SFVSensorLink.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#include "SFV/SFVSensorLink.h"

SFVSensorLink::SFVSensorLink() {
	// TODO Auto-generated constructor stub

}

int SFVSensorLink::getId() const {
	return m_Id;
}

void SFVSensorLink::setId(int id) {
	m_Id = id;
}

double SFVSensorLink::getLocationPitchDeviation() const {
	return m_locationPitchDeviation;
}

void SFVSensorLink::setLocationPitchDeviation(double locationPitchDeviation) {
	m_locationPitchDeviation = locationPitchDeviation;
}

double SFVSensorLink::getLocationRollDeviation() const {
	return m_locationRollDeviation;
}

void SFVSensorLink::setLocationRollDeviation(double locationRollDeviation) {
	m_locationRollDeviation = locationRollDeviation;
}

double SFVSensorLink::getLocationXDeviation() const {
	return m_locationXDeviation;
}

void SFVSensorLink::setLocationXDeviation(double locationXDeviation) {
	m_locationXDeviation = locationXDeviation;
}

double SFVSensorLink::getLocationYawDeviation() const {
	return m_locationYawDeviation;
}

void SFVSensorLink::setLocationYawDeviation(double locationYawDeviation) {
	m_locationYawDeviation = locationYawDeviation;
}

double SFVSensorLink::getLocationYDeviation() const {
	return m_locationYDeviation;
}

void SFVSensorLink::setLocationYDeviation(double locationYDeviation) {
	m_locationYDeviation = locationYDeviation;
}

double SFVSensorLink::getLocationZDeviation() const {
	return m_locationZDeviation;
}

void SFVSensorLink::setLocationZDeviation(double locationZDeviation) {
	m_locationZDeviation = locationZDeviation;
}

SFVSensorLink::~SFVSensorLink() {
	// TODO Auto-generated destructor stub
}

void SFVSensorLink::setRolledValue(RolledValue * value)
{
	switch(value->getType()._type)
	{
		case ScenarioFeatureType::sensor_link_i_location_deviation_X:
			setLocationXDeviation(value->getValue());
			break;
		case ScenarioFeatureType::sensor_link_i_location_deviation_Y:
			setLocationYDeviation(value->getValue());
			break;
		case ScenarioFeatureType::sensor_link_i_location_deviation_Z:
			setLocationZDeviation(value->getValue());
			break;
		case ScenarioFeatureType::sensor_link_i_location_deviation_Roll:
			setLocationRollDeviation(value->getValue());
			break;
		case ScenarioFeatureType::sensor_link_i_location_deviation_Pitch:
			setLocationPitchDeviation(value->getValue());
			break;
		case ScenarioFeatureType::sensor_link_i_location_deviation_Yaw:
			setLocationYawDeviation(value->getValue());
			break;
	}
}


TiXmlElement * SFVSensorLink::toXMLElement()
{
	std::stringstream ss;
	TiXmlElement * sensor_link= new TiXmlElement( "sensor_link" );
	ss << getId();
	sensor_link->SetAttribute("id",ss.str());
	sensor_link->SetAttribute("name",getLinkName());
	ss.str("");

	TiXmlElement * sensor_linkLocationXDeviation= new TiXmlElement( "locationXDeviation" );
	ss << getLocationXDeviation();
	TiXmlText * sensor_linkDirectionXVal= new TiXmlText( ss.str() );
	ss.str("");
	sensor_linkLocationXDeviation->LinkEndChild(sensor_linkDirectionXVal);
	sensor_link->LinkEndChild(sensor_linkLocationXDeviation);

	TiXmlElement * sensor_linkLocationYDeviation= new TiXmlElement( "locationYDeviation" );
	ss << getLocationYDeviation();
	TiXmlText * sensor_linkDirectionYVal= new TiXmlText( ss.str() );
	ss.str("");
	sensor_linkLocationYDeviation->LinkEndChild(sensor_linkDirectionYVal);
	sensor_link->LinkEndChild(sensor_linkLocationYDeviation);

	TiXmlElement * sensor_linkLocationZDeviation= new TiXmlElement( "locationZDeviation" );
	ss << getLocationZDeviation();
	TiXmlText * sensor_linkConeVal= new TiXmlText( ss.str() );
	ss.str("");
	sensor_linkLocationZDeviation->LinkEndChild(sensor_linkConeVal);
	sensor_link->LinkEndChild(sensor_linkLocationZDeviation);

	TiXmlElement * sensor_linkLocationRollDeviation= new TiXmlElement( "locationRollDeviation" );
	ss << getLocationRollDeviation();
	TiXmlText * sensor_linkDirectionRollVal= new TiXmlText( ss.str() );
	ss.str("");
	sensor_linkLocationRollDeviation->LinkEndChild(sensor_linkDirectionRollVal);
	sensor_link->LinkEndChild(sensor_linkLocationRollDeviation);

	TiXmlElement * sensor_linkLocationPitchDeviation= new TiXmlElement( "locationPitchDeviation" );
	ss << getLocationPitchDeviation();
	TiXmlText * sensor_linkDirectionPitchVal= new TiXmlText( ss.str() );
	ss.str("");
	sensor_linkLocationPitchDeviation->LinkEndChild(sensor_linkDirectionPitchVal);
	sensor_link->LinkEndChild(sensor_linkLocationPitchDeviation);

	TiXmlElement * sensor_linkLocationYawDeviation= new TiXmlElement( "locationYawDeviation" );
	ss << getLocationYawDeviation();
	TiXmlText * sensor_linkYawVal= new TiXmlText( ss.str() );
	ss.str("");
	sensor_linkLocationYawDeviation->LinkEndChild(sensor_linkYawVal);
	sensor_link->LinkEndChild(sensor_linkLocationYawDeviation);


	return sensor_link;
}

void SFVSensorLink::fromXMLElement(TiXmlElement * xmlElement)
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
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("locationXDeviation")==0){
			setLocationXDeviation(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("locationYDeviation")==0){
			setLocationYDeviation(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("locationZDeviation")==0){
			setLocationZDeviation(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("locationRollDeviation")==0){
			setLocationRollDeviation(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("locationPitchDeviation")==0){
			setLocationPitchDeviation(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("locationYawDeviation")==0){
			setLocationYawDeviation(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
	}
}

const std::string& SFVSensorLink::getLinkName() const {
	return m_link_name;
}

void SFVSensorLink::setLinkName(const std::string& linkName) {
	m_link_name = linkName;
}
