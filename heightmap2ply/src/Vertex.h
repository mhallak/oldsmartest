/*
 * Vertex.h
 *
 *  Created on: Jan 29, 2014
 *      Author: userws1
 */

#ifndef VERTEX_H_
#define VERTEX_H_
#include <string>

class Vertex {
	int   _num;
	float _x;
	float _y;
	float _z;
	int   _r;
	int   _g;
	int   _b;
public:

	Vertex(int num,float x,float y,float z);
	virtual ~Vertex();
	void setRGB(int r,int g,int b);
	int getNum() const;
	float getX() const;
	float getY() const;
	float getZ() const;
	std::string toString();
};



#endif /* VERTEX_H_ */
