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

Face::Face(Vertex *v1,Vertex* v2,Vertex* v3) {

	_v1=v1;
	_v2=v2;
	_v3=v3;
}

Face::~Face() {

}


std::string Face::texCordsToString()
{
	std::stringstream ss;
		ss<<_v1->getXTexCord()
		  <<" "<<_v1->getYTexCord()
		  <<" "<<_v2->getXTexCord()
		  <<" "<<_v2->getYTexCord()
		  <<" "<<_v3->getXTexCord()
		  <<" "<<_v3->getYTexCord();
	return ss.str();
}

std::string Face::toString()
{
	std::stringstream ss;
	ss<< "3"<<" "<<_v1->getNum()
					<<" "<<_v2->getNum()<<" "<<_v3->getNum()<<" 6"<<" "<<_v1->getXTexCord()
																  <<" "<<_v1->getYTexCord()
																  <<" "<<_v2->getXTexCord()
																  <<" "<<_v2->getYTexCord()
																  <<" "<<_v3->getXTexCord()
																  <<" "<<_v3->getYTexCord();
	return ss.str();
}
