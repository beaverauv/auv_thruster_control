#include <auv_thruster_control/ThrustStamped.h>
#include <iostream>
#include <limits>
#include <ros/ros.h>

ros::Publisher thruster_xy_pub_;
ros::Publisher thruster_z_pub_;

void wait_for_enter(std::string string) {
  std::cout << string << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pub_thrust_horizontal(int fr, int fl, int br, int bl) {
  auv_thruster_control::ThrustStamped thrust;
  thrust.thrust.fr = fr;
  thrust.thrust.fl = fl;
  thrust.thrust.br = br;
  thrust.thrust.bl = bl;
  thruster_xy_pub_.publish(thrust);
}

void pub_thrust_vertical(int fr, int fl, int br, int bl) {
  auv_thruster_control::ThrustStamped thrust;
  thrust.thrust.fr = fr;
  thrust.thrust.fl = fl;
  thrust.thrust.br = br;
  thrust.thrust.bl = bl;
  thruster_z_pub_.publish(thrust);
}

void zero_thrust_horizontal() { pub_thrust_horizontal(0, 0, 0, 0); }
void zero_thrust_vertical() { pub_thrust_vertical(0, 0, 0, 0); }
int main(int argc, char **argv) {

  ros::init(argc, argv, "motor_controller");
  ros::NodeHandle nh_;

  thruster_xy_pub_ =
      nh_.advertise<auv_thruster_control::ThrustStamped>("thrust_xy", 1);

  thruster_z_pub_ =
      nh_.advertise<auv_thruster_control::ThrustStamped>("thrust_z", 1);

  wait_for_enter("Press enter to start testing");

  wait_for_enter("Press enter to start running horizontal front right");

  pub_thrust_horizontal(10, 0, 0, 0);

  wait_for_enter("Press enter to stop");

  zero_thrust_horizontal();

  wait_for_enter("Press enter to start running horizontal front left");

  pub_thrust_horizontal(0, 10, 0, 0);

  wait_for_enter("Press enter to stop");

  zero_thrust_horizontal();

  wait_for_enter("Press enter to start running horizontal back right");

  pub_thrust_horizontal(0, 0, 10, 0);

  wait_for_enter("Press enter to stop");

  zero_thrust_horizontal();

  wait_for_enter("Press enter to start running horizontal back left");

  pub_thrust_horizontal(0, 0, 0, 10);

  wait_for_enter("Press enter to stop");

  zero_thrust_horizontal();

  wait_for_enter("Press enter to start running vertical front right");

  pub_thrust_vertical(10, 0, 0, 0);

  wait_for_enter("Press enter to stop");

  zero_thrust_vertical();

  wait_for_enter("Press enter to start running vertical front left");

  pub_thrust_vertical(0, 10, 0, 0);

  wait_for_enter("Press enter to stop");

  zero_thrust_vertical();

  wait_for_enter("Press enter to start running vertical back right");

  pub_thrust_vertical(0, 0, 10, 0);

  wait_for_enter("Press enter to stop");

  zero_thrust_vertical();

  wait_for_enter("Press enter to start running vertical back left");

  pub_thrust_vertical(0, 0, 0, 10);

  wait_for_enter("Press enter to stop");

  zero_thrust_vertical();
}
