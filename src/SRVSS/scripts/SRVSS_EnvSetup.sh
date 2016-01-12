#!/bin/sh


#locate SRVSS package
SRVSS_dir=$(rospack find SRVSS)

#replacing environment models in .gazebo in order to avoid collisions in the greading process
cp -R $SRVSS_dir/world_components_models/. $HOME/.gazebo/models/

Robot_meshes_dir=$HOME/.gazebo/models/bobcat/meshes/

find $Robot_meshes_dir -name "*.stl" -exec bash -c 'meshlabserver -i $0 -o ${0/stl/obj}' {} \;
find $Robot_meshes_dir -name "*.STL" -exec bash -c 'meshlabserver -i $0 -o ${0/STL/obj}' {} \;

echo "Robot_meshes_dir = $Robot_meshes_dir"


