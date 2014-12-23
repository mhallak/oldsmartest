#include <iostream>
#include <cmath>      // std::abs()
#include <string>
#include <map>
#include <vector>

#include "ros/ros.h"
#include "std_msgs/Float32MultiArray.h"
#include "std_msgs/Bool.h"

#include "tf/transform_listener.h"
#include "tf/LinearMath/Matrix3x3.h"
#include "tf/LinearMath/Quaternion.h"

#include "fcl/distance.h"
#include "fcl/traversal/traversal_node_bvhs.h"

#include <sdformat-1.4/sdf/sdf.hh>

#include "SFV/SFV.h"
#include "SFV/SFVobjScattering.h"
#include "SFV/SFVobsOnPathScattering.h"
#include "Resource/ResourceHandler.h"

using namespace fcl;


#define PI 3.14159265359
#define MIN_ALLOWED_OBS_DIST 2
#define MAX_ALLOWED_ROLL_ANG (15*PI/180)
#define MAX_ALLOWED_PITCH_ANG (30*PI/180)

float scenario_obj_min_dist = 100;
float scenario_roll_max_ang = 0;
float scenario_pitch_max_ang = 0;




/**
 *   utility function for loading *.obj file to fcl Vertices and Triangles
 */
void loadOBJFile(const char* filename, std::vector<Vec3f>& points, std::vector<Triangle>& triangles)
{

  FILE* file = fopen(filename, "rb");
  if(!file)
  {
    std::cerr << "file not exist" << std::endl;
    return;
  }

  bool has_normal = false;
  bool has_texture = false;
  char line_buffer[2000];
  while(fgets(line_buffer, 2000, file))
  {
    char* first_token = strtok(line_buffer, "\r\n\t ");
    if(!first_token || first_token[0] == '#' || first_token[0] == 0)
      continue;

    switch(first_token[0])
    {
    case 'v':
      {
        if(first_token[1] == 'n')
        {
          strtok(NULL, "\t ");
          strtok(NULL, "\t ");
          strtok(NULL, "\t ");
          has_normal = true;
        }
        else if(first_token[1] == 't')
        {
          strtok(NULL, "\t ");
          strtok(NULL, "\t ");
          has_texture = true;
        }
        else
        {
          FCL_REAL x = (FCL_REAL)atof(strtok(NULL, "\t "));
          FCL_REAL y = (FCL_REAL)atof(strtok(NULL, "\t "));
          FCL_REAL z = (FCL_REAL)atof(strtok(NULL, "\t "));
          Vec3f p(x, y, z);
          points.push_back(p);
        }
      }
      break;
    case 'f':
      {
        Triangle tri;
        char* data[30];
        int n = 0;
        while((data[n] = strtok(NULL, "\t \r\n")) != NULL)
        {
          if(strlen(data[n]))
            n++;
        }

        for(int t = 0; t < (n - 2); ++t)
        {
          if((!has_texture) && (!has_normal))
          {
            tri[0] = atoi(data[0]) - 1;
            tri[1] = atoi(data[1]) - 1;
            tri[2] = atoi(data[2]) - 1;
          }
          else
          {
            const char *v1;
            for(int i = 0; i < 3; i++)
            {
              // vertex ID
              if(i == 0)
                v1 = data[0];
              else
                v1 = data[t + i];

              tri[i] = atoi(v1) - 1;
            }
          }
          triangles.push_back(tri);
        }
      }
      break;
    }
  }
}

/**
 *   utility function for creating fcl Quanterion from Roll, Pitch and Yaw
 */
Quaternion3f Quanterion3f_from_RPY(float Roll,float Pitch,float Yaw)
{
	tf::Matrix3x3 obs_mat;
	obs_mat.setEulerYPR(Yaw,Pitch,Roll);

	tf::Quaternion q_tf;
	obs_mat.getRotation(q_tf);

	Quaternion3f q(q_tf.getW(),q_tf.getX(),q_tf.getY(),q_tf.getZ());
	return(q);
}





// Global Variabled used by Grading function
std::map<std::string ,BVHModel<RSS> *> * obs_models_map;
std::map<std::string ,BVHModel<RSS> *> * robot_models_map;
SFV *sfv;
tf::TransformListener *listener_ptr;
boost::mutex collision_mutex;
boost::mutex tf_data_mutex;
/**
 * Grading function for collision detection
 */
void collision_grader(const ros::TimerEvent&)
{
    float min_dist = 100;

    std::string part_name;
    BVHModel<RSS> * part_model;

	for (std::map<std::string ,BVHModel<RSS> *>::iterator RobotPart_it=robot_models_map->begin(); RobotPart_it!=robot_models_map->end(); ++RobotPart_it)
	{
    	part_name = RobotPart_it->first;
		part_model = RobotPart_it->second;

		Vec3f part_p(0,0,0);
		Quaternion3f part_q;
		Transform3f part_pose;

		tf::StampedTransform part_transform;
		try {
		   listener_ptr->waitForTransform("/world", part_name, ros::Time(0), ros::Duration(1) );
		   listener_ptr->lookupTransform("/world", part_name ,ros::Time(0), part_transform);

		   part_p.setValue(part_transform.getOrigin().x(),part_transform.getOrigin().y(),part_transform.getOrigin().z());
		   part_q = Quaternion3f(part_transform.getRotation().w(),part_transform.getRotation().x(),part_transform.getRotation().y(),part_transform.getRotation().z());
		   part_pose.setTransform(part_q,part_p);
		     }
		   catch (tf::LookupException &ex)
		      {
		   	ROS_ERROR("%s",ex.what());
		   	continue;
		   	// return;
		      }
		   	    std::vector<SFVobsOnPathScattering*> *obsOnPathScatterings_vec = new std::vector<SFVobsOnPathScattering*>;
		   	   	sfv->get_VecOfSubGroupsByFeatureGroupType(ScenarioFeatureGroupType::obstacles_on_path, (std::vector<sfvSubGroup*> *)obsOnPathScatterings_vec);
				for (SFVobsOnPathScattering *obsScattering_it : *obsOnPathScatterings_vec )
				{

					for (SFVObstacleOnPath *obs : *(obsScattering_it->get_ObstaclesOnPath()))
					{

						std::string obs_name = ResourceHandler::getInstance(sfv->get_ResourceFile()).getObjectById(obs->get_ObstacleType()->get_RolledValue());

						float obs_x = obs->get_Obstacle_xyz()->at('x');
						float obs_y = obs->get_Obstacle_xyz()->at('y');
						float obs_z = obs->get_Obstacle_xyz()->at('z');
						Vec3f obs_p(obs_x, obs_y, obs_z);

						Vec3f centers_dist = obs_p - part_p;
						if ( centers_dist.length() > 100 )
						   { continue;	}

						double obs_roll = obs->get_LocationRoll()->get_RolledValue();
						double obs_pitch = obs->get_LocationPitch()->get_RolledValue();
						double obs_yaw = obs->get_LocationYaw()->get_RolledValue();
						Quaternion3f obs_q = Quanterion3f_from_RPY(obs_roll,obs_pitch,obs_yaw);

						Transform3f obs_pose(obs_q,obs_p);

						DistanceResult local_result;
						if ( (robot_models_map->find(part_name)!=robot_models_map->end()) && (obs_models_map->find(obs_name.c_str())!=obs_models_map->end()) )
						{
							distance(robot_models_map->at(part_name),part_pose,obs_models_map->at(obs_name.c_str()),obs_pose,1,local_result);
							if (  min_dist > local_result.min_distance )
								min_dist = local_result.min_distance;
						}
					}
				}


				std::vector<SFVobjScattering*> *objectsOnPathScatterings_vec = new std::vector<SFVobjScattering*>;
		   	   	sfv->get_VecOfSubGroupsByFeatureGroupType(ScenarioFeatureGroupType::objects, (std::vector<sfvSubGroup*> *)objectsOnPathScatterings_vec);
				for (SFVobjScattering* objScattering_it : *objectsOnPathScatterings_vec )
			    {
					for (SFVObject* obj : *(objScattering_it->get_Objects()))
					{
						std::string obj_name = ResourceHandler::getInstance(sfv->get_ResourceFile()).getObjectById(obj->get_ObjectType()->get_RolledValue());

						float obj_x = obj->get_Object_xyz()->at('x');
						float obj_y = obj->get_Object_xyz()->at('y');
						float obj_z = obj->get_Object_xyz()->at('z');
						Vec3f obj_p(obj_x, obj_y, obj_z);

						Vec3f centers_dist = obj_p - part_p;
						if ( centers_dist.length() > 10 )
						   { continue;	}

						double obj_roll = obj->get_LocationRoll()->get_RolledValue();
						double obj_pitch = obj->get_LocationPitch()->get_RolledValue();
						double obj_yaw = obj->get_LocationYaw()->get_RolledValue();
						Quaternion3f obj_q = Quanterion3f_from_RPY(obj_roll,obj_pitch,obj_yaw);

						Transform3f obj_pose(obj_q,obj_p);

						DistanceResult local_result;
						if ( (robot_models_map->find(part_name)!=robot_models_map->end()) && (obs_models_map->find(obj_name.c_str())!=obs_models_map->end()) )
						{
							distance(robot_models_map->at(part_name),part_pose,obs_models_map->at(obj_name.c_str()),obj_pose,1,local_result);
							if (  min_dist > local_result.min_distance )
								min_dist = local_result.min_distance;
						}

					}

				}


	}

		//std::cout << " min dist to  =  " <<  min_dist << std::endl;

		collision_mutex.lock();
			scenario_obj_min_dist = std::min(scenario_obj_min_dist , min_dist);
		collision_mutex.unlock();
}



// variable used by the Grading funtion
boost::mutex rollover_mutex;

/**
 *
 * Grading function for platform stability
 */
void rollover_grader(const ros::TimerEvent&)
{
	Quaternion3f rob_body_q;
	tf::StampedTransform rob_body_transform;

	double roll, pitch, yaw;

	try {
	   listener_ptr->waitForTransform("/world", "body", ros::Time(0), ros::Duration(1.0) );
	   listener_ptr->lookupTransform("/world", "body" ,ros::Time(0), rob_body_transform);
	   //listener_ptr->clear();
	   tf::Matrix3x3 mat( rob_body_transform.getRotation());
	   mat.getRPY(roll, pitch, yaw);
	     }
	   catch (tf::TransformException &ex)
	      {
	   	ROS_ERROR("%s",ex.what());
	   	return;
	      }

	   //std::cout << " roll = " << roll << std::endl;

	rollover_mutex.lock();
		scenario_roll_max_ang = std::max( scenario_roll_max_ang , std::abs((float)roll) );
		scenario_pitch_max_ang = std::max( scenario_pitch_max_ang , std::abs((float)pitch) );
	rollover_mutex.unlock();
}





// grades publishing
std_msgs::Float32MultiArray greads_array;
std_msgs::Bool reset_flag;
ros::Publisher greades_pub_;
ros::Publisher reset_pub_;
void grades_publishing(const ros::TimerEvent&)
{
  	greads_array.data.clear();

	collision_mutex.lock();
	rollover_mutex.lock();

    	greads_array.data.push_back(scenario_obj_min_dist);
  		greads_array.data.push_back(scenario_roll_max_ang);
  		greads_array.data.push_back(scenario_pitch_max_ang);

  		greades_pub_.publish(greads_array);

  		if (  (scenario_obj_min_dist <= MIN_ALLOWED_OBS_DIST)  || ( scenario_roll_max_ang >= MAX_ALLOWED_ROLL_ANG) || (scenario_pitch_max_ang >= MAX_ALLOWED_PITCH_ANG)  )
			{
			reset_flag.data = true;
			//ROS_INFO(" vreset_flag = %d " , reset_flag.data);
			}
		   reset_pub_.publish(reset_flag);

   collision_mutex.unlock();
   rollover_mutex.unlock();
}

/**
 * Loads fcl_models of world objects into a map of <name,world_object_model>
 */
void load_obstacles_models()
{
    obs_models_map = new std::map<std::string ,BVHModel<RSS> *>;
    std::string resours_file = sfv->get_ResourceFile();
    std::string obj_dir_path= ResourceHandler::getInstance(resours_file).getWorldModelsFolderURL();

	   int id=1;
	   while(ResourceHandler::getInstance(resours_file).getObjectById(id) != "")
	   {
		   std::string obj_name = ResourceHandler::getInstance(resours_file).getObjectById(id);
		   std::string obj_path = obj_dir_path + "/" + obj_name + "/models/" + obj_name + ".obj";

		  // std::cout << " obj_path = " << obj_path << std::endl;

		   std::vector<Vec3f> o_ver;
		   std::vector<Triangle> o_tri;
		   loadOBJFile( obj_path.c_str() , o_ver, o_tri);

		   BVHModel<RSS> * obj_model = new BVHModel<RSS>();
		   obj_model->beginModel();
		   obj_model->addSubModel(o_ver, o_tri);
		   obj_model->endModel();

		   std::pair<std::string ,BVHModel<RSS> *> pair_name_obj =  std::pair<std::string ,BVHModel<RSS> *>( obj_name , obj_model);
		   obs_models_map->insert(pair_name_obj);

		   id++;
	   }
}

/**
 * Loads fcl_models of robot parts in to a map of <name,robot_part_model>
 */
void load_robot_models()
{
	robot_models_map = new std::map<std::string ,BVHModel<RSS> *>;

	std::string resours_file = sfv->get_ResourceFile();
	std::string robot_model_folder_url = ResourceHandler::getInstance(resours_file).getRobotModelsFolderURL();
	std::string robot_model_url = robot_model_folder_url + "/" +  ResourceHandler::getInstance(resours_file).getRobotPlatformName() + "/model.sdf";

	//std::cout << "robot_model_url = " << robot_model_url << std::endl;

	sdf::SDFPtr sdfPtr(new sdf::SDF());
	init(sdfPtr);
	sdf::readFile(robot_model_url,sdfPtr);
	sdf::ElementPtr sdfModelPtr=sdfPtr->root->GetElement("model");
	sdf::ElementPtr sdfUriPtr ;
	   for (sdf::ElementPtr sdfLinkPtr=sdfModelPtr->GetElement("link"); sdfLinkPtr ; sdfLinkPtr=sdfLinkPtr->GetNextElement("link"))
	   {
		   for (sdf::ElementPtr sdfCollisionPtr=sdfLinkPtr->GetElement("collision"); sdfCollisionPtr; sdfCollisionPtr=sdfCollisionPtr->GetNextElement("collision"))
		   {
		   sdfUriPtr=sdfCollisionPtr->GetElement("geometry")->GetElement("mesh")->GetElement("uri");
		   std::string part_obj_uri = sdfUriPtr->GetValue()->GetAsString();

		   unsigned found1 = part_obj_uri.find_last_of("/");
		   unsigned found2 = part_obj_uri.find_last_of(".");
		   std::string part_name = part_obj_uri.substr(found1+1,(found2-found1)-1);

		   part_obj_uri = robot_model_folder_url + "/" + part_obj_uri.erase( 0 , 8);
		   part_obj_uri = part_obj_uri.erase(part_obj_uri.length()-3 , part_obj_uri.length() ) + "obj";

		  // std::cout << "part_name = " << part_name << std::endl;

		   std::vector<Vec3f> p_ver;
		   std::vector<Triangle> p_tri;
		   loadOBJFile( part_obj_uri.c_str() , p_ver, p_tri);

		   BVHModel<RSS> * part_model = new BVHModel<RSS>();
		   part_model->beginModel();
		   part_model->addSubModel(p_ver, p_tri);
		   part_model->endModel();

		   std::pair<std::string ,BVHModel<RSS> *> pair_partName_obj =  std::pair<std::string ,BVHModel<RSS> *>( part_name , part_model);
		   robot_models_map->insert(pair_partName_obj);
		   }
	   }
}

void printUsage()
{
	std::cout << "Two variables required SFV_ws_folder and SFV_file_url" << std::endl;
}


int main(int argc, char **argv)
{
	std::cout << " i am in grader !!! " << std::endl;

	/*
	if(argc!=3)
		{
		printUsage();
		return 0;
		}
*/

   ros::init(argc, argv, "greader_node");

   std::string SFV_ws_folder = argv[1];       // "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/scenarios/scenario_1";
   std::string SFV_file_url = argv[2];        // "/home/userws3/dany_ws/src/Simulation/srvss/src/SRVSS/scenarios/scenario_1/test.SFV";
   sfv = new SFV(SFV_file_url,SFV_ws_folder);

   load_obstacles_models();
   load_robot_models();

   ros::NodeHandle n;

   tf::TransformListener listener(ros::Duration(1),true);
   listener_ptr = &listener;

   reset_flag.data = false;

   ros::Timer collision_grader_timer = n.createTimer(ros::Duration(0.05), collision_grader);
   ros::Timer rollover_grader_timer = n.createTimer(ros::Duration(0.05), rollover_grader);
   ros::Timer grades_publishing_timer = n.createTimer(ros::Duration(0.01), grades_publishing);

   greades_pub_ = n.advertise<std_msgs::Float32MultiArray>("/srvss/grades", 100);
   reset_pub_ = n.advertise<std_msgs::Bool>("/srvss/scenario_reset", 100);


   ros::spin();

   return 0;
}

