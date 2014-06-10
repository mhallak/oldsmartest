/*
 * SFVMassLink.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: userws1
 */

#include "SFV/SFVMassLink.h"

SFVMassLink::SFVMassLink(DPGroup * dpGroup): SFVBase(dpGroup)
{
	setStructure();
	init(dpGroup);
}

void SFVMassLink::setStructure()
{
	m_objectType="MassLink";

	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::mass_link_i_inertia_Ixx_component,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::mass_link_i_inertia_Iyy_component,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::mass_link_i_inertia_Izz_component,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::mass_link_i_location_deviation_Roll,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::mass_link_i_location_deviation_Pitch,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::mass_link_i_location_deviation_Yaw,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::mass_link_i_location_deviation_X,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::mass_link_i_location_deviation_Y,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::mass_link_i_location_deviation_Z,0));
	m_objects->insert(std::pair<ScenarioFeatureType,DPObject*>(ScenarioFeatureType::mass_link_i_mass,0));

}

int SFVMassLink::getId() const {
	return m_Id;
}

void SFVMassLink::setId(int id) {
	m_Id = id;
}

double SFVMassLink::getInertiaIxxComponent() const {
	return m_objects->at(ScenarioFeatureType::mass_link_i_inertia_Ixx_component)->getResult();
}

void SFVMassLink::setInertiaIxxComponent(double inertiaIxxComponent) {
	m_objects->at(ScenarioFeatureType::mass_link_i_inertia_Ixx_component)->setResult(inertiaIxxComponent);
}

double SFVMassLink::getInertiaIyyComponent() const {
	return m_objects->at(ScenarioFeatureType::mass_link_i_inertia_Iyy_component)->getResult();
}

void SFVMassLink::setInertiaIyyComponent(double inertiaIyyComponent) {
	m_objects->at(ScenarioFeatureType::mass_link_i_inertia_Iyy_component)->setResult(inertiaIyyComponent);
}

double SFVMassLink::getInertiaIzzComponent() const {
	return m_objects->at(ScenarioFeatureType::mass_link_i_inertia_Izz_component)->getResult();
}

void SFVMassLink::setInertiaIzzComponent(double inertiaIzzComponent) {
	m_objects->at(ScenarioFeatureType::mass_link_i_inertia_Izz_component)->setResult(inertiaIzzComponent);
}

double SFVMassLink::getLocationPitchDeviation() const {
	return m_objects->at(ScenarioFeatureType::mass_link_i_location_deviation_Pitch)->getResult();
}

void SFVMassLink::setLocationPitchDeviation(double locationPitchDeviation) {
	m_objects->at(ScenarioFeatureType::mass_link_i_location_deviation_Pitch)->setResult(locationPitchDeviation);
}

double SFVMassLink::getLocationRollDeviation() const {
	return m_objects->at(ScenarioFeatureType::mass_link_i_location_deviation_Roll)->getResult();
}

void SFVMassLink::setLocationRollDeviation(double locationRollDeviation) {
	m_objects->at(ScenarioFeatureType::mass_link_i_location_deviation_Roll)->setResult(locationRollDeviation);
}

double SFVMassLink::getLocationXDeviation() const {
	return m_objects->at(ScenarioFeatureType::mass_link_i_location_deviation_X)->getResult();
}

void SFVMassLink::setLocationXDeviation(double locationXDeviation) {
	m_objects->at(ScenarioFeatureType::mass_link_i_location_deviation_X)->setResult(locationXDeviation);
}

double SFVMassLink::getLocationYawDeviation() const {
	return m_objects->at(ScenarioFeatureType::mass_link_i_location_deviation_Yaw)->getResult();
}

void SFVMassLink::setLocationYawDeviation(double locationYawDeviation) {
	m_objects->at(ScenarioFeatureType::mass_link_i_location_deviation_Yaw)->setResult(locationYawDeviation);
}

double SFVMassLink::getLocationYDeviation() const {
	return m_objects->at(ScenarioFeatureType::mass_link_i_location_deviation_Y)->getResult();
}

void SFVMassLink::setLocationYDeviation(double locationYDeviation) {
	m_objects->at(ScenarioFeatureType::mass_link_i_location_deviation_Y)->setResult(locationYDeviation);
}

double SFVMassLink::getLocationZDeviation() const {
	return m_objects->at(ScenarioFeatureType::mass_link_i_location_deviation_Z)->getResult();
}

void SFVMassLink::setLocationZDeviation(double locationZDeviation) {
	m_objects->at(ScenarioFeatureType::mass_link_i_location_deviation_Z)->setResult(locationZDeviation);
}

double SFVMassLink::getMass() const {
	return m_objects->at(ScenarioFeatureType::mass_link_i_mass)->getResult();
}

void SFVMassLink::setMass(double mass) {
	m_objects->at(ScenarioFeatureType::mass_link_i_mass)->setResult(mass);
}

SFVMassLink::~SFVMassLink() {
	// TODO Auto-generated destructor stub
}



 std::string& SFVMassLink::getLinkName() {
	return m_name;
}

void SFVMassLink::setLinkName(const std::string& linkName) {
	m_name = linkName;
}
