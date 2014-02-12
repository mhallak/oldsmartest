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
	_r=255;
	_g=255;
	_b=255;
}

Vertex::~Vertex() {

}


void Vertex::setRGB(int r,int g,int b)
{
	_r=r;
	_g=g;
	_b=b;
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
	ss<<""<<_x <<" "<< _y <<" "<< _z<<" "<<_r<<" "<<_g<<" "<<_b;
	return ss.str();
}
