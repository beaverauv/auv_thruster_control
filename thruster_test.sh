
function set_zero() {
  rostopic pub /thrust_xy auv_thruster_control/ThrustStamped "header:
  seq: 0\
  stamp:\
    secs: 0\
    nsecs: 0\
  frame_id: ''\
thrust:\
  fr: 0\
  bl: 0\
  br: 0\
  bl: 0"
}

echo "Testing horizontal thrusters"

read -p "Press enter to start"

echo "Testing Horizontal Front Right"

rostopic pub /thrust_xy auv_thruster_control/ThrustStamped "header:
  seq: 0\
  stamp:\
    secs: 0\
    nsecs: 0\
  frame_id: ''\
thrust:\
  fr: 10\
  fl: 0\
  br: 0\
bl: 0"

set_zero

echo "Testing Horizontal Front Left"

rostopic pub /thrust_xy auv_thruster_control/ThrustStamped "header:
  seq: 0\
  stamp:\
    secs: 0\
    nsecs: 0\
  frame_id: ''\
thrust:\
  fr: 0\
  fl: 10\
  br: 0\
bl: 0"

set_zero



echo "Testing Horizontal Back Right"

rostopic pub /thrust_xy auv_thruster_control/ThrustStamped "header:
  seq: 0\
  stamp:\
    secs: 0\
    nsecs: 0\
  frame_id: ''\
thrust:\
  fr: 0\
  fl: 0\
  br: 10\
bl: 0"

set_zero

echo "Testing Horizontal Back Left"

rostopic pub /thrust_xy auv_thruster_control/ThrustStamped "header:
  seq: 0\
  stamp:\
    secs: 0\
    nsecs: 0\
  frame_id: ''\
thrust:\
  fr: 0\
  fl: 0\
  br: 0\
bl: 10"

set_zero




echo "Testing Vertical Front Right"

rostopic pub /thrust_z auv_thruster_control/ThrustStamped "header:
  seq: 0\
  stamp:\
    secs: 0\
    nsecs: 0\
  frame_id: ''\
thrust:\
  fr: 10\
  fl: 0\
  br: 0\
bl: 0"

set_zero

echo "Testing Vertical Front Left"

rostopic pub /thrust_z auv_thruster_control/ThrustStamped "header:
  seq: 0\
  stamp:\
    secs: 0\
    nsecs: 0\
  frame_id: ''\
thrust:\
  fr: 0\
  fl: 10\
  br: 0\
bl: 0"

set_zero

echo "Testing Vertical Back Right"

rostopic pub /thrust_z auv_thruster_control/ThrustStamped "header:
  seq: 0\
  stamp:\
    secs: 0\
    nsecs: 0\
  frame_id: ''\
thrust:\
  fr: 0\
  fl: 0\
  br: 10\
bl: 0"

set_zero

echo "Testing Vertical Back Left"

rostopic pub /thrust_z auv_thruster_control/ThrustStamped "header:
  seq: 0\
  stamp:\
    secs: 0\
    nsecs: 0\
  frame_id: ''\
thrust:\
  fr: 0\
  fl: 0\
  br: 0\
bl: 10"

set_zero
