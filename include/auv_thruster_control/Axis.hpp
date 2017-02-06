#ifndef AXIS_H_
#define AXIS_H_

#include <auv_thruster_control/Thrusters.hpp>
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>

#include <string>

class Axis {
public:
  Axis();
  ~Axis();

  void setSubscriber(std::string topic, uint32_t queue_size);

  void controlEffortCb(const std_msgs::Float64::ConstPtr &effort);

  double getEffort() { return control_effort_; }

  Thrusters getThrusters();
  Thrusters getThrusters(double fr, double fl, double br, double bl);

  double radiansToDegrees(double r) { return r * 180 / M_PI; }
  double degreesToRadians(double d) { return d * M_PI / 180; }

private:
  ros::Subscriber control_effort_sub_;

  ros::NodeHandle nh_;

  double control_effort_ = 0;
};

#endif
