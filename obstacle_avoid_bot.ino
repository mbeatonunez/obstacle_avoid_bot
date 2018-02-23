/*
 * Name:        Obstacle Avoidance Bot
 * Author:      Moises Beato Nunez
 * Date:        22 Feb 2018
 * Description: A simple robot that can endlessly roams an area while avoiding obstacle.
 *				The robot is controlled via an Arduino Mega, and uses 3 HC-SR04 Ultrasonic
 * 				to "see" in front of it. It uses a L983n v3 Dual H-Bridge to drive 4 DC motors,
 *              an SPST switch to start it, and it is powered by  7.4v @ 3300mAh LIPO battery.
 */

#define VERSION 1.0.1
 
// Trigger and Echo pins per sensor (HC-SR04)
#define TRIGGER_FRONT     22
#define ECHO_FRONT        23
#define TRIGGER_RIGHT     24
#define ECHO_RIGHT        25
#define TRIGGER_LEFT      26
#define ECHO_LEFT         27


#define PING_MIN_DISTANCE 30  //Min distance from obstacle (30cm or ~12in) 

#define DELAYTIME 250         //stops everything while the robot turns.
                              //Increase to extend the turning time.
                              //Note: the faster the speed, the more it turns at each time.      
/*
 * Motor setup: PWM pins
 *    Left motors   -> Front: 8,9
 *                  -> Rear : 10,11
 *    Right motors  -> Front: 7,6
 *                  -> Rear : 4,5
 * Note: since the motor pins are sent analog signals, 
 * their pins do not need to be initialized
 */
int motor_left[] = {8,9,10,11};  
int motor_right[] = {7,6,5,4};

const uint8_t speed = 192; //out of 225 (MAX SPEED)

void setup() {
  //initialize the trigger and echo pins for the sensors
  //Triggers send the ultrasonic pulse and Echoes receive them
  pinMode(TRIGGER_FRONT, OUTPUT); 
  pinMode(TRIGGER_RIGHT, OUTPUT);
  pinMode(TRIGGER_LEFT,  OUTPUT);

  pinMode(ECHO_FRONT, INPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(ECHO_LEFT,  INPUT);
  

}
/*
 * loop()    	Infinitively check and void obstacles
 * argument: 	void
 * operation: 	The robot avoids obstacles by comparing the distance received by the sensor functions
 *				to the predefined minimum distance from any object. If the condition return true, the robot
 *				turn in the direction opposite to the sensor that detected the nearby object. For example,
 *				if the right sensor perceives a near by object, the robot turns left until the object is no longer 
 *				in range
 * Returns:   	void
 */
void loop() { 
    if(front_sensor() < PING_MIN_DISTANCE){ 					//if something is in front of it, drive backwards and turn left
        motors_backward();
        delay(DELAYTIME);                             			//turn for this amount of time
        motors_left();
        delay(DELAYTIME);
    }else if(right_sensor() < PING_MIN_DISTANCE) motors_left(); //if the right sensor pings, turn left until clear
    
    else if(left_sensor() < PING_MIN_DISTANCE) motors_right(); //if the left sensor pings, turn right until clear

	//if trapped in a corner, back up until one or both sensors are clear
    else if((right_sensor() < PING_MIN_DISTANCE)&& (left_sensor() < PING_MIN_DISTANCE)) motors_backward();
    else motors_forward();   								//Drive forward until you run into something

}

/*
 * xxxx_sensor() checks for distance from obstacle
 * argument:     void
 * operation:    The trigger sends a ping, then the echo receives it. 
 *               using the duration of the return ping, it then calculates
 *               the distance in mm
 * Returns:      Distance in mm
 */
static long front_sensor(void){   
    long distance_front, duration_front; 
    digitalWrite(TRIGGER_FRONT, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_FRONT, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_FRONT, LOW);
    duration_front = pulseIn(ECHO_FRONT, HIGH);
    distance_front = (duration_front/2) / 29.1;
    return  distance_front;
}
static long right_sensor(void){
    long distance_right, duration_right;
    digitalWrite(TRIGGER_RIGHT, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_RIGHT, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_RIGHT, LOW);
    duration_right = pulseIn(ECHO_RIGHT, HIGH);
    distance_right = (duration_right/2) / 29.1;
    return distance_right;
}
static long left_sensor(void){
    long distance_left, duration_left;
    digitalWrite(TRIGGER_LEFT, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_LEFT, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_LEFT, LOW);
    duration_left = pulseIn(ECHO_LEFT, HIGH);
    distance_left  = (duration_left/2) / 29.1;
    return distance_left;
}
// end of distance check


/*
 * motors_xxxx() moves robot in the desired direction
 * argument:    void
 * operation:  	Send a PWM signal to the positive terminal of the DC motor to engage it,
 *				or send a PWM signal to the negative terminal to reverse the motion. Send
 *				zeros to all the terminals to make the motors stop.
 * Returns:  	void
 */
void motors_forward(void) 
{ //both sided forward
  analogWrite(motor_left[0], speed);
  analogWrite(motor_left[1], 0);
  analogWrite(motor_left[2], speed);
  analogWrite(motor_left[3], 0);  

  analogWrite(motor_right[0], speed);
  analogWrite(motor_right[1], 0);
  analogWrite(motor_right[2], speed);
  analogWrite(motor_right[3], 0);  
}

void motors_backward(void) 
{ //both sides reversed
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], speed);
  analogWrite(motor_left[2], 0);
  analogWrite(motor_left[3], speed);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], speed);
  analogWrite(motor_right[2], 0);
  analogWrite(motor_right[3], speed);
 
}
void motors_right(void) 
{
  //right_side back, left_side forward 
  analogWrite(motor_left[0], speed);
  analogWrite(motor_left[1], 0);
  analogWrite(motor_left[2], speed);
  analogWrite(motor_left[3], 0);

  analogWrite(motor_right[0], 0);
  analogWrite(motor_right[1], speed);
  analogWrite(motor_right[2], 0);
  analogWrite(motor_right[3], speed);
}

void motors_left(void) 
{
   //left_side back, right_side forward 
  analogWrite(motor_left[0], 0);
  analogWrite(motor_left[1], speed);
  analogWrite(motor_left[2], 0);
  analogWrite(motor_left[3], speed);

  analogWrite(motor_right[0], speed);
  analogWrite(motor_right[1], 0);
  analogWrite(motor_right[2], speed);
  analogWrite(motor_right[3], 0); 
}
//This function is not currently in use
// void motors_stop(void)
// {
  // analogWrite(motor_left[0], 0); 
  // analogWrite(motor_left[1], 0); 
  // analogWrite(motor_left[2], 0); 
  // analogWrite(motor_left[3], 0);
  
  // analogWrite(motor_right[0], 0); 
  // analogWrite(motor_right[1], 0);
  // analogWrite(motor_right[2], 0); 
  // analogWrite(motor_right[3], 0);

// }

