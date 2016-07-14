#ifndef _VELODYNE_PLUGIN_HH_
#define _VELODYNE_PLUGIN_HH_

#include <gazebo/gazebo.hh>
#include "gazebo/sensors/sensors.hh"

#include "gazebo/common/Plugin.hh"
#include "gazebo/sensors/SensorTypes.hh"
#include "gazebo/sensors/RaySensor.hh"
#include "gazebo/sensors/sensors.hh"
#include "gazebo/gazebo.hh"
#include "gazebo/physics/physics.hh"
#include "gazebo/physics/Joint.hh"
#include <ros/ros.h>
#include "sensor_msgs/PointCloud.h"
#include "geometry_msgs/Point32.h"
#include <boost/thread.hpp>

#include <math.h>

#define NUM_OF_PLANS 32
#define NUM_OF_RAYS 10
using namespace std;

namespace gazebo
{
  /// \brief A plugin to control a Velodyne sensor.
  class velodyne : public ModelPlugin
  {
    /// \brief Constructor
    public:
	velodyne() {}



	void thread_RVIZ()
	{
		ros::Time lastUpdateTime = ros::Time::now();
		while(true)
		{
			ros::Time newRosTime = ros::Time::now();
			double diff = newRosTime.toSec() - lastUpdateTime.toSec() - RVIZPublishRate;
			if(diff > 0.0001)
			{
				RVIZ_Publisher();
				lastUpdateTime = newRosTime;
			}
		}
	}

     void OnUpdate(const common::UpdateInfo & _info)
     {
    	double dgree = fmod(joint->GetAngle(0).Degree(),360.0);

		double diff = dgree - lastDegree;
		if (diff < 0)
			diff = diff+360;

		if ((diff - angleRes) > 0.000001)
		{
			int tick = (int)(dgree);
			lastDegree = dgree;

			getRanges(tick);
		}
     }

     void initSensors(string modelName)
     {
   	  sensors::SensorPtr ray1, ray2, ray3, ray4, ray5, ray6, ray7, ray8, ray9, ray10;
   	  ray1 = sensors::SensorManager::Instance()->GetSensor("velodyne_ray");
   	  ray2 = sensors::SensorManager::Instance()->GetSensor("velodyne_ray_2");
   	  ray3 = sensors::SensorManager::Instance()->GetSensor("velodyne_ray_3");
   	  ray4 = sensors::SensorManager::Instance()->GetSensor("velodyne_ray_4");
   	  ray5 = sensors::SensorManager::Instance()->GetSensor("velodyne_ray_5");
   	  ray6 = sensors::SensorManager::Instance()->GetSensor("velodyne_ray_6");
   	  ray7 = sensors::SensorManager::Instance()->GetSensor("velodyne_ray_7");
   	  ray8 = sensors::SensorManager::Instance()->GetSensor("velodyne_ray_8");
   	  ray9 = sensors::SensorManager::Instance()->GetSensor("velodyne_ray_9");
   	  ray10 = sensors::SensorManager::Instance()->GetSensor("velodyne_ray_10");
   	  if(!ray1 || !ray2 || !ray3 || !ray4 || !ray5 || !ray6 || !ray7 || !ray8 || !ray9 || !ray10)
      {
   		std::string error = "velodyne Sensor Model \"" + modelName + "\" failed to locate his sub-sensor.\n(Do the names in the .sdf match the names in the .cpp?)\n";
   		gzthrow(error);
   		return;
      }
   	  myRay_1 = boost::dynamic_pointer_cast<sensors::RaySensor>(ray1);
   	  myRay_2 = boost::dynamic_pointer_cast<sensors::RaySensor>(ray2);
   	  myRay_3 = boost::dynamic_pointer_cast<sensors::RaySensor>(ray3);
   	  myRay_4 = boost::dynamic_pointer_cast<sensors::RaySensor>(ray4);
   	  myRay_5 = boost::dynamic_pointer_cast<sensors::RaySensor>(ray5);
   	  myRay_6 = boost::dynamic_pointer_cast<sensors::RaySensor>(ray6);
   	  myRay_7 = boost::dynamic_pointer_cast<sensors::RaySensor>(ray7);
   	  myRay_8 = boost::dynamic_pointer_cast<sensors::RaySensor>(ray8);
   	  myRay_9 = boost::dynamic_pointer_cast<sensors::RaySensor>(ray9);
   	  myRay_10 = boost::dynamic_pointer_cast<sensors::RaySensor>(ray10);

   	  if(!myRay_1 || !myRay_2 || !myRay_3 || !myRay_4 || !myRay_5 || !myRay_6 || !myRay_7 || !myRay_8 || !myRay_9 || !myRay_10)
   	  {
   		std::string error = "velodyne Sensor Model \"" + modelName + "\" found that it's sensor arent of class RaySensor. You must be really messed up\n";
   		gzthrow(error);
   		return;
      }

   	  VerticalAngelResolutionReal[0] = (myRay_1->GetAngleResolution() * 180 / M_PI);
   	  if((int)(VerticalAngelResolutionReal[0] * 100) != (int)(verticalAngleResolutionFromSDF * 100))
   		  ROS_WARN("velodyne: the parameter 'verticalAngleResolution' is not equal to GetAngleResolution() in Ray_1");
   	  VerticalAngelResolutionReal[1] = (myRay_2->GetAngleResolution() * 180 / M_PI);
   	  if((int)(VerticalAngelResolutionReal[1] * 100) != (int)(verticalAngleResolutionFromSDF * 100))
   		  ROS_WARN("velodyne: the parameter 'verticalAngleResolution' is not equal to GetAngleResolution() in Ray_2");
   	  VerticalAngelResolutionReal[2] = (myRay_3->GetAngleResolution() * 180 / M_PI);
   	  if((int)(VerticalAngelResolutionReal[2] * 100) != (int)(verticalAngleResolutionFromSDF * 100))
   		  ROS_WARN("velodyne: the parameter 'verticalAngleResolution' is not equal to GetAngleResolution() in Ray_3");
   	  VerticalAngelResolutionReal[3] = (myRay_4->GetAngleResolution() * 180 / M_PI);
   	  if((int)(VerticalAngelResolutionReal[3] * 100) != (int)(verticalAngleResolutionFromSDF * 100))
   		  ROS_WARN("velodyne: the parameter 'verticalAngleResolution' is not equal to GetAngleResolution() in Ray_4");
   	  VerticalAngelResolutionReal[4] = (myRay_5->GetAngleResolution() * 180 / M_PI);
   	  if((int)(VerticalAngelResolutionReal[4] * 100) != (int)(verticalAngleResolutionFromSDF * 100))
   		  ROS_WARN("velodyne: the parameter 'verticalAngleResolution' is not equal to GetAngleResolution() in Ray_5");
   	  VerticalAngelResolutionReal[5] = (myRay_6->GetAngleResolution() * 180 / M_PI);
   	  if((int)(VerticalAngelResolutionReal[5] * 100) != (int)(verticalAngleResolutionFromSDF * 100))
   		  ROS_WARN("velodyne: the parameter 'verticalAngleResolution' is not equal to GetAngleResolution() in Ray_6");
   	  VerticalAngelResolutionReal[6] = (myRay_7->GetAngleResolution() * 180 / M_PI);
   	  if((int)(VerticalAngelResolutionReal[6] * 100) != (int)(verticalAngleResolutionFromSDF * 100))
   		  ROS_WARN("velodyne: the parameter 'verticalAngleResolution' is not equal to GetAngleResolution() in Ray_7");
   	  VerticalAngelResolutionReal[7] = (myRay_8->GetAngleResolution() * 180 / M_PI);
   	  if((int)(VerticalAngelResolutionReal[7] * 100) != (int)(verticalAngleResolutionFromSDF * 100))
   		  ROS_WARN("velodyne: the parameter 'verticalAngleResolution' is not equal to GetAngleResolution() in Ray_8");
   	  VerticalAngelResolutionReal[8] = (myRay_9->GetAngleResolution() * 180 / M_PI);
   	  if((int)(VerticalAngelResolutionReal[8] * 100) != (int)(verticalAngleResolutionFromSDF * 100))
   		  ROS_WARN("velodyne: the parameter 'verticalAngleResolution' is not equal to GetAngleResolution() in Ray_9");
   	  VerticalAngelResolutionReal[9] = (myRay_10->GetAngleResolution() * 180 / M_PI);
   	  if((int)(VerticalAngelResolutionReal[9] * 100) != (int)(verticalAngleResolutionFromSDF * 100))
   		  ROS_WARN("velodyne: the parameter 'verticalAngleResolution' is not equal to GetAngleResolution() in Ray_10");

     }

    //getRanges
    void getRanges(int tick)
    {
    	std::vector<double> ranges_1, ranges_2, ranges_3, ranges_4, ranges_5, ranges_6, ranges_7, ranges_8, ranges_9, ranges_10;

    	myRay_1->GetRanges(ranges_1);
        myRay_2->GetRanges(ranges_2);
        myRay_3->GetRanges(ranges_3);
        myRay_4->GetRanges(ranges_4);
        myRay_5->GetRanges(ranges_5);
        myRay_6->GetRanges(ranges_6);
        myRay_7->GetRanges(ranges_7);
        myRay_8->GetRanges(ranges_8);
        myRay_9->GetRanges(ranges_9);
        myRay_10->GetRanges(ranges_10);

        if(ranges_1.size() == NUM_OF_PLANS && ranges_2.size() == NUM_OF_PLANS && ranges_3.size() == NUM_OF_PLANS && ranges_4.size() == NUM_OF_PLANS && ranges_5.size() == NUM_OF_PLANS && ranges_6.size() == NUM_OF_PLANS &&
        		ranges_7.size() == NUM_OF_PLANS && ranges_8.size() == NUM_OF_PLANS && ranges_9.size() == NUM_OF_PLANS && ranges_10.size() == NUM_OF_PLANS)
        {
        	int i0 = fmod(tick + 0*36,360);
        	int i1 = fmod(tick + 1*36,360);
        	int i2 = fmod(tick + 2*36,360);
        	int i3 = fmod(tick + 3*36,360);
        	int i4 = fmod(tick + 4*36,360);
        	int i5 = fmod(tick + 5*36,360);
        	int i6 = fmod(tick + 6*36,360);
        	int i7 = fmod(tick + 7*36,360);
        	int i8 = fmod(tick + 8*36,360);
        	int i9 = fmod(tick + 9*36,360);
        	for(int i = 0 ; i < NUM_OF_PLANS ; i++)
        	{
				rangesArray[i0][i] = ranges_1[i];
				rangesArray[i1][i] = ranges_2[i];
				rangesArray[i2][i] = ranges_3[i];
				rangesArray[i3][i] = ranges_4[i];
				rangesArray[i4][i] = ranges_5[i];
				rangesArray[i5][i] = ranges_6[i];
				rangesArray[i6][i] = ranges_7[i];
				rangesArray[i7][i] = ranges_8[i];
				rangesArray[i8][i] = ranges_9[i];
				rangesArray[i9][i] = ranges_10[i];
        	}
        }
    }

	/// \brief The load function is called by Gazebo when the plugin is
	/// inserted into simulation
	/// \param[in] _model A pointer to the model that this plugin is
	/// attached to.
	/// \param[in] _sdf A pointer to the plugin's SDF element.
	virtual void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf)
	{
	// Safety check
	  if (_model->GetJointCount() == 0)
	  {
	    std::cerr << "Invalid joint count, Velodyne plugin not loaded\n";
	    return;
	  }

	  // Store the model pointer for convenience.
	  this->model = _model;

  	  // Get the joint.
	  std::string jointName = "velodyne::velodyne_joint";
	  if (_sdf->HasElement("jointName"))
	  {
	  	   _sdf->GetElement("jointName")->GetValue()->Get<std::string>(jointName);
	  }
	  this->joint = _model->GetJoint(jointName);

	  // Setup a P-controller, with a gain of 0.1.
	  this->pid = common::PID(0.1, 0, 0);

 	  // Apply the P-controller to the joint.
 	  this->model->GetJointController()->SetVelocityPID(this->joint->GetScopedName(), this->pid);

	  // Set the joint's target velocity. This target velocity is just
	  // for demonstration purposes.
	  this->model->GetJointController()->SetVelocityTarget(this->joint->GetScopedName(), 10.0);


	  // set the angle resolution, default is 0.2 deg
	  angleRes = 0.2;
	  if (_sdf->HasElement("angleRes"))
		  angleRes = _sdf->Get<double>("angleRes");

	  //RVIZ Publish Rate, default is 1HZ
	  RVIZPublishRate = 1.0;
	  if (_sdf->HasElement("RVIZPublishRate"))
		  RVIZPublishRate = _sdf->Get<double>("RVIZPublishRate");

	  // get the 'verticalAngleResolutionFromSDF' parameter
	  // using for validate the user, compare this veriable and real vertical angle (VerticalAngelResolutionReal[])
	  verticalAngleResolutionFromSDF = 0;
   	  if (_sdf->HasElement("verticalAngleResolution"))
   		  verticalAngleResolutionFromSDF = _sdf->Get<double>("verticalAngleResolution");
   	  else
   		  ROS_WARN("velodyne: there is no 'verticalAngleResolution' parameter in the SDF (validation parameter)");

	  // Default to 1HZ velocity
	  rate = 10.0;
	  // Check that the velocity element exists, then read the value
	  if (_sdf->HasElement("rate"))
	  {
		  rate = _sdf->Get<double>("rate");
	  }

	  //set the velocity
	  velocity =  (rate / NUM_OF_RAYS) * 2 * M_PI; //depend on rate

	  // Set the joint's target velocity. This target velocity is just
   	  // for demonstration purposes.
   	  this->model->GetJointController()->SetVelocityTarget(this->joint->GetScopedName(), velocity);

   	  //set the topic
	  std::string topic = "/SENSORS/VELODYNE";
	  if (_sdf->HasElement("topic"))
	  {
	  	   _sdf->GetElement("topic")->GetValue()->Get<std::string>(topic);
	  }
   	  _marker_pub = _nodeHandle.advertise<sensor_msgs::PointCloud>(topic, 10);

	  initSensors(_model->GetName());

	  lastDegree = -1;
	  _threadRVIZ=boost::thread(&velodyne::thread_RVIZ,this);
	  this->_updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&velodyne::OnUpdate, this, _1));
	}

	void RVIZ_Publisher()
	{
		sensor_msgs::PointCloud points;
		for(int i = 0 ; i < 360 ; i++)
		{
			for(int j = 0 ; j < NUM_OF_PLANS ; j++)
			{
				geometry_msgs::Point32 point;
				double yaw_ang = i * (3.14159 /180);
				double pitch_ang((j-23) * verticalAngleResolutionFromSDF * (3.14159 /180));
				point.x = rangesArray[i][j] * cos(pitch_ang) * cos(yaw_ang);
				point.y = rangesArray[i][j] * cos(pitch_ang) * sin(yaw_ang);
				point.z	= rangesArray[i][j] * sin (pitch_ang);
				points.points.insert(points.points.begin(), point);
			}
		}
		points.header.stamp = ros::Time();
		points.header.frame_id = "map";

		_marker_pub.publish(points);
	}

    physics::ModelPtr model;
    physics::JointPtr joint;
    //boost::shared_ptr<physics::Joint> joint;
    common::PID pid;

    gazebo::sensors::RaySensorPtr myRay_1;
    gazebo::sensors::RaySensorPtr myRay_2;
    gazebo::sensors::RaySensorPtr myRay_3;
    gazebo::sensors::RaySensorPtr myRay_4;
    gazebo::sensors::RaySensorPtr myRay_5;
    gazebo::sensors::RaySensorPtr myRay_6;
    gazebo::sensors::RaySensorPtr myRay_7;
    gazebo::sensors::RaySensorPtr myRay_8;
    gazebo::sensors::RaySensorPtr myRay_9;
    gazebo::sensors::RaySensorPtr myRay_10;

    event::ConnectionPtr 		_updateConnection; // Pointer to the update event connection
    common::Time			sim_Time;

    double lastDegree;
	double angleRes;
	double velocity;
	double rate;
    double rangesArray[360][NUM_OF_PLANS];
    double RVIZPublishRate;
    double verticalAngleResolutionFromSDF;
    double VerticalAngelResolutionReal[10];
    ros::Publisher _marker_pub;
    ros::NodeHandle		_nodeHandle;

    boost::thread _threadRVIZ;

  };

  // Tell Gazebo about this plugin, so that Gazebo can call Load on this plugin.
  GZ_REGISTER_MODEL_PLUGIN(velodyne)
}
#endif
