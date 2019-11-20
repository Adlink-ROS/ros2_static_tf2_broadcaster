#include <rclcpp/rclcpp.hpp>
#include <cstdio>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <chrono>

using namespace std::chrono_literals;

std::string static_turtle_name;

int main(int argc, char ** argv)
{

  // initialize ros2 and create a node
  rclcpp::init(argc, argv);
  rclcpp::Node::SharedPtr node = rclcpp::Node::make_shared("ros2_static_tf2_broadcaster");

  if(argc != 8)
  {
    RCLCPP_INFO(node->get_logger(), "Invalid number of parameters\nusage: tf2_broadcaster child_frame_name x y z roll pitch yaw");
    return -1;
  }
  if(strcmp(argv[1],"world")==0)
  {
    RCLCPP_INFO(node->get_logger(), "Your static turtle name cannot be 'world'");
    return -1;
  }

  static_turtle_name = argv[1];
  static tf2_ros::TransformBroadcaster static_broadcaster(node);

  geometry_msgs::msg::TransformStamped static_transformStamped;

  while (rclcpp::ok()) 
  {
    static_transformStamped.header.stamp = rclcpp::Clock().now();
    static_transformStamped.header.frame_id = "world";
    static_transformStamped.child_frame_id = static_turtle_name;
    static_transformStamped.transform.translation.x = atof(argv[2]);
    static_transformStamped.transform.translation.y = atof(argv[3]);
    static_transformStamped.transform.translation.z = atof(argv[4]);
    tf2::Quaternion quat;
    quat.setRPY(atof(argv[5]), atof(argv[6]), atof(argv[7]));
    static_transformStamped.transform.rotation.x = quat.x();
    static_transformStamped.transform.rotation.y = quat.y();
    static_transformStamped.transform.rotation.z = quat.z();
    static_transformStamped.transform.rotation.w = quat.w();
    static_broadcaster.sendTransform(static_transformStamped);
    RCLCPP_INFO(node->get_logger(), "Publish %s to world", static_turtle_name.c_str());

    rclcpp::WallRate loop_rate(1s);
    loop_rate.sleep();
  }

  return 0;
}