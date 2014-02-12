/*
 * PolygonMaker.h
 *
 *  Created on: Jan 30, 2014
 *      Author: userws1
 */

#ifndef POLYGONMAKER_H_
#define POLYGONMAKER_H_
#include "Vertex.h"
#include "Face.h"
#include <vector>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

class PolygonMaker {
public:
	vector<vector<Vertex *>*> * vertexMap;
	vector<Face *> * faces;
	int vertexCount;
	float _lengthFactor;
	float _widthFactor;
	float _heightFactor;

	PolygonMaker(float lengthFactor,float widthFactor,float heightFactor);
	virtual ~PolygonMaker();
	void loadFromMat(cv::Mat heightmap);
	void projectImage(cv::Mat heightmap);
	void outputPLYFile(std::string filename);
	void outputSTLFile(std::string filename,bool binary);
};

#endif /* POLYGONMAKER_H_ */
