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
	Face(Vertex *v1,Vertex* v2,Vertex* v3);
	virtual ~Face();
	std::string toString();
	std::string texCordsToString();
};

#endif /* FACE_H_ */
