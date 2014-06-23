/*
 * TerrainBoundsRule.cpp
 *
 *  Created on: Jun 2, 2014
 *      Author: userws1
 */

#include "Rules/TerrainBoundsRule.h"
#include "Resource/ResourceHandler.h"
#include "Generators/Gazebo/TerrainAnalyzer.h"
#include "SFV/SFVComponent.h"
#include "SFV/SFVTerrain.h"
#include <boost/foreach.hpp>

TerrainBoundsRule::TerrainBoundsRule() {
	// TODO Auto-generated constructor stub

}

TerrainBoundsRule::~TerrainBoundsRule() {
	// TODO Auto-generated destructor stub
}


bool TerrainBoundsRule::isRuleValid(SFVComponent *comp)
{
	for(SFVTerrain* terrain :*(comp->getTerrains()))
	{
		//load terrain
		std::string terrain_name=ResourceHandler::getInstance(comp->m_resource_file_path).getTerrainById(terrain->getTerrainId());
		std::string path = ResourceHandler::getInstance(comp->m_resource_file_path).getModelsPath();
		TerrainAnalyzer* terrainA=new TerrainAnalyzer();
		terrainA->loadFile(path+"/"+terrain_name);

		//get terrain bounds
		float xMax,yMax,xMin,yMin,temp;
		terrainA->getXYZCoord(0.95,0.95,xMax,yMax,temp);
		terrainA->getXYZCoord(0.05,0.05,xMin,yMin,temp);

		for(SFVPlatformPose* platformPose : *(comp->getPlatformPoses()))
		{
			for(SFVPath* waypoints:*(comp->getPaths()))
			{
				float x,y,z;
				terrainA->getXYZCoord(platformPose->getLocationX(),platformPose->getLocationY(),x,y,z);
				float azimut = platformPose->getLocationAzimut();

				for(SFVWaypoint* waypoint:*(waypoints->m_objects))
				{
					azimut+=waypoint->getRelativeAngle();
					x+=waypoint->getWpIDistanceI()*cos(azimut);
					y+=waypoint->getWpIDistanceI()*sin(azimut);

					if(x<xMin || y<yMin || x>xMax || y>yMax)
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}
