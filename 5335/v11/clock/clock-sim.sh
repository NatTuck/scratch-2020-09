#!/bin/bash
WD=`pwd`

source /usr/share/gazebo/setup.sh
export GAZEBO_MODEL_PATH=$GAZEBO_MODEL_PATH:$WD
export GAZEBO_PLUGIN_PATH=$GAZEBO_PLUGIN_PATH:$WD

gazebo --verbose ./clock-demo.world
