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

SFVLight::~SFVLight() {
	// TODO Auto-generated destructor stub
}

