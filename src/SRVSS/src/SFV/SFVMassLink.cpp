/*
 * SFVMassLink.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#include "SFV/SFVMassLink.h"

SFVMassLink::SFVMassLink() {
	// TODO Auto-generated constructor stub

}

int SFVMassLink::getId() const {
	return m_Id;
}

void SFVMassLink::setId(int id) {
	m_Id = id;
}

double SFVMassLink::getInertiaIxxComponent() const {
	return m_inertiaIxxComponent;
}

void SFVMassLink::setInertiaIxxComponent(double inertiaIxxComponent) {
	m_inertiaIxxComponent = inertiaIxxComponent;
}

double SFVMassLink::getInertiaIyyComponent() const {
	return m_inertiaIyyComponent;
}

void SFVMassLink::setInertiaIyyComponent(double inertiaIyyComponent) {
	m_inertiaIyyComponent = inertiaIyyComponent;
}

double SFVMassLink::getInertiaIzzComponent() const {
	return m_inertiaIzzComponent;
}

void SFVMassLink::setInertiaIzzComponent(double inertiaIzzComponent) {
	m_inertiaIzzComponent = inertiaIzzComponent;
}

double SFVMassLink::getLocationPitchDeviation() const {
	return m_locationPitchDeviation;
}

void SFVMassLink::setLocationPitchDeviation(double locationPitchDeviation) {
	m_locationPitchDeviation = locationPitchDeviation;
}

double SFVMassLink::getLocationRollDeviation() const {
	return m_locationRollDeviation;
}

void SFVMassLink::setLocationRollDeviation(double locationRollDeviation) {
	m_locationRollDeviation = locationRollDeviation;
}

double SFVMassLink::getLocationXDeviation() const {
	return m_locationXDeviation;
}

void SFVMassLink::setLocationXDeviation(double locationXDeviation) {
	m_locationXDeviation = locationXDeviation;
}

double SFVMassLink::getLocationYawDeviation() const {
	return m_locationYawDeviation;
}

void SFVMassLink::setLocationYawDeviation(double locationYawDeviation) {
	m_locationYawDeviation = locationYawDeviation;
}

double SFVMassLink::getLocationYDeviation() const {
	return m_locationYDeviation;
}

void SFVMassLink::setLocationYDeviation(double locationYDeviation) {
	m_locationYDeviation = locationYDeviation;
}

double SFVMassLink::getLocationZDeviation() const {
	return m_locationZDeviation;
}

void SFVMassLink::setLocationZDeviation(double locationZDeviation) {
	m_locationZDeviation = locationZDeviation;
}

double SFVMassLink::getMass() const {
	return m_mass;
}

void SFVMassLink::setMass(double mass) {
	m_mass = mass;
}

SFVMassLink::~SFVMassLink() {
	// TODO Auto-generated destructor stub
}

void SFVMassLink::setRolledValue(RolledValue * value)
{
	switch(value->getType()._type)
	{
		case ScenarioFeatureType::mass_link_i_mass:
			setMass(value->getValue());
			break;
		case ScenarioFeatureType::mass_link_i_inertia_Ixx_component:
			setInertiaIxxComponent(value->getValue());
			break;
		case ScenarioFeatureType::mass_link_i_inertia_Iyy_component:
			setInertiaIyyComponent(value->getValue());
			break;
		case ScenarioFeatureType::mass_link_i_inertia_Izz_component:
			setInertiaIzzComponent(value->getValue());
			break;
		case ScenarioFeatureType::mass_link_i_location_deviation_X:
			setLocationXDeviation(value->getValue());
			break;
		case ScenarioFeatureType::mass_link_i_location_deviation_Y:
			setLocationYDeviation(value->getValue());
			break;
		case ScenarioFeatureType::mass_link_i_location_deviation_Z:
			setLocationZDeviation(value->getValue());
			break;
		case ScenarioFeatureType::mass_link_i_location_deviation_Roll:
			setLocationRollDeviation(value->getValue());
			break;
		case ScenarioFeatureType::mass_link_i_location_deviation_Pitch:
			setLocationPitchDeviation(value->getValue());
			break;
		case ScenarioFeatureType::mass_link_i_location_deviation_Yaw:
			setLocationYawDeviation(value->getValue());
			break;
	}
}


TiXmlElement * SFVMassLink::toXMLElement()
{
	std::stringstream ss;
	TiXmlElement * mass_link= new TiXmlElement( "mass_link" );
	ss << getId();
	mass_link->SetAttribute("id",ss.str());
	mass_link->SetAttribute("name",getLinkName());
	ss.str("");

	TiXmlElement * mass_linkMass= new TiXmlElement( "mass" );
	ss << getMass();
	TiXmlText * mass_linkMassVal= new TiXmlText( ss.str() );
	ss.str("");
	mass_linkMass->LinkEndChild(mass_linkMassVal);
	mass_link->LinkEndChild(mass_linkMass);

	TiXmlElement * mass_linkInertiaIxx= new TiXmlElement( "inertiaIxxComponent" );
	ss << getInertiaIxxComponent();
	TiXmlText * mass_linkXVal= new TiXmlText( ss.str() );
	ss.str("");
	mass_linkInertiaIxx->LinkEndChild(mass_linkXVal);
	mass_link->LinkEndChild(mass_linkInertiaIxx);

	TiXmlElement * mass_linkInertiaIyy= new TiXmlElement( "inertiaIyyComponent" );
	ss << getInertiaIyyComponent();
	TiXmlText * mass_linkYVal= new TiXmlText( ss.str() );
	ss.str("");
	mass_linkInertiaIyy->LinkEndChild(mass_linkYVal);
	mass_link->LinkEndChild(mass_linkInertiaIyy);

	TiXmlElement * mass_linkInertiaIzzComponent= new TiXmlElement( "inertiaIzzComponent" );
	ss << getInertiaIzzComponent();
	TiXmlText * mass_linkZVal= new TiXmlText( ss.str() );
	ss.str("");
	mass_linkInertiaIzzComponent->LinkEndChild(mass_linkZVal);
	mass_link->LinkEndChild(mass_linkInertiaIzzComponent);

	TiXmlElement * mass_linkLocationXDeviation= new TiXmlElement( "locationXDeviation" );
	ss << getLocationXDeviation();
	TiXmlText * mass_linkDirectionXVal= new TiXmlText( ss.str() );
	ss.str("");
	mass_linkLocationXDeviation->LinkEndChild(mass_linkDirectionXVal);
	mass_link->LinkEndChild(mass_linkLocationXDeviation);

	TiXmlElement * mass_linkLocationYDeviation= new TiXmlElement( "locationYDeviation" );
	ss << getLocationYDeviation();
	TiXmlText * mass_linkDirectionYVal= new TiXmlText( ss.str() );
	ss.str("");
	mass_linkLocationYDeviation->LinkEndChild(mass_linkDirectionYVal);
	mass_link->LinkEndChild(mass_linkLocationYDeviation);

	TiXmlElement * mass_linkLocationZDeviation= new TiXmlElement( "locationZDeviation" );
	ss << getLocationZDeviation();
	TiXmlText * mass_linkConeVal= new TiXmlText( ss.str() );
	ss.str("");
	mass_linkLocationZDeviation->LinkEndChild(mass_linkConeVal);
	mass_link->LinkEndChild(mass_linkLocationZDeviation);


	TiXmlElement * mass_linkLocationRollDeviation= new TiXmlElement( "locationRollDeviation" );
	ss << getLocationRollDeviation();
	TiXmlText * mass_linkDirectionRollVal= new TiXmlText( ss.str() );
	ss.str("");
	mass_linkLocationRollDeviation->LinkEndChild(mass_linkDirectionRollVal);
	mass_link->LinkEndChild(mass_linkLocationRollDeviation);

	TiXmlElement * mass_linkLocationPitchDeviation= new TiXmlElement( "locationPitchDeviation" );
	ss << getLocationPitchDeviation();
	TiXmlText * mass_linkDirectionPitchVal= new TiXmlText( ss.str() );
	ss.str("");
	mass_linkLocationPitchDeviation->LinkEndChild(mass_linkDirectionPitchVal);
	mass_link->LinkEndChild(mass_linkLocationPitchDeviation);

	TiXmlElement * mass_linkLocationYawDeviation= new TiXmlElement( "locationYawDeviation" );
	ss << getLocationYawDeviation();
	TiXmlText * mass_linkYawVal= new TiXmlText( ss.str() );
	ss.str("");
	mass_linkLocationYawDeviation->LinkEndChild(mass_linkYawVal);
	mass_link->LinkEndChild(mass_linkLocationYawDeviation);

	return mass_link;
}

void SFVMassLink::fromXMLElement(TiXmlElement * xmlElement)
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
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("mass")==0){
			setMass(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
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
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("inertiaIxxComponent")==0){
			setInertiaIxxComponent(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("inertiaIyyComponent")==0){
			setInertiaIyyComponent(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
		if(pChild->Type()==XML_ELEMENT && pChild->ValueStr().compare("inertiaIzzComponent")==0){
			setInertiaIzzComponent(atof(pChild->FirstChild()->ToText()->ValueStr().c_str()));
		}
	}
}

const std::string& SFVMassLink::getLinkName() const {
	return m_link_name;
}

void SFVMassLink::setLinkName(const std::string& linkName) {
	m_link_name = linkName;
}
