#!/bin/sh


#locate SRVSS package
SRVSS_dir=$(rospack find SRVSS)

# replacing environment models in .gazebo in order to avoid collisions in the greading process
cp $SRVSS_dir/world_components_models/. $HOME/.gazebo/models/ -R

