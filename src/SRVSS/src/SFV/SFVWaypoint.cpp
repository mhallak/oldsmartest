/*
 * SFVWaypoint.cpp
 *
 *  Created on: Apr 10, 2014
 *      Author: userws1
 */

#include "SFV/SFVWaypoint.h"

SFVWaypoint::SFVWaypoint():
m_id(0),
m_relative_angle(0),
m_wp_i_distance_i(0)
{
}

SFVWaypoint::~SFVWaypoint() {
	// TODO Auto-generated destructor stub
}

int SFVWaypoint::getId() const {
	return m_id;
}

void SFVWaypoint::setId(int id) {
	m_id = id;
}

float SFVWaypoint::getRelativeAngle() const {
	return m_relative_angle;
}

void SFVWaypoint::setRelativeAngle(float relativeAngle) {
	m_relative_angle = relativeAngle;
}

float SFVWaypoint::getWpIDistanceI() const {
	return m_wp_i_distance_i;
}

void SFVWaypoint::setWpIDistanceI(float wpIDistanceI) {
	m_wp_i_distance_i = wpIDistanceI;
}

void SFVWaypoint::setRolledValue(RolledValue * value)
{
	switch(value->getType()._type)
	{
	case ScenarioFeatureType::wp_i_distance_i:
		setWpIDistanceI(value->getValue());
		break;
	case ScenarioFeatureType::relative_angle_teta:
		setRelativeAngle(value->getValue());
		break;
	case ScenarioFeatureType::wp_velocity:
		setWpVelocity(value->getValue());
		break;

	}
}


TiXmlElement * SFVWaypoint::toXMLElement()
{
	std::stringstream ss;
	TiXmlElement * waypoint= new TiXmlElement( "waypoint" );
	ss << getId();
	waypoint->SetAttribute("id",ss.str());
	ss.str("");

	TiXmlElement * waypointI_distance= new TiXmlElement( "i_distance" );
	ss << getWpIDistanceI();
	TiXmlText * waypointI_distanceVal= new TiXmlText( ss.str() );
	ss.str("");
	waypointI_distance->LinkEndChild(waypointI_distanceVal);
	waypoint->LinkEndChild(waypointI_distance);

	TiXmlElement * waypointRelative_angle= new TiXmlElement( "relative_angle" );
	ss << getRelativeAngle();
	TiXmlText * waypointRelative_angleVal= new TiXmlText( ss.str() );
	ss.str("");
	waypointRelative_angle->LinkEndChild(waypointRelative_angleVal);
	waypoint->LinkEndChild(waypointRelative_angle);

	TiXmlElement * waypointwp_velocity= new TiXmlElement( "wp_velocity" );
	ss << getWpVelocity();
	TiXmlText * waypointwp_velocityVal= new TiXmlText( ss.str() );
	ss.str("");
	waypointwp_velocity->LinkEndChild(waypointwp_velocityVal);
	waypoint->LinkEndChild(waypointwp_velocity);

	return waypoint;
}

void SFVWaypoint::fromXMLElement(TiXmlElement * xmlElement)
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
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("i_distance")==0){
			setWpIDistanceI(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("relative_angle")==0){
			setRelativeAngle(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("wp_velocity")==0){
			setWpVelocity(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
	}
}

float SFVWaypoint::getWpVelocity() const {
	return m_wp_velocity;
}

void SFVWaypoint::setWpVelocity(float wpVelocty) {
	m_wp_velocity = wpVelocty;
}
