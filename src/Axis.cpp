#include <auv_thruster_control/Axis.hpp>

Axis::Axis() {}

Axis::~Axis() {}

void Axis::setSubscriber(std::string topic, uint32_t queue_size) {
  control_effort_sub_ =
      nh_.subscribe(topic, queue_size, &Axis::controlEffortCb, this);
}

void Axis::controlEffortCb(const std_msgs::Float64::ConstPtr &effort) {
  control_effort_ = effort->data;
}

Thrusters Axis::getThrusters() {
  return Thrusters(control_effort_, control_effort_, control_effort_,
                   control_effort_);
}

Thrusters Axis::getThrusters(double fr, double fl, double br, double bl) {
  return Thrusters(control_effort_ * fr, control_effort_ * fl,
                   control_effort_ * br, control_effort_ * bl);
}
