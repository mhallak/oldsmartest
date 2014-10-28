
import roslib
#import roslaunch
from roslaunch import main as roslaunchMain
from roslaunch.scriptapi import ROSLaunch
from roslaunch.core import Node as ROSNode
from std_srvs.srv import Empty
from gazebo_msgs.srv import DeleteModel, SpawnModel
from gazebo_msgs.msg import ModelStates
import rospy
import time
import os
import threading
import multiprocessing


# uri example http://127.0.0.1:11345
class SimCordinator:

    def __init__(self,gazebo_server_port,ros_server_port,gazebo_host="http://127.0.0.1",ros_host="http://127.0.0.1"):
	print "I am in python !! "
        self.gazebo_host = gazebo_host
        self.ros_host = ros_host
        self.gazebo_server_port = gazebo_server_port
        self.ros_server_port = ros_server_port
        self.ros_core_started = False
        self.gazebo_server_started = False
        self.ros_core_process = None
        self.gazebo_server_process = None
        self.ros_nodes = dict()
        self.spawnModelPublisher=None
        self.deleteModelPublisher=None
        self.upauseSimulationPublisher=None
        self.pauseSimulationPublisher=None
        
    def setEnvironment(self):
       os.environ["GAZEBO_MASTER_URI"] = self.gazebo_host + ":" + self.gazebo_server_port
       os.environ["GAZEBO_MODEL_DATABASE_URI"] ="http://gazebosim.org/models"
       os.environ["GAZEBO_RESOURCE_PATH"] ="/home/userws1/.gazebo/models:/usr/share/gazebo-1.9:/usr/share/gazebo_models"
       os.environ["GAZEBO_PLUGIN_PATH"] ="/usr/lib/gazebo-1.9/plugins/:/opt/ros/hydro/lib/:${GAZEBO_PLUGIN_PATH}"
       os.environ["LD_LIBRARY_PATH"] ="/opt/ros/hydro/lib/:/usr/lib/gazebo-1.9/plugins/:${LD_LIBRARY_PATH}"
       os.environ["ROS_ROOT"] ="/opt/ros/hydro/share/ros"
       os.environ["ROS_MASTER_URI"] = self.ros_host+":"+self.ros_server_port
       os.environ["ROS_DISTRO"] ="hydro"
       os.environ["ROS_ETC_DIR"] ="/opt/ros/hydro/etc/ros"


    def startRosCoreAux(self):
        #roslaunch.main(['roscore', '--core', '--port='+self.ros_server_port])
        roslaunchMain(['roscore', '--core', '--port='+self.ros_server_port])

    def startRosCore(self):
        if self.ros_core_started:
            return False
        self.setEnvironment()
        self.ros_core_started=True
        self.ros_core_process=multiprocessing.Process(target=self.startRosCoreAux)
        self.ros_core_process.start()
        time.sleep(3)
        return True

    def stopRosCore(self):
        self.ros_core_started=False
        self.ros_core_process.terminate()
        return True

    def startGazeboServer(self):
        if self.gazebo_server_started or (not self.ros_core_started):
            return False
        self.gazebo_server_started=True
        self.setEnvironment()
        node =ROSNode("SRVSS", "gazebo_server",name="gazebo",args='/usr/share/gazebo-1.9/worlds/empty.world')
        launch = ROSLaunch()
        launch.start()
        self.gazebo_server_process=launch.launch(node)
        time.sleep(3)
        return True

    def stopGazeboServer(self):
        self.gazebo_server_process.stop()
        self.gazebo_server_started=False
        return True

    def launchGazeboClient(self):
        self.runNode("gzClient","SRVSS", "gazebo_client")

    def runNode(self,name,package,executable,arguments=None):
        if (not self.ros_core_started) or (name in self.ros_nodes):
            return False
        self.setEnvironment()
        node =ROSNode(package, executable,args=arguments)
        launch = ROSLaunch()
        launch.start()
        self.ros_nodes[name]=launch.launch(node)
        time.sleep(3)
        return True

    def killNode(self,name):
        if not name in self.ros_nodes:
            return False
        if self.ros_nodes[name].is_alive():
            self.ros_nodes[name].stop()
        self.ros_nodes.pop(name)
        return True
        
    def killAllNodes(self):
        for name in self.ros_nodes:
            if self.ros_nodes[name].is_alive():
                self.ros_nodes[name].stop()
        return True
    
    
    def serviceFunc(self,name, msg_class,args):
        print "wait for service" + name
        rospy.wait_for_service(name)
        print "done wating"
        try:
            service = rospy.ServiceProxy(name, msg_class)
            resp1 = service(*args)
            return True
        except rospy.ServiceException, e:
            print "Service call failed: %s"%e
                
    def loadEnvFile(self,envfile):
        print "read file"
        f = open(envfile, 'r')

        self.serviceFunc('/gazebo/spawn_sdf_model',SpawnModel,('',f.read(),'',None,None))

        return True
        
    def pauseSimulation(self):
        self.serviceFunc('/gazebo/pause_physics',Empty,tuple(None))
        return True
        
    def unpauseSimulation(self):
        self.serviceFunc('/gazebo/unpause_physics',Empty,tuple(None))
        return True
        
    def resetSimulation(self):
        self.serviceFunc('/gazebo/reset_simulation',Empty,tuple(None))
        return True

    def spawnGazeboObject(self,modelName,sdf):
        self.serviceFunc('/gazebo/spawn_sdf_model',SpawnModel,(modelName,sdf,'',None,None))
        return True

'''
cordList= []
port = 11600
for i in range(0,2):
    cord =SimCordinator(str(port+i),str(port+i+1))
    port=port+i+1
    cord.startRosCore()
    cord.startGazeboServer()
    cord.launchGazeboClient()
    time.sleep(10)
    #cord.loadEnvFile('/home/userws1/Desktop/Robil2/src/Simulation/live_bobcat/worlds/empty.world')
    print 'env loaded'
    #cord.pauseSimulation()
    cordList.append(cord)

time.sleep(200)

for cord in cordList:
    print "kill client"
    cord.killNode("gzClient")
    print "kill server"
    cord.stopGazeboServer()
    print "kill core"
    time.sleep(10)
    cord.stopRosCore() '''
