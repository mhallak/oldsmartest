/*
 * Face.h
 *
 *  Created on: Jan 29, 2014
 *      Author: userws1
 */

#ifndef FACE_H_
#define FACE_H_
#include <string>
class Vertex;

class Face {

public:
	Vertex *_v1;
	Vertex *_v2;
	Vertex *_v3;
	Vertex *_v4;
	Face(Vertex *v1,Vertex* v2,Vertex* v3,Vertex* v4);
	virtual ~Face();
	std::string toString();
};

#endif /* FACE_H_ */
