#!/usr/bin/env python

import sys
import roslaunch
import rospy

import rospkg

import subprocess

import os
import datetime

import roslib.message
from rosgraph_msgs.msg import Clock

import thread


def wait_duration(duration_seconds = 0.5):
	command_beginning_time = datetime.datetime.now()
	command_duration = datetime.timedelta()
	while ( command_duration.seconds * 1e6 + command_duration.microseconds  <  duration_seconds*1e6 ):
		command_duration = datetime.datetime.now() - command_beginning_time
	#print "command = " , command , " duration = " , command_duration.microseconds	


def run_proc( command , duration_seconds = 0.5):
	proc = subprocess.Popen(command, shell=True , stdin=subprocess.PIPE , stdout=subprocess.PIPE )	
	wait_duration(duration_seconds)
	return proc
	


def run_new_scenario(scenario_index):
	scenario = "scenario_" + str(scenario_index)
	print "runing " + scenario

	rp = rospkg.rospack.RosPack()		
	SRVSS_pkg_path = rp.get_path("SRVSS") 	

	SFDP_file_url = SRVSS_pkg_path + "/SFDP/test.SFDP"
	SFV_file_url = SRVSS_pkg_path + "/SFV" + "/" + scenario + ".SFV"
	scen_folder_url = SRVSS_pkg_path+"/scenarios/" + scenario + "/"
	scen_world_file_url = scen_folder_url+"/env.world" 
	scen_platform_file_url = scen_folder_url+"/platform.sdf" 
	scen_mission_file_url = scen_folder_url+"/myMission.txt" 

	SFV_gen_proc = run_proc("rosrun SRVSS mainGen -gen " + SFDP_file_url + " " + SFV_file_url)
	SFV_gen_proc.terminate()	

	if not os.path.exists(scen_folder_url):
    		os.makedirs(scen_folder_url)

	scen_gen_proc = run_proc("rosrun SRVSS mainGen -run " + SFV_file_url + " " + scen_folder_url)
	scen_gen_proc.terminate()

	roscore_proc = run_proc("roscore")
	print "roscore !!!!"

	gaz_proc = run_proc("gnome-terminal -x rosrun gazebo_ros gazebo") # # roslaunch SRVSS scenario.launch scenario:=" + scenario) # 



def user_input(thread_name):
	#global scenario_terminate_flag
	global user_stop_flag; user_stop_flag = 0		
	while(user_stop_flag == 0):
		str = raw_input("Enter your input: ");
		print "Received input is : ", str
		if (str == "-q"):
			user_stop_flag = 1


import rosnode
def ros_gazebo_terminate():	
	print rosnode.rosnode_listnodes()
	my_nodes = rosnode.get_node_names()
	
	print rosnode.kill_nodes(my_nodes)
	rospy.signal_shutdown("scenario termination")

	wait_duration(3)
	rosnode.rosnode_cleanup()
	
	temp = run_proc("killall mainGen");
	temp = run_proc("killall sh");
	temp = run_proc("killall gazebo");
	temp = run_proc("killall gzclient");
	temp = run_proc("killall gzserver");
	temp = run_proc("killall robot_state_publisher");
	temp = run_proc("killall roslaunch");
	temp = run_proc("killall roscore",2);
	temp = run_proc("killall rosout",2);
	temp = run_proc("killall rosmaster",2);
	
	#rospy.core._shutdown_flag=False
	#rospy.client._init_node_args=None


def gazebo_clock_callback(msg):
	#print "and here 1 !!!"
	global scenario_terminate_flag, gazebo_print_timer
	gazebo_time = msg.clock 
	gazebo_scenario_duration = gazebo_time - rospy.Time()
	if (gazebo_print_timer >= 500):
		print "GAZEBO time :" , gazebo_scenario_duration
		gazebo_print_timer = 0
	else:
		gazebo_print_timer = gazebo_print_timer + 1

	if ( gazebo_scenario_duration > rospy.Duration(10) ):
		scenario_terminate_flag = 1
		#print "GAZEBO : 10 sec have pased killing scenario !!!"
		


def srvss_ros_node_launch():
	print "I AM here !!!"
	
	#rospy.core._shutdown_flag=False
	#rospy.client._init_node_args=None
	#+str(senario_index)
	rospy.init_node('srvss_ros_node', anonymous=False, disable_signals=False)
	
	#wait_duration(5)	
	sub = rospy.Subscriber("/clock", Clock, gazebo_clock_callback)
	

if __name__ == "__main__":
	gazebo_print_timer = 0 

	total_senario_number = 5
	senario_index = 0
	active_scenario_flag = 0

	user_stop_flag = 0
	scenario_terminate_flag = 0
	
	thread.start_new_thread( user_input , ("user_input_thread", ) )
	
	out = 0
	while(out <> 1):
		if (  ((senario_index == total_senario_number) and (active_scenario_flag == 0) )  or  (user_stop_flag == 1)):		
			print "End main loop"
			ros_gazebo_terminate()
			out = 1
		else:
			if (active_scenario_flag == 0):
				
				wait_duration(5)
		
				scenario_terminate_flag = 0
				senario_index = senario_index + 1
				run_new_scenario(senario_index)
				srvss_ros_node_launch()	
				active_scenario_flag = 1

			elif (active_scenario_flag == 1):
				if (scenario_terminate_flag == 1):
					ros_gazebo_terminate()
					active_scenario_flag = 0
				#else:
				#	print "active scenarion is ok !!!"
     

