# Obstacle Avoidance Robot
A simple robot meant to endlessly avoid obstacles in its path.
### Operation:
The robot uses the ultrasonic sensors to "see" in front of it (~120 degrees combined). If the sensors notice something near them (~12in away), the robot turns left, right, or reverses depending on where the object is. This continues until either you turn it off, or the battery runs out. See the comments in the code for the specific funtional details.

Note: The ultrasonic sensors work by bouncing a high frequency (40kHz) pulse of off anything in front of it, then converting the time it takes for the pulse to return (Time of Flight) into distance. Consequenly, if the object is at an angle from the sensor, them the sensor is effectively blind to it. Additionally, If the object is below or above the sensor's "viewing" range (~30 degrees per sensor), the sensor will not notice it either... so, obstable avoidance...within reason.
### Components:
* [Arduino Mega](https://store.arduino.cc/usa/arduino-mega-2560-rev3) - The brains of the robot
* [Ultrasonic Sensors (3)](https://www.sparkfun.com/products/13959) - Used for sensing obstacles
* [Sensor Mounts (3)](https://www.amazon.com/gp/product/B01FDGU0GY/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1) - To hold the ultrasonic sensors
* [Motor Driver](https://www.amazon.com/gp/product/B017FZF42G/ref=oh_aui_detailpage_o03_s00?ie=UTF8&psc=1) - Controls the DC motors
* [Cheap Chasis](https://www.amazon.com/DAGU-HI-TECH-ELECTRONICS-DG008-Chassis/dp/B00B88F66Q/ref=sr_1_1?ie=UTF8&qid=1519367387&sr=8-1&keywords=DAGU+HI-TECH+ELECTRONICS+DG008) - The robot's body
* [7.4v LiPo battery](https://www.amazon.com/gp/product/B00HVQORR8/ref=oh_aui_detailpage_o08_s01?ie=UTF8&psc=1) - To power the whole thing
* [Toggle switch](https://www.amazon.com/SPST-Subminiature-Toggle-Switch-handle/dp/B0193XU2GQ/ref=sr_1_10?s=industrial&ie=UTF8&qid=1519367646&sr=1-10&keywords=spst+toggle+switch) - To turn it ON/OFF
