/*
 * EnvironmentGenerator.cpp
 *
 *  Created on: Feb 25, 2014
 *      Author: userws1
 */

#include "Generators/Gazebo/GazeboEnvironmentGenerator.h"
#include "Generators/Gazebo/TerrainAnalyzer.h"
#include "SFV/SFVComponent.h"
#include "SFV/SFVObject.h"
#include "SFV/SFVTerrain.h"
#include "SFV/SFVPath.h"


#include "utils/TinyXmlDef.h"
#include "Resource/ResourceHandler.h"
#include <sstream>
#include <stdlib.h>
#include <sdf/sdf.hh>

#include <iostream>

GazeboEnvironmentGenerator::GazeboEnvironmentGenerator() {
	m_terrainAnalyzer=new TerrainAnalyzer();
	 m_objectCount=0;
	 m_ObstacleOnPathCounter=0;
	 m_WpMarkCounter=0;
}

GazeboEnvironmentGenerator::~GazeboEnvironmentGenerator() {
	// TODO Auto-generated destructor stub
}

void GazeboEnvironmentGenerator::spawnObject(SFVObject* sfvObj,TiXmlElement * element, std::string resources_file_path)
{
	TiXmlElement * include = new TiXmlElement( "include" );
	element->LinkEndChild(include);
	TiXmlElement * url = new TiXmlElement( "uri" );
	TiXmlText * url_text = new TiXmlText(std::string("model://")+ResourceHandler::getInstance(resources_file_path).getObjectById(sfvObj->getType()));
	url->LinkEndChild(url_text);
	include->LinkEndChild(url);
	TiXmlElement * pose = new TiXmlElement( "pose" );
	std::stringstream ss;
	float x,y,z;
	m_terrainAnalyzer->getXYZCoord(sfvObj->getX(),sfvObj->getY(),x,y,z);

	ss<<x <<" " << y <<" "<< z+sfvObj->getZ() << " ";
	ss<<sfvObj->getRoll() <<" " << sfvObj->getPitch() <<" "<< sfvObj->getYaw();
	TiXmlText * pose_text = new TiXmlText(ss.str());
	ss.str("");
	pose->LinkEndChild(pose_text);
	include->LinkEndChild(pose);
	TiXmlElement * scale = new TiXmlElement( "scale" );

	ss<<sfvObj->getScale() <<" " << sfvObj->getScale() <<" "<< sfvObj->getScale();
	TiXmlText * scale_text = new TiXmlText(ss.str());
	ss.str("");
	scale->LinkEndChild(scale_text);
	include->LinkEndChild(scale);
	TiXmlElement * name = new TiXmlElement( "name" );
	include->LinkEndChild(name);
	ss.str("");
	ss<< "object";
	ss<<m_objectCount;
	name->LinkEndChild(new TiXmlText(ss.str()));
	m_objectCount++;
}

void GazeboEnvironmentGenerator::spawnObstacleOnPath(SFVComponent* sfvComp,TiXmlElement * element, std::string resources_file_path)
{
	SFVPlatformPose* platformPose=sfvComp->getPlatformPoses()->at(0);
	float plat_x,plat_y,plat_z;
	m_terrainAnalyzer->getXYZCoord(platformPose->getLocationX(),platformPose->getLocationY(),plat_x,plat_y,plat_z);
    //std::cout <<  "plat_x = " << plat_x <<  "plat_y = " << plat_y << std::endl;
	double plat_init_azi = platformPose->getLocationAzimut();

    SFVPath* path=sfvComp->getPaths()->at(0);
	double path_length = path->getPathLength();

	SFVObstaclesOnPath *obsOnPath = sfvComp->getObstaclesOnPath()->at(0);
	for (SFVObstacleOnPath *obs : *obsOnPath->m_objects)
	{
		TiXmlElement * include = new TiXmlElement( "include" );
		element->LinkEndChild(include);
		TiXmlElement * url = new TiXmlElement( "uri" );

		TiXmlText * url_text = new TiXmlText(std::string("model://")+ResourceHandler::getInstance(resources_file_path).getObjectById(obs->getType()));
		url->LinkEndChild(url_text);
		include->LinkEndChild(url);
		TiXmlElement * pose = new TiXmlElement( "pose" );
		std::stringstream ss;

		double alo = obs->getAlong();
		double per = obs->getPerpendicular();
		double alo_path_pos = alo * path_length;
	    //std::cout <<  "alo = " << alo <<  "  per = " << per << std::endl;
	    double alon_path_dis = 0, azi = plat_init_azi, dis = 0, x=plat_x, y=plat_y, next_x=plat_x, next_y=plat_y;
	    for (SFVWaypoint *wp : *(path->m_objects) )
	    {
	    	azi = azi + wp->getRelativeAngle();
	    	dis = wp->getWpIDistanceI();
	    	next_x = x + dis*cos(azi);
	    	next_y = y + dis*sin(azi);

	    	if ( (alon_path_dis + dis) < alo_path_pos  )
	    	{
	    		alon_path_dis = alon_path_dis + dis;
	    		x = next_x;
	    		y = next_y;
	    	    //std::cout <<  "wp_x = " << x <<  "  wp_y = " << y << std::endl;
	    	}
	    	else
	    	{
	    		break;
	    	}
	    }
	    double rem_alo = ((alo - alon_path_dis/path_length)*path_length)/dis;
	    double obs_x = x + rem_alo * (next_x - x) - per*(next_y - y)/dis;
	    double obs_y = y + rem_alo * (next_y - y) + per*(next_x - x)/dis;
	   // std::cout <<  "obs_x = " << obs_x <<  "  obs_y = " << obs_y << std::endl;

	float obs_z;
	m_terrainAnalyzer->getZCoord(obs_x,obs_y,obs_z);

	ss<<obs_x <<" " << obs_y <<" "<< obs_z+obs->getZ() << " ";
    ss<<obs->getRoll() <<" " << obs->getPitch() <<" "<< obs->getYaw();

    TiXmlText * pose_text = new TiXmlText(ss.str());
	ss.str("");
	pose->LinkEndChild(pose_text);
	include->LinkEndChild(pose);

	TiXmlElement * scale = new TiXmlElement( "scale" );
	ss<<obs->getScale() <<" " << obs->getScale() <<" "<< obs->getScale();
	TiXmlText * scale_text = new TiXmlText(ss.str());
	ss.str("");
	scale->LinkEndChild(scale_text);
	include->LinkEndChild(scale);

	TiXmlElement * name = new TiXmlElement( "name" );
	include->LinkEndChild(name);
	ss.str("");
	ss<< "obstacle_on_path";
	ss<<m_ObstacleOnPathCounter;

	name->LinkEndChild(new TiXmlText(ss.str()));
	m_ObstacleOnPathCounter++;
	}
}


void GazeboEnvironmentGenerator::spawnPathWpMarks(SFVComponent* sfvComp,TiXmlElement * element)
{
	SFVPlatformPose* platformPose=sfvComp->getPlatformPoses()->at(0);
	float plat_x=0,plat_y=0,plat_z=0;
	m_terrainAnalyzer->getXYZCoord(platformPose->getLocationX(),platformPose->getLocationY(),plat_x,plat_y,plat_z);
	double plat_init_azi = platformPose->getLocationAzimut();

    SFVPath* path=sfvComp->getPaths()->at(0);

    double azi = plat_init_azi, dis = 0, wp_x=plat_x, wp_y=plat_y ;
    for (SFVWaypoint *wp : *(path->m_objects) )
	     {
	    	azi = azi + wp->getRelativeAngle();
	    	dis = wp->getWpIDistanceI();
	    	wp_x = wp_x + dis*cos(azi);
	    	wp_y = wp_y + dis*sin(azi);

	   // std::cout <<  "wp_x = " << wp_x <<  "  wp_y = " << wp_y << std::endl;

	    TiXmlElement * include = new TiXmlElement( "include" );
		element->LinkEndChild(include);
		TiXmlElement * url = new TiXmlElement( "uri" );

		TiXmlText * url_text = new TiXmlText("model://wp_mark");
		url->LinkEndChild(url_text);
		include->LinkEndChild(url);

		TiXmlElement * pose = new TiXmlElement( "pose" );
		std::stringstream ss;
		float mark_x = wp_x, mark_y = wp_y, mark_z;
		m_terrainAnalyzer->getZCoord(mark_x,mark_y,mark_z);
		ss<<mark_x <<" " << mark_y <<" "<< mark_z+3 << " ";
		ss<<0 <<" " << 0 <<" "<< 0;
		TiXmlText * pose_text = new TiXmlText(ss.str());
		ss.str("");
		pose->LinkEndChild(pose_text);
		include->LinkEndChild(pose);

		TiXmlElement * name = new TiXmlElement( "name" );
		include->LinkEndChild(name);
		ss.str("");
		ss<< "wp_mark";
		ss<<m_WpMarkCounter;

		name->LinkEndChild(new TiXmlText(ss.str()));
		m_WpMarkCounter++;
	     }
}



void GazeboEnvironmentGenerator::spawnTerrain(SFVTerrain* sfvTerrain,TiXmlElement * element, std::string resources_file_path)
{
	TiXmlElement * include = new TiXmlElement( "include" );
	element->LinkEndChild(include);
	TiXmlElement * url = new TiXmlElement( "uri" );
	TiXmlText * url_text = new TiXmlText(std::string("model://")+ResourceHandler::getInstance(resources_file_path).getTerrainById(sfvTerrain->getTerrainId()));
	url->LinkEndChild(url_text);
	include->LinkEndChild(url);
}

void GazeboEnvironmentGenerator::spawnPlatformPose(SFVPlatformPose* sfvPlatformPose,TiXmlElement * element, std::string resources_file_path)
{
	TiXmlElement * include = new TiXmlElement( "include" );
	element->LinkEndChild(include);
	TiXmlElement * url = new TiXmlElement( "uri" );
	TiXmlText * url_text = new TiXmlText(std::string("model://")+ResourceHandler::getInstance(resources_file_path).getRobotPlatformName());
	url->LinkEndChild(url_text);
	include->LinkEndChild(url);
	TiXmlElement * pose = new TiXmlElement( "pose" );
	std::stringstream ss;
	float x,y,z, azi;
	m_terrainAnalyzer->getXYZCoord(sfvPlatformPose->getLocationX(),sfvPlatformPose->getLocationY(),x,y,z);
    azi = sfvPlatformPose->getLocationAzimut();

	z=z+0.5;  // compensation for the wheels height
	ss<<x <<" " << y <<" "<< z << " ";
	ss<<0 <<" " << 0 <<" "<< azi;
	TiXmlText * pose_text = new TiXmlText(ss.str());
	ss.str("");
	pose->LinkEndChild(pose_text);
	include->LinkEndChild(pose);

	TiXmlElement * name = new TiXmlElement( "name" );
	name->LinkEndChild(new TiXmlText(ResourceHandler::getInstance(resources_file_path).getRobotName()));
	include->LinkEndChild(name);
}

void GazeboEnvironmentGenerator::genEnvFromSFV(SFVComponent* sfvComp,std::string filename, std::string resources_file_path)
{
	//load terrain
	std::string terrain=ResourceHandler::getInstance(resources_file_path).getTerrainById(sfvComp->getTerrains()->at(0)->getTerrainId());
	std::string path = ResourceHandler::getInstance(resources_file_path).getWorldModelsFolderURL();

	m_terrainAnalyzer->loadFile(path+"/"+terrain);

	TiXmlDocument doc(filename);
	TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild(decl);
	TiXmlElement * element = new TiXmlElement( "sdf" );
	element->SetAttribute("version","1.4");
	doc.LinkEndChild(element);
	TiXmlElement * world = new TiXmlElement( "world" );
	world->SetAttribute("name","default");
	element->LinkEndChild(world);


	// addition of sunlight
	TiXmlElement * include = new TiXmlElement( "include" );
	world->LinkEndChild(include);
	TiXmlElement * uri = new TiXmlElement( "uri" );
	TiXmlText * sun_url = new TiXmlText("model://sun");
	uri->LinkEndChild(sun_url);
	include->LinkEndChild(uri);

	// addition of sky to the environment
	TiXmlElement * scene = new TiXmlElement( "scene" );
	world->LinkEndChild(scene);
	TiXmlElement * sky = new TiXmlElement( "sky" );
	scene->LinkEndChild(sky);

	TiXmlElement * time = new TiXmlElement( "time" );
	sky->LinkEndChild(time);
	TiXmlText * time_value = new TiXmlText("10");
	time->LinkEndChild(time_value);

	// addition of clouds
	TiXmlElement * clouds = new TiXmlElement( "clouds" );
	sky->LinkEndChild(clouds);

	TiXmlElement * speed = new TiXmlElement( "speed" );
	clouds->LinkEndChild(speed);
	TiXmlText * speed_value = new TiXmlText("5");
	speed->LinkEndChild(speed_value);

	TiXmlElement * direction = new TiXmlElement( "direction" );
	clouds->LinkEndChild(direction);
	TiXmlText * direction_value = new TiXmlText("1.14");
	direction->LinkEndChild(direction_value);
	TiXmlElement * humidity = new TiXmlElement( "humidity" );
	clouds->LinkEndChild(humidity);
	TiXmlText * humidity_value = new TiXmlText("0.3");
	humidity->LinkEndChild(humidity_value);


	spawnTerrain( sfvComp->getTerrains()->at(0),world, resources_file_path);

	spawnPlatformPose(sfvComp->m_platformPoses->at(0),world, resources_file_path);


	for(auto objs : *sfvComp->getObjects())
	{
		for(auto obj : *objs->m_objects)
		{
			spawnObject(obj,world,resources_file_path);
		}
	}

	spawnObstacleOnPath(sfvComp, world, resources_file_path);

	spawnPathWpMarks(sfvComp, world);

	doc.SaveFile(filename.c_str());
}

void GazeboEnvironmentGenerator::generate(SFVComponent * sfvComp, std::string scenario_folder_url, std::string resource_file_url)
{
	std::string temp = scenario_folder_url+"/scenarioEnv.world";
	std::cout << "\033[1;36m Producing " << temp << "\033[0m"<< std::endl;

	genEnvFromSFV(sfvComp, temp ,resource_file_url);
}

