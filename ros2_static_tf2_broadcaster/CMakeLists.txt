cmake_minimum_required(VERSION 3.5)
project(ros2_static_tf2_broadcaster)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)

include_directories(
  include
  )

add_executable(ros2_static_tf2_broadcaster src/ros2_static_tf2_broadcaster.cpp)

ament_target_dependencies(${PROJECT_NAME}
    "ament_cmake"
    "rclcpp"
    "geometry_msgs"
    "tf2"
    "tf2_geometry_msgs") # Doesn't add this line causing a link error (undefined reference)

install(TARGETS ${PROJECT_NAME}
DESTINATION lib/${PROJECT_NAME})

ament_package()
