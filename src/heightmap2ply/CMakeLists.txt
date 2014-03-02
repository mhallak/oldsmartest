cmake_minimum_required(VERSION 2.8.3)
project(heightmap2ply)


find_package(catkin REQUIRED COMPONENTS
cmake_modules
)

find_package(Boost REQUIRED COMPONENTS system filesystem)

find_package(TinyXML REQUIRED)

find_package(OpenCV REQUIRED)

find_package(VTK REQUIRED)
                                                                                                                              
catkin_package(
    #LIBRARIES  
    INCLUDE_DIRS
      include
    DEPENDS
      TinyXML
)

                                                                                                                                                 
include_directories(include ${catkin_INCLUDE_DIRS} ${TinyXML_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${VTK_INCLUDE_DIRS})


add_library(Vertex src/Vertex.cpp)
add_library(Face src/Face.cpp)

add_library(DataMaker src/DataMaker.cpp)
target_link_libraries(DataMaker ${catkin_LIBRARIES} ${TinyXML_LIBRARIES})

add_library(PolygonMaker src/PolygonMaker.cpp)
target_link_libraries(PolygonMaker ${catkin_LIBRARIES} ${TinyXML_LIBRARIES} ${OpenCV_LIBRARIES} ${VTK_LIBRARIES}
Vertex
Face
)

add_library(MaterialFileMaker src/MaterialFileMaker.cpp)
target_link_libraries(MaterialFileMaker ${catkin_LIBRARIES} ${TinyXML_LIBRARIES})


add_library(ModelFileMaker src/ModelFileMaker.cpp)
target_link_libraries(ModelFileMaker ${catkin_LIBRARIES} ${TinyXML_LIBRARIES}
DataMaker
)

add_executable(main src/main.cpp)
target_link_libraries(main ${catkin_LIBRARIES} ${OpenCV_LIBRARIES} ${Boost_LIBRARIES}
PolygonMaker
ModelFileMaker
MaterialFileMaker
)
