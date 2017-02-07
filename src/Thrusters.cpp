#include <auv_thruster_control/Thrusters.hpp>

Thrusters::Thrusters() {}

Thrusters::Thrusters(double fr, double fl, double br, double bl)
    : front_right_(fr), front_left_(fl), back_right_(br), back_left_(bl) {}

Thrusters::~Thrusters() {}

double Thrusters::getProportionalMultiplier(double max) {
  double maxThruster = std::max({fabs(front_right_), fabs(front_left_),
                                 fabs(back_right_), fabs(back_left_)});
  if (maxThruster <= max)
    return 1.0;
  else
    return max / maxThruster;
}

void Thrusters::multiplyProportionally(double max) {
  *this *= getProportionalMultiplier(max);
}

void Thrusters::removeNan() {
  front_right_ = (std::isnan(front_right_) ? 0.0 : front_right_);
  front_left_ = (std::isnan(front_left_) ? 0.0 : front_left_);
  back_right_ = (std::isnan(back_right_) ? 0.0 : back_right_);
  back_left_ = (std::isnan(back_left_) ? 0.0 : back_left_);
}

void Thrusters::publish(ros::Publisher pub) {
  thrust_stamped_.header.stamp = ros::Time::now();

  thrust_stamped_.thrust.fr = front_right_;
  thrust_stamped_.thrust.fl = front_left_;
  thrust_stamped_.thrust.br = back_right_;
  thrust_stamped_.thrust.bl = back_left_;

  pub.publish(thrust_stamped_);
}

std::string Thrusters::toString() {
  char values[100];
  sprintf(values, "FR: %f, FL: %f, BR: %f, BL: %f", front_right_, front_left_,
          back_right_, back_left_);
  return std::string(values);
}

bool Thrusters::operator!=(const Thrusters &t2) {
  return (front_right_ != t2.front_right_ && front_left_ != t2.front_left_ &&
          back_right_ != t2.back_right_ && back_left_ != t2.back_left_);
}

Thrusters Thrusters::operator+(const Thrusters &other) {
  return Thrusters(this->front_right_ + other.front_right_,
                   this->front_left_ + other.front_left_,
                   this->back_right_ + other.back_right_,
                   this->back_left_ + other.back_left_);
}

Thrusters Thrusters::operator+=(const Thrusters &other) {
  this->front_right_ += other.front_right_;
  this->front_left_ += other.front_left_;
  this->back_right_ += other.back_right_;
  this->back_left_ += other.back_left_;
  return *this;
}

Thrusters Thrusters::operator*(const double &other) {
  return Thrusters(this->front_right_ * other, this->front_left_ * other,
                   this->back_right_ * other, this->back_left_ * other);
}

Thrusters Thrusters::operator*=(const double &other) {
  this->front_right_ *= other;
  this->front_left_ *= other;
  this->back_right_ *= other;
  this->back_left_ *= other;
  return *this;
}
