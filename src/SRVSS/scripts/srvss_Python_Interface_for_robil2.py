#!/usr/bin/env python

import roslib
import roslaunch
from roslaunch.scriptapi import ROSLaunch
from roslaunch.core import Node as ROSNode
import rospy
#from std_srvs.srv import Empty
import std_srvs.srv

import time
import os

import rospkg

roslib.load_manifest("rosparam")
import rosparam

from controller_manager_msgs.srv import *

import subprocess

#import roslib.load_manifest('urdf_parser_py')
#from urdf_parser_py.urdf import URDF

# uri example http://127.0.0.1:11345
class ScenarioLauncher:

    def __init__(self):
	print "I am ScenarioLauncher in python !!"

    def start_launcher(self):
	self.launcher = ROSLaunch()
	self.launcher.start()

    def stop_launcher(self):
	self.launcher.stop()
        time.sleep(10)


    def runGazeboServer(self, Scenarin_folder):
 	arguments = "-u " + Scenarin_folder + "/scenarioEnv.world"     # -u starts the simulation in pause mode
	node = ROSNode("gazebo_ros","gzserver",name="gazebo" ,args=arguments ,output="screen" , respawn="false")      	   # name="gazebo" in order for replay and grader to work (name space)
	self.launcher.launch(node)	
        time.sleep(3)
	return True
	
    def runGazeboClient(self):
	node = ROSNode("gazebo_ros", "gzclient",name="gazebo_client" ,output="screen", respawn="false")
	self.launcher.launch(node)	
        time.sleep(3)
	return True	

    def setScenarioEnv(self,Scenarin_folder):
	rospy.set_param('/use_sim_time',True)	#synchronizing ros to gazebo

	rospack = rospkg.RosPack()
	srvss_pkg_path = rospack.get_path('SRVSS')
	os.environ["GAZEBO_MODEL_PATH"] = srvss_pkg_path+"/world_components_models/:" + Scenarin_folder + "/scenarioSystemModels/"

	bobcat_pkg_path = rospack.get_path('bobcat')
	urdf_file = bobcat_pkg_path +"/urdf/BOBCAT.URDF"
        robot_urdf_file = open(urdf_file)
	robot_urdf = robot_urdf_file.read()
	rospy.set_param("/robot_description", robot_urdf )
	return True


    def launch_platform_controls_spawner(self):
	rospack = rospkg.RosPack()
	bobcat_pkg_path = rospack.get_path('bobcat')
	bobcat_controllers_yaml = bobcat_pkg_path +"/config/bobcat_gazebo_control.yaml"
	paramlist=rosparam.load_file(bobcat_controllers_yaml, default_namespace='' ,verbose=True)
	for params, ns in paramlist:
    		rosparam.upload_params(ns,params)

	# if the controllers do not load it possible to increase the time of waiting for the server in the spawner
	# it located in /home/userws3/gz_ros_cws/src/ros_control/controller_manager/scripts			
	node = ROSNode("controller_manager", "spawner", name="platform_controllers_spawner" ,namespace="/Sahar", output="screen", respawn="false" ,
				args="joint_state_controller \
					back_right_wheel_velocity_controller \
					front_right_wheel_velocity_controller \
					front_left_wheel_velocity_controller \
					back_left_wheel_velocity_controller \
					loader_position_controller \
					supporter_position_controller \
                                        brackets_position_controller")	
	self.launcher.launch(node)	
        time.sleep(10)
	
	node = ROSNode("rate2effort", "rate2effort", name="RateToEffort_node", cwd="node", output="screen") 
	self.launcher.launch(node)	
        time.sleep(3)

    
    def launch_platform_controls_unspawner(self):
	node = ROSNode("controller_manager", "unspawner" ,name="platform_controllers_unspawner" ,namespace="/srvss_bobcat", output="screen", respawn="false" ,
				args="joint_state_controller \
					back_right_wheel_velocity_controller \
					front_right_wheel_velocity_controller \
					front_left_wheel_velocity_controller \
					back_left_wheel_velocity_controller \
					loader_position_controller \
					supporter_position_controller \
                                        brackets_position_controller")	
	self.launcher.launch(node)	
        time.sleep(10)
    

    def launch_WPdriver(self,Scenarin_folder):
	rospack = rospkg.RosPack()
	robil2conf_pkg_path = rospack.get_path('robil2conf')
	robil2conf_yaml = robil2conf_pkg_path +"/configuration.yaml"
	paramlist=rosparam.load_file(robil2conf_yaml, default_namespace='' ,verbose=True)
	for params, ns in paramlist:
    		rosparam.upload_params(ns,params)	

	# == MONITORING == -->
	node = ROSNode("ssm", "ssm_fsm_states_tracker_node",name="ssm_fsm_states_tracker_node",output="screen")
	self.launcher.launch(node)
	node = ROSNode("ssm", "ssm_heartbeat_monitor_node",name="ssm_heartbeat_monitor_node",output="screen")
	self.launcher.launch(node)
	node = ROSNode("ssm", "ssm_node",name="ssm_node",output="screen")
	self.launcher.launch(node)	
	# ================ -->

	# == PERCEPTION == -->
	node = ROSNode("sensors", "sensors_node",name="sensors_node",output="screen")
	self.launcher.launch(node)
	node = ROSNode("iedsim", "iedsim_node",name="iedsim_node",output="screen")
	self.launcher.launch(node)
	node = ROSNode("per", "per_node",name="per_node",output="screen")
	self.launcher.launch(node)
	node = ROSNode("loc", "loc_node",name="loc_node",output="screen")
	self.launcher.launch(node)
	# ================ -->


	# -- MISSION CONTROL  -->
	node = ROSNode("smme", "smme_node",name="smme_node",output="screen")
	self.launcher.launch(node)
	node = ROSNode("wsm", "wsm_node",name="wsm_node",output="screen")
	self.launcher.launch(node)
	node = ROSNode("ocu", "ocu_node",name="ocu_node",output="screen")
	self.launcher.launch(node)
	# ================ -->


	#-- == NAVIGATION == -->
	node = ROSNode("smme", "smme_node",name="smme_node",output="screen")
	self.launcher.launch(node)


	<include file="$(find pp)/launch/navigation.launch" />
	<node name="llc_node" type="llc_node" pkg="llc" output="screen"/>
	<!-- ================ -->


	os.system("roslaunch robil2conf frameworkInit.launch")
	#arguments = "-file " + Scenarin_folder + "/scenarioMission.txt"
	#node = ROSNode("srvss_wp_driver", "srvss_wp_driver_node",name="srvss_wp_driver_node", args=arguments , respawn="false") # output="screen"
	#self.launcher.launch(node)	
        #time.sleep(3)


    def launch_robot_tf_broadcaster(self):
	remaping = [ ("/joint_states" , "/Sahar/joint_states") ] 
	node = ROSNode("robot_state_publisher", "robot_state_publisher",name="robot_state_broadcaster_node", remap_args=remaping ,output="screen", respawn="false")
	self.launcher.launch(node)
        time.sleep(3)	
	
	node = ROSNode("tf", "static_transform_publisher",name="sick_link_tf_broadcaster_node", args="1 0 0.2 0 0 0 body front_sick 100" ,output="screen", respawn="false")
	self.launcher.launch(node)	
        time.sleep(3)


    def launch_recorder(self, Scenarin_folder):
	arguments = "-a -O " + Scenarin_folder + "/scen_rec.bag"
	node = ROSNode("rosbag", "record", name="rosbag_recorde_node", args=arguments)
	self.launcher.launch(node)
        time.sleep(3)	


    def launch_grader(self):
	node = ROSNode("SRVSS", "grader_node", name="grader_node", output="screen")
	self.launcher.launch(node)
        time.sleep(3)	



    def Gazebo_UnPause(self):
	name = '/gazebo/unpause_physics'
	msg_class = std_srvs.srv.Empty()
	print "wait for service " + name
     	rospy.wait_for_service(name)
        print "done wating"
        try:
            service = rospy.ServiceProxy(name, msg_class)
            resp1 = service()
            return True
        except rospy.ServiceException, e:
            print "Service call failed: %s"%e
        return True



    def Gazebo_UnPause(self):
	name = '/gazebo/unpause_physics'
	msg_class = std_srvs.srv.Empty()
	print "wait for service " + name
     	rospy.wait_for_service(name)
        print "done wating"
        try:
            service = rospy.ServiceProxy(name, msg_class)
            resp1 = service()
            return True
        except rospy.ServiceException, e:
            print "Service call failed: %s"%e
        return True



















