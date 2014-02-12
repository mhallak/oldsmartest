/*
 * PolygonMaker.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: userws1
 */


#include "vtkTIFFWriter.h"
#include "vtkPolyData.h"
#include "vtkPLYReader.h"
#include "vtkTriangleFilter.h"
#include "vtkSTLWriter.h"

#include "PolygonMaker.h"

PolygonMaker::PolygonMaker(float lengthFactor,float widthFactor,float heightFactor):
	_lengthFactor(lengthFactor),
	_widthFactor(widthFactor),
	_heightFactor(heightFactor)
{
	vertexCount=0;
	vertexMap=new vector<vector<Vertex *>*>;
	faces=new vector<Face *>;

}

PolygonMaker::~PolygonMaker() {
}

void PolygonMaker::loadFromMat(cv::Mat heightmap)
{
	vertexMap->clear();
	faces->clear();
	vertexCount=0;
	vertexMap=new vector<vector<Vertex *>*>;
	faces=new vector<Face *>;

	//generate verticles
	for(int i=0;i<heightmap.cols;i++)
	{
		vertexMap->push_back(new vector<Vertex *>);
		for(int j=0;j<heightmap.rows;j++)
		{
			vertexMap->at(i)->push_back(
					new Vertex(vertexCount,
							i*_widthFactor,
							j*_lengthFactor,
							heightmap.at<uchar>(j, i, 0)*_heightFactor));
			vertexCount++;
		}
	}
	//generate faces
	for(int i=1;i<heightmap.cols;i++)
	{
		for(int j=1;j<heightmap.rows;j++)
		{
			faces->push_back(new Face(vertexMap->at(i)->at(j),vertexMap->at(i-1)->at(j),vertexMap->at(i-1)->at(j-1),vertexMap->at(i)->at(j-1)));
		}
	}
}


void PolygonMaker::projectImage(cv::Mat heightmap)
{
	for(int i=0;i<heightmap.cols;i++)
	{
		for(int j=0;j<heightmap.rows;j++)
		{
			vertexMap->at(i)->at(j)->setRGB(heightmap.at<Vec3b>(i, j)[2],heightmap.at<Vec3b>(i, j)[1],heightmap.at<Vec3b>(i, j)[0]);
		}
	}
}

void PolygonMaker::outputPLYFile(std::string filename)
{
	ofstream myfile;
	myfile.open (filename.c_str());
	myfile << "ply\n";
	myfile << "format ascii 1.0\n";
	myfile << "comment author: Yuval Deri\n";
	myfile << "comment object: heightMap\n";
	myfile << "element vertex ";
	myfile << vertexCount;
	myfile << "\n";
	myfile << "property float x\n";
	myfile << "property float y\n";
	myfile << "property float z\n";
	myfile << "property uchar red\n";
	myfile << "property uchar green\n";
	myfile << "property uchar blue\n";
	myfile << "element face ";
	myfile << faces->size();
	myfile << "\n";
	myfile << "property list uchar int vertex_index\n";
	myfile << "end_header\n";
	for(int i=0;i<vertexMap->size();i++)
	{
		for(int j=0;j<vertexMap->at(i)->size();j++)
		{
			myfile << vertexMap->at(i)->at(j)->toString() <<"\n";
		}
	}
	for(int i=0;i<faces->size();i++)
	{
		myfile << faces->at(i)->toString() <<"\n";
	}
	myfile.close();
}

void PolygonMaker::outputSTLFile(std::string filename,bool binary)
{
	outputPLYFile("TEMPexample.ply");
	vtkPLYReader *indata = vtkPLYReader::New();
	indata->SetFileName("TEMPexample.ply");
	indata->Update();

	vtkTriangleFilter *triangles = vtkTriangleFilter::New();
	triangles->SetInputConnection(indata->GetOutputPort());
	triangles->Update();

	//write stl file
	vtkSTLWriter *data = vtkSTLWriter::New();
	data->SetInput(triangles->GetOutput());
	data->SetFileName(filename.c_str());
	if(binary){
		data->SetFileTypeToBinary();
	}else{
		data->SetFileTypeToASCII();
	}
	data->Write();
	data->Delete();
}
