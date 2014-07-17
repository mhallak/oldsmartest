cmake_minimum_required(VERSION 2.8.3)
project(SRVSS)

SET(CMAKE_CXX_FLAGS "-std=c++0x")

find_package(catkin REQUIRED COMPONENTS
  cmake_modules
  roscpp
  rospy
  std_msgs
  rosbag
  robil_msgs 
  gazebo_msgs
)

find_package(Boost REQUIRED COMPONENTS system thread filesystem)

find_package(TinyXML REQUIRED)

find_package(OpenCV REQUIRED)
                            
find_package(Gazebo REQUIRED)


catkin_package(
    #LIBRARIES  
    INCLUDE_DIRS
      include
    DEPENDS
      TinyXML
  CATKIN_DEPENDS      
      message_runtime 
      robil_msgs 
)

                                                                                                                                                 
include_directories(include ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS} ${TinyXML_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} /usr/include/sdformat-1.4)



add_library(NumberSampler src/utils/NumberSampler.cpp)






#############
#### DP #####
#############
add_library(DPGroup src/SFV/DPGroup.cpp)
add_library(DPObject src/SFV/DPObject.cpp)

target_link_libraries(DPObject ${catkin_LIBRARIES}
NumberSampler
)
target_link_libraries(DPGroup ${catkin_LIBRARIES}
DPObject
)

##############
## RESOURCE ##
##############
add_library(ResourceHandler src/Resource/ResourceHandler.cpp)
target_link_libraries(ResourceHandler ${catkin_LIBRARIES} ${TinyXML_LIBRARIES})

add_library(TerrainAnalyzer src/Generators/Gazebo/TerrainAnalyzer.cpp)
target_link_libraries(TerrainAnalyzer ${catkin_LIBRARIES} ${OpenCV_LIBS})


#############
#### RULES ##
#############
add_library(RULE_wp_path_inside_map src/Rules/RULE_wp_path_inside_map.cpp)
target_link_libraries(RULE_wp_path_inside_map ${catkin_LIBRARIES}
TerrainAnalyzer ResourceHandler
)

add_library(RULE_platform_init_pose_with_no_obj_colisions src/Rules/RULE_platform_init_pose_with_no_obj_colisions.cpp)
target_link_libraries(RULE_platform_init_pose_with_no_obj_colisions ${catkin_LIBRARIES}
TerrainAnalyzer ResourceHandler
)
#############
#### SFV ####
#############

add_library(SFVBase src/SFV/SFVBase.cpp)
add_library(SFVGeneric src/SFV/SFVGeneric.cpp)
add_library(SFVObject src/SFV/SFVObject.cpp)
add_library(SFVObstacleOnPath src/SFV/SFVObstacleOnPath.cpp)
add_library(SFVLight src/SFV/SFVLight.cpp)
add_library(SFVTerrain src/SFV/SFVTerrain.cpp)
add_library(SFVFrictionLink src/SFV/SFVFrictionLink.cpp)
add_library(SFVSensorLink src/SFV/SFVSensorLink.cpp)
add_library(SFVMassLink src/SFV/SFVMassLink.cpp)
add_library(SFVPlatformPose src/SFV/SFVPlatformPose.cpp)
add_library(SFVWaypoint src/SFV/SFVWaypoint.cpp)

add_library(SFVPath src/SFV/SFVPath.cpp)
add_library(SFVComponent src/SFV/SFVComponent.cpp)

target_link_libraries(SFVBase ${catkin_LIBRARIES}
DPGroup
)

target_link_libraries(SFVGeneric ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
SFVGeneric
)

target_link_libraries(SFVObject ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
SFVBase
)

target_link_libraries(SFVObstacleOnPath ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
SFVBase
)

target_link_libraries(SFVLight ${catkin_LIBRARIES}
SFVBase
)
target_link_libraries(SFVTerrain ${catkin_LIBRARIES}
SFVBase
)
target_link_libraries(SFVFrictionLink ${catkin_LIBRARIES}
SFVBase
)
target_link_libraries(SFVSensorLink ${catkin_LIBRARIES}
SFVBase
)
target_link_libraries(SFVMassLink ${catkin_LIBRARIES}
SFVBase
)
target_link_libraries(SFVPlatformPose ${catkin_LIBRARIES}
SFVBase
)
target_link_libraries(SFVWaypoint ${catkin_LIBRARIES}
SFVBase
)

target_link_libraries(SFVPath ${catkin_LIBRARIES}
SFVWaypoint
SFVGeneric
)

target_link_libraries(SFVComponent ${catkin_LIBRARIES}
SFVLight
SFVObject
SFVObstacleOnPath
SFVTerrain
SFVFrictionLink
SFVSensorLink
SFVMassLink
SFVPlatformPose
SFVWaypoint
SFVGeneric
SFVPath
DPGroup

RULE_wp_path_inside_map
RULE_platform_init_pose_with_no_obj_colisions
)


#############
### SFDP ####
#############
add_library(ScenarioFeatureGroup src/SFDP/ScenarioFeatureGroup.cpp)
add_library(ScenarioFeature src/SFDP/ScenarioFeature.cpp)

target_link_libraries(ScenarioFeature ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
)


target_link_libraries(ScenarioFeatureGroup  ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
ScenarioFeature
)


add_library(SFDPComponent src/SFDP/SFDPComponent.cpp)
target_link_libraries(SFDPComponent ${catkin_LIBRARIES}
ScenarioFeatureGroup
ScenarioFeature
SFVComponent
)

add_library(SFDPobj src/SFDP/SFDPobj.cpp)
target_link_libraries(SFDPobj ${catkin_LIBRARIES} ${Boost_INCLUDE_DIR}
ScenarioFeatureGroup
ScenarioFeature
SFVComponent
GazeboExecutor
)


add_library(SFDPParser src/SFDP/SFDPParser.cpp)
target_link_libraries(SFDPParser ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
SFDPComponent
ScenarioFeatureGroup
)



##############
# GENERATORS #
##############


add_library(GazeboEnvironmentGenerator src/Generators/Gazebo/GazeboEnvironmentGenerator.cpp)
target_link_libraries(GazeboEnvironmentGenerator ${catkin_LIBRARIES}
ResourceHandler
TerrainAnalyzer
)

add_library(GazeboMissionGenerator src/Generators/Gazebo/GazeboMissionGenerator.cpp)
target_link_libraries(GazeboMissionGenerator ${catkin_LIBRARIES}
ResourceHandler
TerrainAnalyzer
)

add_library(GazeboPlatformGenerator src/Generators/Gazebo/GazeboPlatformGenerator.cpp)
target_link_libraries(GazeboPlatformGenerator ${catkin_LIBRARIES}
ResourceHandler
/usr/lib/libsdformat.so
)


add_library(GazeboScenarioGenerator src/Generators/Gazebo/GazeboScenarioGenerator.cpp)
target_link_libraries(GazeboScenarioGenerator ${catkin_LIBRARIES}
GazeboEnvironmentGenerator
GazeboMissionGenerator
GazeboPlatformGenerator
)



################
# synchronizer #
################
add_library(Executor src/Executor.cpp)

add_library(SRVSSSyncronizer src/SRVSSSyncronizer.cpp)
target_link_libraries(GazeboPlatformGenerator ${catkin_LIBRARIES}
ResourceHandler
Executor
)

############
# Executor #
############
add_library(GazeboExecutor src/Executor/GazeboExecutor.cpp)
target_link_libraries(GazeboExecutor ${catkin_LIBRARIES}
)


#############
#### MAIN ###
#############
add_executable(mainGen src/Main.cpp)
target_link_libraries(mainGen ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
SFVComponent
SFDPobj
SFDPParser
SFDPobj
GazeboScenarioGenerator
)



######################
#### Sampling Algo ###
######################
add_executable(SamplingAlgo src/SamplingAlgo.cpp)
target_link_libraries(SamplingAlgo ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
SFVComponent
SFDPobj
SFDPParser
GazeboScenarioGenerator
)



######################
#### Replay Player ###
######################
add_executable(ReplayPlayer src/ReplayPlayer/ReplayPlayer.cpp)
target_link_libraries(ReplayPlayer ${catkin_LIBRARIES} ${GAZEBO_INCLUDE_DIRS}
)



###############
#### grader ###
###############
# add_executable(grader_node src/Grader/grader_node.cpp)
# target_link_libraries(grader_node
#   ${catkin_LIBRARIES}
#)

