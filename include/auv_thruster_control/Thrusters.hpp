#ifndef THRUSTER_SET_H_
#define THRUSTER_SET_H_

#include <algorithm>
#include <array>
#include <math.h>
#include <stdio.h>
#include <string>

#include <ros/ros.h>

#include <auv_thruster_control/ThrustStamped.h>

class Thrusters {
public:
  Thrusters();
  Thrusters(double fr, double fl, double br, double bl);
  ~Thrusters();

  double getFrontRight() { return front_right_; }
  double getFrontLeft() { return front_left_; }
  double getBackRight() { return back_right_; }
  double getBackLeft() { return back_left_; }

  double getProportionalMultiplier(double max);

  void multiplyProportionally(double max);

  void removeNan();

  void publish(ros::Publisher pub);

  bool operator!=(const Thrusters &t1);

  Thrusters operator+(const Thrusters &other);
  Thrusters operator+=(const Thrusters &other);
  Thrusters operator*(const double &other);
  Thrusters operator*=(const double &other);

  std::string toString();

  auv_thruster_control::ThrustStamped thrust_stamped_;

  double front_right_, front_left_, back_right_, back_left_;
};

#endif
