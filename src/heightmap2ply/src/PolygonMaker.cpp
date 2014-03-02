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

#include <tinyxml.h>
#include "PolygonMaker.h"

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/postprocess.h>

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
	for(int i=0;i<heightmap.cols
	;i++)
	{
		vertexMap->push_back(new vector<Vertex *>);
		for(int j=0;j<heightmap.rows
		;j++)
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
	for(int i=1;i<heightmap.cols;
	i++)
	{
		for(int j=1;j<heightmap.rows;
				j++)
		{
			//upsideDown
			//faces->push_back(new Face(vertexMap->at(i-1)->at(j-1),vertexMap->at(i-1)->at(j),vertexMap->at(i)->at(j-1)));
			//faces->push_back(new Face(vertexMap->at(i)->at(j),vertexMap->at(i)->at(j-1),vertexMap->at(i-1)->at(j)));
			faces->push_back(new Face(vertexMap->at(i)->at(j-1),vertexMap->at(i-1)->at(j),vertexMap->at(i-1)->at(j-1)));
			faces->push_back(new Face(vertexMap->at(i-1)->at(j),vertexMap->at(i)->at(j-1),vertexMap->at(i)->at(j)));
		}
	}

	for(int i= 0 ; i< vertexMap->size(); i++)
		{
			for(int j = 0 ; j < vertexMap->at(i)->size();j++)
			{
				vertexMap->at(i)->at(j)->setXTexCord(((float)i)/((float) vertexMap->size()));
				vertexMap->at(i)->at(j)->setYTexCord(1-((float)j)/((float) vertexMap->at(i)->size()));
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
	myfile << "comment TextureFile mapHColor.jpg\n";
	myfile << "element vertex ";
	myfile << vertexCount;
	myfile << "\n";
	myfile << "property float x\n";
	myfile << "property float y\n";
	myfile << "property float z\n";
	myfile << "element face ";
	myfile << faces->size();
	myfile << "\n";
	myfile << "property list uchar int vertex_index\n";
	myfile << "property list uchar float texcoord\n";
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
		//cout << faces->at(i)->toString() <<"\n";
		myfile << faces->at(i)->toString() <<"\n";
	}
	myfile.close();
}


void PolygonMaker::outputDAEFile(std::string filename)
{
	  TiXmlDocument doc(filename);
	  TiXmlElement * elem;
	  string dateTime = "Wed Feb 26 11:17:12 2014";

	  // Set XML declaration
	  doc.LinkEndChild(new TiXmlDeclaration("1.0", "utf-8", ""));

	  // Create root node
	  TiXmlElement * root = new TiXmlElement("COLLADA");
	  doc.LinkEndChild(root);
	  root->SetAttribute("xmlns", "http://www.collada.org/2005/11/COLLADASchema");
	  root->SetAttribute("version", "1.4.1");

	  // Create traceability nodes
	  TiXmlElement * asset = new TiXmlElement("asset");
	  root->LinkEndChild(asset);
	  TiXmlElement * contributor = new TiXmlElement("contributor");
	  asset->LinkEndChild(contributor);
	  TiXmlElement * authoring_tool = new TiXmlElement("authoring_tool");
	  contributor->LinkEndChild(authoring_tool);
	  authoring_tool->LinkEndChild(new TiXmlText("heightmap2ply"));
	  TiXmlElement * comments = new TiXmlElement("comments");
	  contributor->LinkEndChild(comments);
	  comments->LinkEndChild(new TiXmlText("no comment"));
	  elem = new TiXmlElement("created");
	  asset->LinkEndChild(elem);
	  elem->LinkEndChild(new TiXmlText(dateTime.c_str()));
	  elem = new TiXmlElement("modified");
	  asset->LinkEndChild(elem);
	  elem->LinkEndChild(new TiXmlText(dateTime.c_str()));

	  //add library images
	  TiXmlElement *library_images =new TiXmlElement("library_images");
	  root->LinkEndChild(library_images);
	  TiXmlElement *image =new TiXmlElement("image");
	  image->SetAttribute("id","texture0");
	  image->SetAttribute("name","texture0");
	  library_images->LinkEndChild(image);
	  elem = new TiXmlElement("init_from");
	  image->LinkEndChild(elem);
	  elem->LinkEndChild(new TiXmlText("mapHColor.jpg"));


	  //add library materials
	  TiXmlElement *library_materials =new TiXmlElement("library_materials");
	  root->LinkEndChild(library_materials);
	  TiXmlElement *material =new TiXmlElement("material");
	  material->SetAttribute("id","material0");
	  material->SetAttribute("name","material0");
	  library_materials->LinkEndChild(material);
	  elem = new TiXmlElement("instance_effect");
	  material->LinkEndChild(elem);
	  elem->SetAttribute("url","#material0-fx");

	  //add library effects
	  TiXmlElement *library_effects =new TiXmlElement("library_effects");
	  root->LinkEndChild(library_effects);
	  TiXmlElement *effect =new TiXmlElement("effect");
	  effect->SetAttribute("id","material0-fx");
	  library_effects->LinkEndChild(effect);
	  TiXmlElement *profile = new TiXmlElement("profile_COMMON");
	  effect->LinkEndChild(profile);

	  TiXmlElement *newparam =new TiXmlElement("newparam");
	  profile->LinkEndChild(newparam);
	  newparam->SetAttribute("sid","texture0-surface");
	  TiXmlElement *surface =new TiXmlElement("surface");
	  newparam->LinkEndChild(surface);
	  surface->SetAttribute("type","2D");
	  elem = new TiXmlElement("init_from");
	  surface->LinkEndChild(elem);
	  elem->LinkEndChild(new TiXmlText("texture0"));
	  elem = new TiXmlElement("format");
	  surface->LinkEndChild(elem);
	  elem->LinkEndChild(new TiXmlText("R8G8B8"));


	  newparam =new TiXmlElement("newparam");
	  profile->LinkEndChild(newparam);
	  newparam->SetAttribute("sid","texture0-sampler");
	  surface =new TiXmlElement("sampler2D");
	  newparam->LinkEndChild(surface);
	  elem = new TiXmlElement("source");
	  surface->LinkEndChild(elem);
	  elem->LinkEndChild(new TiXmlText("texture0-surface"));
	  elem = new TiXmlElement("minfilter");
	  surface->LinkEndChild(elem);
	  elem->LinkEndChild(new TiXmlText("LINEAR"));
	  elem = new TiXmlElement("magfilter");
	  surface->LinkEndChild(elem);
	  elem->LinkEndChild(new TiXmlText("LINEAR"));

	  TiXmlElement *technique =new TiXmlElement("technique");
	  profile->LinkEndChild(technique);
	  technique->SetAttribute("sid","common");
	  TiXmlElement *blinn =new TiXmlElement("blinn");
	  technique->LinkEndChild(blinn);
	  TiXmlElement *emission = new TiXmlElement("emission");
	  blinn->LinkEndChild(emission);
	  TiXmlElement *color = new TiXmlElement("color");
	  emission->LinkEndChild(color);
	  color->LinkEndChild(new TiXmlText("0 0 0 1"));

	  TiXmlElement *ambient = new TiXmlElement("ambient");
	  blinn->LinkEndChild(ambient);
	  color = new TiXmlElement("color");
	  ambient->LinkEndChild(color);
	  color->LinkEndChild(new TiXmlText("0 0 0 1"));

	  TiXmlElement *diffuse = new TiXmlElement("diffuse");
	  blinn->LinkEndChild(diffuse);
	  diffuse->SetAttribute("texture","texture0");
	  diffuse->SetAttribute("texcoord","UVSET0");

	  TiXmlElement *specular = new TiXmlElement("specular");
	  blinn->LinkEndChild(specular);
	  color = new TiXmlElement("color");
	  specular->LinkEndChild(color);
	  color->LinkEndChild(new TiXmlText("0 0 0 1"));

	  TiXmlElement *shininess = new TiXmlElement("shininess");
	  blinn->LinkEndChild(shininess);
	  color = new TiXmlElement("float");
	  shininess->LinkEndChild(color);
	  color->LinkEndChild(new TiXmlText("0.3"));

	  TiXmlElement *reflective= new TiXmlElement("reflective");
	  blinn->LinkEndChild(reflective);
	  color = new TiXmlElement("color");
	  reflective->LinkEndChild(color);
	  color->LinkEndChild(new TiXmlText("0 0 0 1"));

	  TiXmlElement *reflectivity = new TiXmlElement("reflectivity");
	  blinn->LinkEndChild(reflectivity);
	  color = new TiXmlElement("float");
	  reflectivity->LinkEndChild(color);
	  color->LinkEndChild(new TiXmlText("0.5"));

	  TiXmlElement *transparent = new TiXmlElement("transparent");
	  blinn->LinkEndChild(transparent);
	  color = new TiXmlElement("color");
	  transparent->LinkEndChild(color);
	  color->LinkEndChild(new TiXmlText("0 0 0 1"));

	  TiXmlElement *transparency = new TiXmlElement("transparency");
	  blinn->LinkEndChild(transparency);
	  color = new TiXmlElement("float");
	  transparency->LinkEndChild(color);
	  color->LinkEndChild(new TiXmlText("0"));
	  TiXmlElement *index_of_refraction = new TiXmlElement("index_of_refraction");
	  blinn->LinkEndChild(index_of_refraction);
	  color = new TiXmlElement("float");
	  index_of_refraction->LinkEndChild(color);
	  color->LinkEndChild(new TiXmlText("0"));



	  // Create the geometry nodes
	  TiXmlElement * library_geometries = new TiXmlElement("library_geometries");
	  root->LinkEndChild(library_geometries);
	  TiXmlElement * geometry = new TiXmlElement("geometry");
	  library_geometries->LinkEndChild(geometry);
	  geometry->SetAttribute("id", "shape0-lib");
	  geometry->SetAttribute("name", "shape0");
	  TiXmlElement * mesh = new TiXmlElement("mesh");
	  geometry->LinkEndChild(mesh);

	  // Vertices (positions)
	  TiXmlElement * source_position = new TiXmlElement("source");
	  mesh->LinkEndChild(source_position);
	  source_position->SetAttribute("id", "shape0-lib-positions");
	  source_position->SetAttribute("name", "position");
	  TiXmlElement * positions_array = new TiXmlElement("float_array");
	  source_position->LinkEndChild(positions_array);
	  positions_array->SetAttribute("id", "shape0-lib-positions-array");
	  positions_array->SetAttribute("count", int(vertexCount * 3));
	  stringstream ss;
	  for(int i=0;i<vertexMap->size();i++)
	  	{
	  		for(int j=0;j<vertexMap->at(i)->size();j++)
	  		{
	  			ss << vertexMap->at(i)->at(j)->toString() << " ";
	  		}
	  	}
	  positions_array->LinkEndChild(new TiXmlText(ss.str()));


	  TiXmlElement * positions_technique = new TiXmlElement("technique_common");
	  source_position->LinkEndChild(positions_technique);
	  TiXmlElement * positions_technique_accessor = new TiXmlElement("accessor");
	  positions_technique->LinkEndChild(positions_technique_accessor);
	  positions_technique_accessor->SetAttribute("count", vertexCount);
	  positions_technique_accessor->SetAttribute("offset", 0);
	  positions_technique_accessor->SetAttribute("source", "#shape0-lib-positions-array");
	  positions_technique_accessor->SetAttribute("stride", 3);
	  elem = new TiXmlElement("param");
	  positions_technique_accessor->LinkEndChild(elem);
	  elem->SetAttribute("name", "X");
	  elem->SetAttribute("type", "float");
	  elem = new TiXmlElement("param");
	  positions_technique_accessor->LinkEndChild(elem);
	  elem->SetAttribute("name", "Y");
	  elem->SetAttribute("type", "float");
	  elem = new TiXmlElement("param");
	  positions_technique_accessor->LinkEndChild(elem);
	  elem->SetAttribute("name", "Z");
	  elem->SetAttribute("type", "float");



	  TiXmlElement * source_map1 = new TiXmlElement("source");
	  mesh->LinkEndChild(source_map1);
	  source_map1->SetAttribute("id", "shape0-lib-map");
	  source_map1->SetAttribute("name", "map");
	  TiXmlElement * map1_array = new TiXmlElement("float_array");
	  source_map1->LinkEndChild(map1_array);
	  map1_array->SetAttribute("id", "shape0-lib-map-array");
	  map1_array->SetAttribute("count", int(vertexCount * 2));

	  ss.str("");
	  for(int i=0;i<vertexMap->size();i++)
	  	{
	  		for(int j=0;j<vertexMap->at(i)->size();j++)
	  		{
	  			ss << vertexMap->at(i)->at(j)->getXTexCord() << " ";
	  			ss << vertexMap->at(i)->at(j)->getYTexCord() << " ";
	  		}
	  	}
	  map1_array->LinkEndChild(new TiXmlText(ss.str()));


	  TiXmlElement * map1_technique = new TiXmlElement("technique_common");
	  source_map1->LinkEndChild(map1_technique);
	  TiXmlElement * map1_technique_accessor = new TiXmlElement("accessor");
	  map1_technique->LinkEndChild(map1_technique_accessor);
	  map1_technique_accessor->SetAttribute("count", int(vertexCount));
	  map1_technique_accessor->SetAttribute("offset", 0);
	  map1_technique_accessor->SetAttribute("source", "#shape0-lib-map-array");
	  map1_technique_accessor->SetAttribute("stride", 2);
	  elem = new TiXmlElement("param");
	  map1_technique_accessor->LinkEndChild(elem);
	  elem->SetAttribute("name", "U");
	  elem->SetAttribute("type", "float");
	  elem = new TiXmlElement("param");
	  map1_technique_accessor->LinkEndChild(elem);
	  elem->SetAttribute("name", "V");
	  elem->SetAttribute("type", "float");




	  // Vertices
	  TiXmlElement * vertices = new TiXmlElement("vertices");
	  mesh->LinkEndChild(vertices);
	  vertices->SetAttribute("id", "shape0-lib-vertices");
	  TiXmlElement * vertices_input = new TiXmlElement("input");
	  vertices->LinkEndChild(vertices_input);
	  vertices_input->SetAttribute("semantic", "POSITION");
	  vertices_input->SetAttribute("source", "#shape0-lib-positions");

	  // Triangles
	  TiXmlElement * triangles = new TiXmlElement("triangles");
	  mesh->LinkEndChild(triangles);
	  triangles->SetAttribute("count", faces->size());
	  triangles->SetAttribute("material", "material0");
	  elem = new TiXmlElement("input");
	  triangles->LinkEndChild(elem);
	  elem->SetAttribute("offset", 0);
	  elem->SetAttribute("semantic", "VERTEX");
	  elem->SetAttribute("source", "#shape0-lib-vertices");
	  elem = new TiXmlElement("input");
	  triangles->LinkEndChild(elem);
	  elem->SetAttribute("offset", 1);
	  elem->SetAttribute("semantic", "TEXCOORD");
	  elem->SetAttribute("source", "#shape0-lib-map");
	  elem = new TiXmlElement("p");
	  triangles->LinkEndChild(elem);
	  ss.str("");
	  for(int i=0;i<faces->size();i++)
	  {
		  ss<< " "<<faces->at(i)->_v1->getNum() << " " << faces->at(i)->_v1->getNum();
		  ss<< " "<<faces->at(i)->_v2->getNum() << " " << faces->at(i)->_v2->getNum();
		  ss<< " "<<faces->at(i)->_v3->getNum() << " " << faces->at(i)->_v3->getNum();
	  }
	  elem->LinkEndChild(new TiXmlText(ss.str()));




	  // Scene
	  TiXmlElement * library_visual_scenes = new TiXmlElement("library_visual_scenes");
	  root->LinkEndChild(library_visual_scenes);
	  TiXmlElement * visual_scene = new TiXmlElement("visual_scene");
	  library_visual_scenes->LinkEndChild(visual_scene);
	  visual_scene->SetAttribute("id", "VisualSceneNode");
	  visual_scene->SetAttribute("name", "VisualScene");
	  TiXmlElement * visual_scene_node = new TiXmlElement("node");
	  visual_scene->LinkEndChild(visual_scene_node);
	  visual_scene_node->SetAttribute("id", "node");
	  visual_scene_node->SetAttribute("name", "node");
	  TiXmlElement * instance_geometry = new TiXmlElement("instance_geometry");
	  visual_scene_node->LinkEndChild(instance_geometry);
	  instance_geometry->SetAttribute("url", "#shape0-lib");

	  TiXmlElement * bind_material= new TiXmlElement("bind_material");
	  instance_geometry->LinkEndChild(bind_material);
	  TiXmlElement * bind_tecnique=new TiXmlElement("technique_common");
	  bind_material->LinkEndChild(bind_tecnique);
	  TiXmlElement * instanceMaterial=new TiXmlElement("instance_material");
	  bind_tecnique->LinkEndChild(instanceMaterial);
	  instanceMaterial->SetAttribute("symbol","material0");
	  instanceMaterial->SetAttribute("target","#material0");
	  TiXmlElement * bind_vertex_input=new TiXmlElement("bind_vertex_input");
	  instanceMaterial->LinkEndChild(bind_vertex_input);
	  bind_vertex_input->SetAttribute("semantic","UVSET0");
	  bind_vertex_input->SetAttribute("input_semantic","TEXCOORD");

	  TiXmlElement * scene = new TiXmlElement("scene");
	  root->LinkEndChild(scene);
	  TiXmlElement * instance_visual_scene = new TiXmlElement("instance_visual_scene");
	  scene->LinkEndChild(instance_visual_scene);
	  instance_visual_scene->SetAttribute("url", "#VisualSceneNode");

	  // Save the XML document to a file
	  doc.SaveFile(filename.c_str());
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
