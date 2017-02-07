#include <auv_thruster_control/Axis.hpp>
#include <auv_thruster_control/Strafe.hpp>

double radiansToDegrees(double r) { return r * 180 / M_PI; }
double degreesToRadians(double d) { return d * M_PI / 180; }

int main(int argc, char **argv) {

  ros::init(argc, argv, "motor_controller");
  ros::NodeHandle nh_;
  Strafe axis_strafe_;
  Axis axis_roll_, axis_pitch_, axis_yaw_;
  Thrusters thrusters_strafe_, thrusters_heave_;
  Thrusters thrusters_pitch_, thrusters_roll_, thrusters_yaw_;
  Thrusters thrusters_xy_, thrusters_z_;
  Thrusters thrusters_xy_saved_, thrusters_z_saved_;

  double thrusters_xy__mult = .35;
  double thrusters_z_mult = 1.0;

  auv_thruster_control::ThrustStamped thrust_stamped_;

  axis_strafe_.surge_.setSubscriber("controlEffort_surge", 1);
  axis_strafe_.sway_.setSubscriber("controlEffort_sway", 1);
  axis_strafe_.heave_.setSubscriber("controlEffort_heave", 1);
  axis_roll_.setSubscriber("controlEffort_roll", 1);
  axis_pitch_.setSubscriber("controlEffort_pitch", 1);
  axis_yaw_.setSubscriber("controlEffort_yaw", 1);

  ros::Publisher thruster_xy_pub_ =
      nh_.advertise<auv_thruster_control::ThrustStamped>("thrust_xy", 1);

  ros::Publisher thruster_z_pub_ =
      nh_.advertise<auv_thruster_control::ThrustStamped>("thrust_z", 1);

  ros::Rate loop_rate(10);

  while (ros::ok()) {
    ros::spinOnce();

    loop_rate.sleep();

    // XY Thrusters

    axis_strafe_.calcMagnitude();

    thrusters_strafe_ = axis_strafe_.getThrusters();

    thrusters_yaw_ = axis_yaw_.getThrusters(1, -1, 1, -1);

    thrusters_xy_ = thrusters_strafe_ + thrusters_yaw_;

    thrusters_xy_.multiplyProportionally(100);

    thrusters_xy_.removeNan();

    // Z Thrusters

    thrusters_heave_ = axis_strafe_.heave_.getThrusters();

    thrusters_roll_ = axis_roll_.getThrusters(-1, 1, -1, 1);

    thrusters_pitch_ = axis_pitch_.getThrusters(-1, -1, 1, 1);

    thrusters_z_ = thrusters_heave_ + thrusters_roll_ + thrusters_pitch_;

    thrusters_z_.multiplyProportionally(100);

    thrusters_z_.removeNan();

    thrusters_xy_ *= thrusters_xy__mult;
    thrusters_z_ *= thrusters_z_mult;

    // ROS_INFO("\033[2J\033[1;1H");

    if (thrusters_xy_ != thrusters_xy_saved_) {
      thrusters_xy_.publish(thruster_xy_pub_);
      ROS_INFO("XY: %s", thrusters_xy_.toString().c_str());
    }

    if (thrusters_z_ != thrusters_z_saved_) {
      thrusters_z_.publish(thruster_z_pub_);
      ROS_INFO("Z: %s", thrusters_z_.toString().c_str());
    }

    thrusters_xy_.publish(thruster_xy_pub_);
    thrusters_z_.publish(thruster_z_pub_);

    thrusters_xy_saved_ = thrusters_xy_;
    thrusters_z_saved_ = thrusters_z_;

    // thruster_pub_.publish(thrust_stamped_);
  }
}
