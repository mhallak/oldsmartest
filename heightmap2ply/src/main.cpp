#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "PolygonMaker.h"
#include "ModelFileMaker.h"

using namespace cv;
using namespace std;

Mat heightmap;
Mat mapColor;
vector<vector<Vertex *>*> * vertexMap;
vector<Face *> * faces;
float length,width,height;
int numOfWindowsV,numOfWindowsH;
float lengthFactor,widthFactor,heightFactor;
int vertexCount;


int main(int argc,char** argv)
{

	heightmap=imread(argv[1]);
	length=atof(argv[2]);
	width=atof(argv[3]);
	height=atof(argv[4]);
	mapColor=imread(argv[5]);
	numOfWindowsV=atoi(argv[6]);
	numOfWindowsH=atoi(argv[7]);


	lengthFactor=length/heightmap.rows;
	widthFactor=width/heightmap.cols;
	heightFactor=height/255;

	float windowWidth=heightmap.cols/(float)numOfWindowsH;
	float windowHeight=heightmap.rows/(float)numOfWindowsV;


	std::string modelName("terrain");
	PolygonMaker * poly=new PolygonMaker(lengthFactor,widthFactor,heightFactor);
	ModelFileMaker *modelMaker=new ModelFileMaker(modelName);

	int counter=1;
	std::stringstream ss;
	for(int j=0; j<numOfWindowsH;j++)
	{
		for(int i=0; i<numOfWindowsV;i++)
		{
			Rect winROI(j*windowWidth,
					i*windowHeight,
					min(heightmap.cols-j*numOfWindowsH,(int)windowWidth),
					min(heightmap.rows-i*numOfWindowsV,(int)windowHeight));
			Mat mapWin(heightmap,winROI);

			poly->loadFromMat(mapWin);

			ss<<counter;
			poly->outputSTLFile(modelName+ss.str()+".stl",true);
			modelMaker->addMesh(modelName+ss.str(),modelName+ss.str()+".stl",(j*(windowWidth-1)*widthFactor),(i*(windowHeight-1)*lengthFactor));
			counter++;
			ss.str("");
		}
	}
	modelMaker->outputFile("model.sdf");


	return 0;
}
