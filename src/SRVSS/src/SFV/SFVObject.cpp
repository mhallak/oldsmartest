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

SFVObject::~SFVObject()
{
}

