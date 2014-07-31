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

FIND_PACKAGE(PythonLibs 2.7 REQUIRED)

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

                                                                                                                                                 
include_directories(include ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS} ${TinyXML_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} /usr/include/sdformat-1.4 ${PYTHON_INCLUDE_DIR})



############
## UTILS  ##
############

add_library(NumberSampler src/utils/NumberSampler.cpp)


##############
## RESOURCE ##
##############
#add_library(ResourceHandler src/Resource/ResourceHandler.cpp)
#target_link_libraries(ResourceHandler ${catkin_LIBRARIES} ${TinyXML_LIBRARIES})

#add_library(TerrainAnalyzer src/Generators/Gazebo/TerrainAnalyzer.cpp)
#target_link_libraries(TerrainAnalyzer ${catkin_LIBRARIES} ${OpenCV_LIBS})


#############
#### RULES ##
#############
#add_library(RULE_wp_path_inside_map src/Rules/RULE_wp_path_inside_map.cpp)
#target_link_libraries(RULE_wp_path_inside_map ${catkin_LIBRARIES}
#TerrainAnalyzer ResourceHandler
#)

#add_library(RULE_platform_init_pose_with_no_obj_colisions src/Rules/RULE_platform_init_pose_with_no_obj_colisions.cpp)
#target_link_libraries(RULE_platform_init_pose_with_no_obj_colisions ${catkin_LIBRARIES}
#TerrainAnalyzer ResourceHandler
#)




#############
### SFDP ####
#############
add_library(ScenarioFeatureGroup src/SFDP/ScenarioFeatureGroup.cpp)
add_library(ScenarioFeature src/SFDP/ScenarioFeature.cpp)

target_link_libraries(ScenarioFeature ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
NumberSampler
)


target_link_libraries(ScenarioFeatureGroup  ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
ScenarioFeature
)


#add_library(SFDPobj src/SFDP/SFDPobj.cpp)
#target_link_libraries(SFDPobj ${catkin_LIBRARIES} ${Boost_INCLUDE_DIR}
#ScenarioFeatureGroup
#ScenarioFeature
#SFVComponent
#GazeboExecutor
#GazeboScenarioGenerator
#)


#############
#### SFV ####
#############


add_library(SFVwp src/SFV/SFVwp.cpp)
target_link_libraries(SFVwp ${catkin_LIBRARIES}
)

add_library(SFVpath src/SFV/SFVpath.cpp)
target_link_libraries(SFVpath ${catkin_LIBRARIES}
SFVwp
)


add_library(SFVmass_link src/SFV/SFVmass_link.cpp)
target_link_libraries(SFVmass_link ${catkin_LIBRARIES}
)

add_library(SFVterraine src/SFV/SFVterraine.cpp)
target_link_libraries(SFVterraine ${catkin_LIBRARIES}
)


add_library(SFVObject src/SFV/SFVObject.cpp)
target_link_libraries(SFVterraine ${catkin_LIBRARIES}
)

add_library(SFVobjScattering src/SFV/SFVobjScattering.cpp)
target_link_libraries(SFVobjScattering ${catkin_LIBRARIES}
SFVObject
)


add_library(SFV src/SFV/SFV.cpp)
target_link_libraries(SFV ${catkin_LIBRARIES}
#SFDPobj
SFVpath
SFVmass_link
SFVterraine
SFVobjScattering
)

##############
# GENERATORS #
##############

#add_library(GazeboEnvironmentGenerator src/Generators/Gazebo/GazeboEnvironmentGenerator.cpp)
#target_link_libraries(GazeboEnvironmentGenerator ${catkin_LIBRARIES}
#ResourceHandler
#TerrainAnalyzer
#)

#add_library(GazeboMissionGenerator src/Generators/Gazebo/GazeboMissionGenerator.cpp)
#target_link_libraries(GazeboMissionGenerator ${catkin_LIBRARIES}
#ResourceHandler
#TerrainAnalyzer
#)

#add_library(GazeboPlatformGenerator src/Generators/Gazebo/GazeboPlatformGenerator.cpp)
#target_link_libraries(GazeboPlatformGenerator ${catkin_LIBRARIES}
#ResourceHandler
#/usr/lib/libsdformat.so
#)


#add_library(GazeboScenarioGenerator src/Generators/Gazebo/GazeboScenarioGenerator.cpp)
#target_link_libraries(GazeboScenarioGenerator ${catkin_LIBRARIES}
#GazeboEnvironmentGenerator
#GazeboMissionGenerator
#GazeboPlatformGenerator
#)



############
# Executor #
############
add_library(GazeboExecutor src/Executor/GazeboExecutor.cpp)
target_link_libraries(GazeboExecutor ${catkin_LIBRARIES}
)


############################
#### ScenarioCoordinator ###
############################
#add_library(ScenarioCoordinator src/Synchronizer/ScenarioCoordinator.cpp) 
#target_link_libraries(ScenarioCoordinator ${catkin_LIBRARIES} ${PYTHON_LIBRARY}
#)

#add_library(ScenarioCoordinatorPoolDestroyer STATIC src/Synchronizer/ScenarioCoordinatorPoolDestroyer.cpp)
#target_link_libraries(ScenarioCoordinatorPoolDestroyer ${catkin_LIBRARIES}
#ScenarioCoordinatorPool
#)


#add_library(ScenarioCoordinatorPool STATIC src/Synchronizer/ScenarioCoordinatorPool.cpp)
#target_link_libraries(ScenarioCoordinatorPool ${catkin_LIBRARIES}
#ScenarioCoordinator
#ScenarioCoordinatorPoolDestroyer
#)




#############
#### MAIN ###
#############
add_executable(MainTest src/MainTest.cpp)
target_link_libraries(MainTest ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
ScenarioFeatureGroup
ScenarioFeature
#SFDPobj
SFV
)


######################
#### Sampling Algo ###
######################
#add_executable(SamplingAlgo src/SamplingAlgo.cpp)
#target_link_libraries(SamplingAlgo ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
#SFVComponent
#SFDPobj
#SFDPParser
#GazeboScenarioGenerator
#)



######################
#### Replay Player ###
######################
#add_executable(ReplayPlayer src/ReplayPlayer/ReplayPlayer.cpp)
#target_link_libraries(ReplayPlayer ${catkin_LIBRARIES}
#)



###############
#### grader ###
###############
#add_executable(grader_node src/Grader/grader_node.cpp)
#target_link_libraries(grader_node
#   ${catkin_LIBRARIES}
#)




