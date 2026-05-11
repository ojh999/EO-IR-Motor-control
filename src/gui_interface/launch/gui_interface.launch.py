from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

import os


def generate_launch_description():
    package_share = get_package_share_directory("gui_interface")
    params_file = os.path.join(package_share, "config", "params.yaml")

    return LaunchDescription([
        Node(
            package="gui_interface",
            executable="gui_interface_node",
            name="gui_interface_node",
            output="screen",
            parameters=[params_file],
        )
    ])
