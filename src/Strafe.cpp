#include <auv_thruster_control/Strafe.hpp>

double Strafe::getEffortHeading() {
  int offset;
  double heading_degrees;
  double sway = sway_.getEffort();
  double surge = surge_.getEffort();

  if (sway >= 0 && surge >= 0)
    offset = 0;
  else if ((sway >= 0 && surge < 0) || (sway < 0 && surge < 0))
    offset = 180;
  else
    offset = 360;

  double heading_radians = atan(sway / surge);

  heading_degrees =
      std::isnan(heading_radians) ? 0 : radiansToDegrees(heading_radians);

  return heading_degrees + offset;
}

void Strafe::calcMagnitude() {
  strafe_magnitude_ = sqrt(2) * sqrt((surge_.getEffort() * surge_.getEffort()) +
                                     (sway_.getEffort() * sway_.getEffort()));
}

double Strafe::magnitudeSwayOffset(double heading) {
  heading += 45;
  if (heading >= 360) {
    heading = heading - 360;
  }
  return magnitudeSway(heading);
}

double Strafe::magnitudeSurgeOffset(double heading) {
  heading += 45;
  if (heading >= 360) {
    heading -= 360;
  }
  return magnitudeSurge(heading);
}

Thrusters Strafe::getThrusters() {

  double heading = getEffortHeading();
  double mag_surge = magnitudeSurgeOffset(heading);
  double mag_sway = magnitudeSwayOffset(heading);
  return Thrusters(mag_surge * strafe_magnitude_, mag_sway * strafe_magnitude_,
                   mag_sway * strafe_magnitude_, mag_surge * strafe_magnitude_);
}
