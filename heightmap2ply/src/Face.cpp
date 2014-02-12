/*
 * Face.cpp
 *
 *  Created on: Jan 29, 2014
 *      Author: userws1
 */

#include "Face.h"
#include "Vertex.h"
#include <sstream>
#include <string>

Face::Face(Vertex *v1,Vertex* v2,Vertex* v3,Vertex* v4) {

	_v1=v1;
	_v2=v2;
	_v3=v3;
	_v4=v4;
}

Face::~Face() {

}

std::string Face::toString()
{
	std::stringstream ss;
	ss<< "4"<<" "<<_v1->getNum()
					<<" "<<_v2->getNum()<<" "<<_v3->getNum()<<" "<<_v4->getNum();
	return ss.str();
}
