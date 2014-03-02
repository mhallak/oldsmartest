/*
 * Vertex.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: userws1
 */

#include "Vertex.h"
#include <stdio.h>
#include <sstream>

Vertex::Vertex(int num,float x,float y,float z)
{
	_num=num;
	_x=x;
	_y=y;
	_z=z;
	_XTexCord=0;
	_YTexCord=0;
}

Vertex::~Vertex() {

}



int Vertex::getNum() const
{
	return _num;
}

float Vertex::getX() const
{
	return _x;
}

float Vertex::getY() const
{
	return _y;
}

float Vertex::getZ() const
{
	return _z;
}

std::string Vertex::toString()
{
	std::stringstream ss;
	ss<<""<<_x <<" "<< _y <<" "<< _z;
	return ss.str();
}

float Vertex::getXTexCord() const {
	return _XTexCord;
}

void Vertex::setXTexCord(float texCord) {
	_XTexCord = texCord;
}

float Vertex::getYTexCord() const {
	return _YTexCord;
}

void Vertex::setYTexCord(float texCord) {
	_YTexCord = texCord;
}
