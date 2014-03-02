#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/filesystem.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include "PolygonMaker.h"
#include "ModelFileMaker.h"
#include "MaterialFileMaker.h"
#include "DataMaker.h"

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


void moveFile(std::string origin,std::string dest)
{
	boost::filesystem::copy_file( origin,dest,boost::filesystem::copy_option::overwrite_if_exists);
	boost::filesystem::remove(origin);
}

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

	DataMaker * dataMake=new DataMaker();


	float windowWidth=heightmap.cols/(float)numOfWindowsH;
	float windowHeight=heightmap.rows/(float)numOfWindowsV;


	std::string modelName("terrain");
	PolygonMaker * poly=new PolygonMaker(lengthFactor,widthFactor,heightFactor);
	ModelFileMaker *modelMaker=new ModelFileMaker(modelName);
	MaterialFileMaker *materialMaker=new MaterialFileMaker(modelName+".material");

	int counter=1;
	std::stringstream ss;

	std::string path=std::string("output/")+modelName;

	boost::filesystem::create_directories(path);
	boost::filesystem::create_directories(path+"/meshes");
	boost::filesystem::create_directories(path+"/materials/textures");
	boost::filesystem::create_directories(path+"/materials/scripts");


	dataMake->addData("heightmap",argv[1]);
	dataMake->addData("length",argv[2]);
	dataMake->addData("width",argv[3]);
	dataMake->addData("height",argv[4]);
	dataMake->output("data.xml");
	moveFile("data.xml",path+"/"+"data.xml");

	for(int j=0; j<numOfWindowsH;j++)
	{
		for(int i=0; i<numOfWindowsV;i++)
		{
			Rect winROI(j*windowWidth,
					i*windowHeight,
					min(heightmap.cols-j*numOfWindowsH,(int)windowWidth),
					min(heightmap.rows-i*numOfWindowsV,(int)windowHeight));
			Mat mapWin(heightmap,winROI);
			Mat mapcolorWin(mapColor,winROI);

			poly->loadFromMat(mapWin);

			ss<<counter;
			poly->outputDAEFile(modelName+ss.str()+".dae");
			imwrite(modelName+ss.str()+".png",mapcolorWin);

			materialMaker->addMaterial(modelName,modelName+ss.str(),modelName+ss.str()+".png");
			modelMaker->addMesh(modelName+ss.str(),modelName+ss.str()+".dae",(j*(windowWidth-1)*widthFactor),(i*(windowHeight-1)*lengthFactor));

			moveFile(modelName+ss.str()+".png",path+"/materials/textures/"+modelName+ss.str()+".png");
			moveFile(modelName+ss.str()+".dae",path+"/meshes/"+modelName+ss.str()+".dae");


			counter++;
			ss.str("");
		}
	}
	materialMaker->outputFile();
	modelMaker->outputFile("model.sdf");

	moveFile(modelName+".material",path+"/materials/scripts/"+modelName+".material");
	moveFile("model.sdf",path+"/model.sdf");
	moveFile("model.config",path+"/model.config");

	boost::filesystem::copy_file(argv[1],path+"/materials/textures/"+argv[1],boost::filesystem::copy_option::overwrite_if_exists);
	boost::filesystem::copy_file(argv[5],path+"/materials/textures/"+argv[5],boost::filesystem::copy_option::overwrite_if_exists);




	return 0;
}
