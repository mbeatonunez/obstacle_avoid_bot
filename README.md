# Obstacle Avoidance Robot
A simple robot meant to endlessly avoid obstacles in its path.
### Operation:
The robot uses the ultrasonic sensors to "see" in front of it (~120 degrees combined). If the sensors notice something near them (~12in away), the robot turns left, 
right, or reverses depending on where the object is. This continues until either you turn it off, or the battery runs out. See the comments in the code for the specific functional details.

Note: The ultrasonic sensors work by bouncing a high frequency (40kHz) pulse of off anything in front of it, then converting the time it takes for the pulse to return (Time of Flight) 
into distance. Consequently, if the object is at an angle from the sensor, them the sensor is effectively blind to it. Additionally, If the object is below or above the sensor's "viewing" range 
(~30 degrees per sensor), the sensor will not notice it either... so, obstacle avoidance...within reason.
### Components:
* [Arduino Mega](https://store.arduino.cc/usa/arduino-mega-2560-rev3) - The brains of the robot
* [Ultrasonic Sensors (3)](https://www.sparkfun.com/products/13959) - Used for sensing obstacles
* [Sensor Mounts (3)](https://www.amazon.com/gp/product/B01FDGU0GY/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1) - To hold the ultrasonic sensors
* [Motor Driver](https://www.amazon.com/gp/product/B017FZF42G/ref=oh_aui_detailpage_o03_s00?ie=UTF8&psc=1) - Controls the DC motors
* [Cheap Chassis](https://www.amazon.com/DAGU-HI-TECH-ELECTRONICS-DG008-Chassis/dp/B00B88F66Q/ref=sr_1_1?ie=UTF8&qid=1519367387&sr=8-1&keywords=DAGU+HI-TECH+ELECTRONICS+DG008) - The robot's body
* [7.4v LiPo battery](https://www.amazon.com/gp/product/B00HVQORR8/ref=oh_aui_detailpage_o08_s01?ie=UTF8&psc=1) - To power the whole thing
* [Toggle switch](https://www.amazon.com/SPST-Subminiature-Toggle-Switch-handle/dp/B0193XU2GQ/ref=sr_1_10?s=industrial&ie=UTF8&qid=1519367646&sr=1-10&keywords=spst+toggle+switch) - To turn it ON/OFF
* [Mini breadboard](https://www.amazon.com/Elegoo-6PCS-tie-points-Breadboard-Arduino/dp/B01EV6SBXQ/ref=sr_1_3?s=industrial&ie=UTF8&qid=1519370264&sr=1-3&keywords=mini+breadboard) - To power all the peripherals from the same source

Warning: This motor driver has a 5v regular output that I use to power the ultrasonic sensors via the mini breadboard. In case you don't use this motor driver, you will need to find a different way to regulate the power
going into the sensors.
### Alternative Components
Since this mini project was made out of spare parts from other projects, the items listed above might be overkill.
* [Arduino Uno clone](https://www.amazon.com/Elegoo-EL-CB-001-ATmega328P-ATMEGA16U2-Arduino/dp/B01EWOE0UU/ref=sr_1_3?s=industrial&ie=UTF8&qid=1519370502&sr=1-3&keywords=Arduino+uno) 
* [Motor Driver](https://www.amazon.com/Qunqi-Controller-Module-Stepper-Arduino/dp/B014KMHSW6/ref=sr_1_2?s=industrial&ie=UTF8&qid=1519370602&sr=1-2&keywords=l298n) 

The Uno has 4 PWM pins and 8 other digital pins (along with 6 analog pins that [can also be used as digital pins](https://www.arduino.cc/en/Tutorial/AnalogInputPins)). 
You need 4 PWM pins to drive the L298 motor driver at a user defined speed. Alternatively, you can always use digital pins and have to robot running at full speed. 
Though, you might have to mess with the distance threshold based on the kind of sensor response you get while running at full speed.

Since the DC motors are working as pairs (left-side motors and right-side motors), you can simply connect two motors per side on the motor driver. Allowing you to 
drive the robot with 4 pins rather than 8. 

This motor driver does have a 5v regulator already connected to the enable pins, so, you could use one of those 5v pins to provide power to the ultrasonic sensors, but you have to make sure 
to also power the enable pin if you want both sides of the motor driver to work. 