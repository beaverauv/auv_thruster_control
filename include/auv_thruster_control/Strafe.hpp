#ifndef AXIS_TRANSLATION_H_
#define AXIS_TRANSLATION_H_

#include <auv_thruster_control/Axis.hpp>
#include <auv_thruster_control/Thrusters.hpp>

class Strafe {
public:
  Axis surge_, sway_, heave_;
  double strafe_magnitude_ = 0;

  double getEffortHeading();
  void calcMagnitude();

  double magnitudeSurge(double h) { return cos(degreesToRadians(h)); }
  double magnitudeSway(double h) { return sin(degreesToRadians(h)); }

  double magnitudeSurgeOffset(double heading);
  double magnitudeSwayOffset(double heading);

  double radiansToDegrees(double r) { return r * 180 / M_PI; }
  double degreesToRadians(double d) { return d * M_PI / 180; }

  Thrusters getThrusters();

private:
};

#endif
