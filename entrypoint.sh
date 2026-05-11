#!/bin/bash
source /opt/ros/jazzy/setup.bash

if [ -f /root/pan_tilt_ws/install/setup.bash ]; then
    source /root/pan_tilt_ws/install/setup.bash
fi

exec "$@"