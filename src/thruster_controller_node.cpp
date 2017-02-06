#include <auv_thrust_control/Axis.hpp>
#include <auv_thrust_control/Strafe.hpp>

double radiansToDegrees(double r) { return r * 180 / M_PI; }
double degreesToRadians(double d) { return d * M_PI / 180; }

int main(int argc, char **argv) {

  ros::init(argc, argv, "motor_controller");
  ros::NodeHandle nh_;
  Strafe axis_strafe_;
  Axis axis_roll_, axis_pitch_, axis_yaw_;
  Thrusters thrusters_strafe_, thrusters_heave_;
  Thrusters thrusters_pitch_, thrusters_roll_, thrusters_yaw_;
  Thrusters thrusters_xy_combined_, thrusters_z_combined_;
  Thrusters thrusters_final_;

  double thrusters_xy_mult = .35;
  double thrusters_z_mult = 1.0;

  auv_thruster_control::ThrustStamped thrust_stamped_;

  axis_strafe_.surge_.setSubscriber("controlEffort_surge", 1);
  axis_strafe_.sway_.setSubscriber("controlEffort_sway", 1);
  axis_strafe_.heave_.setSubscriber("controlEffort_heave", 1);
  axis_roll_.setSubscriber("controlEffort_roll", 1);
  axis_pitch_.setSubscriber("controlEffort_pitch", 1);
  axis_yaw_.setSubscriber("controlEffort_yaw", 1);

  ros::Publisher thruster_pub_ =
      nh_.advertise<auv_thruster_control::ThrustStamped>("thruster_values_int",
                                                         1);

  ros::Rate loop_rate(10);

  while (ros::ok()) {
    ros::spinOnce();

    loop_rate.sleep();

    axis_strafe_.calcMagnitude();

    // XY Thrusters
    // ROS_INFO("Magnitude: %f", axis_strafe_.strafe_magnitude_);
    thrusters_strafe_ = axis_strafe_.getThrusters();
    ROS_INFO("\033[2J\033[1;1H");
    // ROS_INFO("STRAFE: %s", thrusters_strafe_.toString().c_str());

    thrusters_yaw_ = axis_yaw_.getThrusters(1, -1, 1, -1);

    // ROS_INFO("YAW: %s", thrusters_yaw_.toString().c_str());

    thrusters_xy_combined_ = thrusters_strafe_ + thrusters_yaw_;

    // ROS_INFO("COMBINED: %s", thrusters_xy_combined_.toString().c_str());

    thrusters_xy_combined_.multiplyProportionally(100);

    // ROS_INFO("PROPORTIONED: %s", thrusters_xy_combined_.toString().c_str());

    thrusters_xy_combined_.removeNan();

    // Z Thrusters

    thrusters_heave_ = axis_strafe_.heave_.getThrusters();

    thrusters_roll_ = axis_roll_.getThrusters(-1, 1, -1, 1);

    thrusters_pitch_ = axis_pitch_.getThrusters(-1, -1, 1, 1);

    thrusters_z_combined_ =
        thrusters_heave_ + thrusters_roll_ + thrusters_pitch_;

    thrusters_z_combined_.multiplyProportionally(100);

    thrusters_z_combined_.removeNan();

    thrusters_xy_combined_ *= thrusters_xy_mult;
    thrusters_z_combined_ *= thrusters_z_mult;

    ROS_INFO("XY: %s", thrusters_xy_combined_.toString().c_str());
    ROS_INFO("Z: %s", thrusters_z_combined_.toString().c_str());

    thrust_stamped_.header.stamp = ros::Time::now();

    thrust_stamped_.thrust.xy_fr = thrusters_xy_combined_.getFrontRight();
    thrust_stamped_.thrust.xy_fl = thrusters_xy_combined_.getFrontLeft();
    thrust_stamped_.thrust.xy_br = thrusters_xy_combined_.getBackRight();
    thrust_stamped_.thrust.xy_bl = thrusters_xy_combined_.getBackLeft();

    thrust_stamped_.thrust.z_fr = thrusters_z_combined_.getFrontRight();
    thrust_stamped_.thrust.z_fl = thrusters_z_combined_.getFrontLeft();
    thrust_stamped_.thrust.z_br = thrusters_z_combined_.getBackRight();
    thrust_stamped_.thrust.z_bl = thrusters_z_combined_.getBackLeft();

    thruster_pub_.publish(thrust_stamped_);
  }
}
