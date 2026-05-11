cmake_minimum_required(VERSION 3.8)
project(gui_interface)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(rclcpp REQUIRED)
find_package(sentinel_interfaces REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(gui_interface_node
  src/gui_interface_node.cpp
)

target_include_directories(gui_interface_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
)

target_compile_features(gui_interface_node PUBLIC c_std_99 cxx_std_17)
ament_target_dependencies(gui_interface_node
  rclcpp
  sentinel_interfaces
  std_msgs
)
target_link_libraries(gui_interface_node Boost::system)

install(TARGETS gui_interface_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/ config/ launch/
  DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
