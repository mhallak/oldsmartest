cmake_minimum_required(VERSION 2.8.3)
project(SRVSS)


find_package(catkin REQUIRED COMPONENTS
cmake_modules
)

find_package(Boost REQUIRED COMPONENTS system)

find_package(TinyXML REQUIRED)

find_package(OpenCV REQUIRED)
                                                                                                                              
catkin_package(
    #LIBRARIES  
    INCLUDE_DIRS
      include
    DEPENDS
      TinyXML
)

                                                                                                                                                 
include_directories(include ${catkin_INCLUDE_DIRS} ${TinyXML_INCLUDE_DIRS} ${Boost_INCLUDE_DIR})

add_library(NumberSampler src/utils/NumberSampler.cpp)






#############
### SFDP ####
#############
add_library(ScenarioFeatureDependecyType src/SFDP/ScenarioFeatureDependecyType.cpp)
add_library(ScenarioFeatureDistributionType src/SFDP/ScenarioFeatureDistributionType.cpp)
add_library(ScenarioFeatureType src/SFDP/ScenarioFeatureType.cpp)
add_library(ScenarioFeature src/SFDP/ScenarioFeature.cpp)

add_library(ScenarioFeatureDependecy src/SFDP/ScenarioFeatureDependecy.cpp)
target_link_libraries(ScenarioFeatureDependecy ${catkin_LIBRARIES}
ScenarioFeatureDependecyType
ScenarioFeatureType
)

target_link_libraries(ScenarioFeature ${catkin_LIBRARIES}
ScenarioFeatureDependecyType
ScenarioFeatureDistributionType
ScenarioFeatureType
ScenarioFeatureDependecy
)

add_library(SDFPComponent src/SFDP/SDFPComponent.cpp)
target_link_libraries(SDFPComponent ${catkin_LIBRARIES}
ScenarioFeatureDependecyType
ScenarioFeatureDistributionType
ScenarioFeatureType
ScenarioFeature
ScenarioFeatureDependecy
NumberSampler
)
add_library(SDFPParser src/SFDP/SDFPParser.cpp)
target_link_libraries(SDFPParser ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
ScenarioFeatureDependecyType
ScenarioFeatureDistributionType
ScenarioFeatureType
ScenarioFeature
SDFPComponent
)


#############
#### SFV ####
#############
add_library(SFVObject src/SFV/SFVObject.cpp)
add_library(SFVLight src/SFV/SFVLight.cpp)
add_library(SFVTerrain src/SFV/SFVTerrain.cpp)
add_library(SFVComponent src/SFV/SFVComponent.cpp)
target_link_libraries(SFVComponent ${catkin_LIBRARIES}
SFVLight
SFVObject
SFVTerrain
)
add_library(SFVParser src/SFV/SFVParser.cpp)
target_link_libraries(SFVParser ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
SFVLight
SFVObject
SFVTerrain
SFVComponent
)

##############
## RESOURCE ##
##############
add_library(ResourceHandler src/Resource/ResourceHandler.cpp)
target_link_libraries(ResourceHandler ${catkin_LIBRARIES} ${TinyXML_LIBRARIES})

##############
# GENERATORS #
##############
add_library(TerrainAnalyzer src/Generators/TerrainAnalyzer.cpp)
target_link_libraries(TerrainAnalyzer ${catkin_LIBRARIES} ${OpenCV_LIBS})

add_library(EnvironmentGenerator src/Generators/EnvironmentGenerator.cpp)
target_link_libraries(EnvironmentGenerator ${catkin_LIBRARIES}
ResourceHandler
TerrainAnalyzer
)
#############
#### MAIN ###
#############
add_executable(mainGen src/Main.cpp)
target_link_libraries(mainGen ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
SDFPComponent
SFVComponent
SDFPParser
SFVParser
EnvironmentGenerator
)

