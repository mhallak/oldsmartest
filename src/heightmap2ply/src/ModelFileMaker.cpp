/*
 * WorldFileMaker.cpp
 *
 *  Created on: Jan 30, 2014
 *      Author: userws1
 */

#include "ModelFileMaker.h"
#include <tinyxml.h>

ModelFileMaker::ModelFileMaker(std::string modelName)
{
	modelname=modelName;
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );

	TiXmlElement *sdf=new TiXmlElement( "sdf" );
	sdf->SetAttribute("version", "1.4");
	doc.LinkEndChild(sdf);

	modelElement = new TiXmlElement( "model" );
	modelElement->SetAttribute("name", modelName);
	sdf->LinkEndChild(modelElement);

	TiXmlElement *mstatic=new TiXmlElement( "static" );
	mstatic->LinkEndChild( new TiXmlText( "true" ));
	modelElement->LinkEndChild(mstatic);

}

ModelFileMaker::~ModelFileMaker() {
}

void ModelFileMaker::addMesh(std::string objectName,std::string stlName,float poseX,float poseY)
{
	TiXmlElement *link = new TiXmlElement( "link" );
	link->SetAttribute("name", objectName);
	modelElement->LinkEndChild(link);

	TiXmlElement *pose = new TiXmlElement( "pose" );
	std::stringstream ss;
	ss<<poseX<<" "<<poseY<<" 0 0 0 0";
	pose->LinkEndChild(new TiXmlText( ss.str()));
	link->LinkEndChild(pose);

	//collision entry

	TiXmlElement *collison = new TiXmlElement( "collision" );
	collison->SetAttribute("name", objectName+"_collision");
	link->LinkEndChild(collison);

	TiXmlElement *collison_geometry = new TiXmlElement( "geometry" );
	collison->LinkEndChild(collison_geometry);

	TiXmlElement *collison_mesh = new TiXmlElement( "mesh" );
	collison_geometry->LinkEndChild(collison_mesh);

	TiXmlElement *collison_mesh_uri = new TiXmlElement( "uri" );
	collison_mesh_uri->LinkEndChild( new TiXmlText( std::string("model://")+modelname+"/meshes/"+stlName ));
	collison_mesh->LinkEndChild(collison_mesh_uri);

	//visual entry

	TiXmlElement *visual = new TiXmlElement( "visual" );
    visual->SetAttribute("name", objectName+"_visual");
    link->LinkEndChild(visual);

    TiXmlElement *visual_geometry = new TiXmlElement( "geometry" );
    visual->LinkEndChild(visual_geometry);

    TiXmlElement *visual_mesh = new TiXmlElement( "mesh" );
    visual_geometry->LinkEndChild(visual_mesh);

    TiXmlElement *visual_mesh_uri = new TiXmlElement( "uri" );
    visual_mesh_uri->LinkEndChild( new TiXmlText( std::string("model://")+modelname+"/meshes/"+stlName ));
    visual_mesh->LinkEndChild(visual_mesh_uri);


    TiXmlElement *material = new TiXmlElement( "material" );
    visual->LinkEndChild(material);

    TiXmlElement *script = new TiXmlElement( "script" );
    material->LinkEndChild(script);

	TiXmlElement *uri = new TiXmlElement( "uri" );
	uri->LinkEndChild( new TiXmlText( std::string("model://")+modelname+"/materials/scripts"));
	script->LinkEndChild(uri);

	uri = new TiXmlElement( "uri" );
	uri->LinkEndChild( new TiXmlText( std::string("model://")+modelname+"/materials/textures"));
	script->LinkEndChild(uri);

	uri = new TiXmlElement( "name" );
	uri->LinkEndChild( new TiXmlText( modelname+"/"+objectName));
	script->LinkEndChild(uri);

}

void ModelFileMaker::outputConfigFile()
{
	TiXmlDocument config("model.config");
	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
	config.LinkEndChild( decl );

	TiXmlElement *model=new TiXmlElement( "model" );
	config.LinkEndChild(model);

	TiXmlElement *name=new TiXmlElement( "name" );
	model->LinkEndChild(name);
	name->LinkEndChild(new TiXmlText(modelname));

	TiXmlElement *version=new TiXmlElement( "version" );
	model->LinkEndChild(version);
	version->LinkEndChild(new TiXmlText("1.0"));

	TiXmlElement *sdf=new TiXmlElement( "sdf" );
	model->LinkEndChild(sdf);
	sdf->SetAttribute("version","1.4");
	sdf->LinkEndChild(new TiXmlText("model.sdf"));

	TiXmlElement *author=new TiXmlElement( "author" );
	model->LinkEndChild(author);

	name=new TiXmlElement( "name" );
	author->LinkEndChild(name);
	name->LinkEndChild(new TiXmlText("Yuval Deri"));
	TiXmlElement *email=new TiXmlElement( "email" );
	author->LinkEndChild(email);
	email->LinkEndChild(new TiXmlText("yderi@iai.co.il"));

	TiXmlElement *description=new TiXmlElement( "description" );
	model->LinkEndChild(description);
	description->LinkEndChild(new TiXmlText("No description"));

	config.SaveFile("model.config");
}

void ModelFileMaker::outputFile(std::string filename)
{
	doc.SaveFile(filename.c_str());
	outputConfigFile();
}
