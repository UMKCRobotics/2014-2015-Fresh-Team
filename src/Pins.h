#ifndef PINS_H
#define PINS_H

/********************************************
Motor Pins
- Enables
- Selection (left, right, off)
********************************************/

// Left Motor
const int PIN_MOTOR_L1 = 41;
const int PIN_MOTOR_L2 = 42;
// Right Motor
const int PIN_MOTOR_L3 = 17;
const int PIN_MOTOR_L4 = 18;

/********************************************
Input Pins
- Reading current round and part
- Telling the robot to start
********************************************/
const int PIN_GO_BUTTON_TO 		= 19;
const int PIN_GO_BUTTON_FROM 	= 1;
const int PIN_GO_BUTTON_VCC 	= 9;
const int PIN_GO_BUTTON_GND 	= 21;
const int PIN_FAST_ROUND		= 135; 

/********************************************
Distance Sensors
- Arranged in the following manner:

    ^FRONT^

	   F
  LF      RF

  LB      RB

- Includes their GND, VCC, and signal pins   
********************************************/
const int PIN_DISTANCE_SENSOR_F 	= 5;
const int PIN_DISTANCE_SENSOR_LF 	= 2;
const int PIN_DISTANCE_SENSOR_LB 	= 3;
const int PIN_DISTANCE_SENSOR_RF 	= 4;
const int PIN_DISTANCE_SENSOR_RB 	= 0;

/********************************************
Line Sensors
- Arranged with one on the left and one on 
  the right
- Arduino is respondible for telling the 
  Linux side when a line is seen
********************************************/
const int PIN_LINE_SENSOR_L 	= 8;
const int PIN_LINE_SENSOR_M 	= 10;
const int PIN_LINE_SENSOR_R 	= 9;

/********************************************
Output Pins
- LED's for showing robot state
- Also includes their GND pins
- If you're not an electrical: an LED just
  needs a potential difference, not an actual
  ground to emit light
********************************************/
const int PIN_READY_LIGHT_VCC	= 124;
const int PIN_END_LIGHT_VCC		= 126;
const int PIN_STATUS_LIGHTS_GND	= 133;

/********************************************
Pin Settings
- Current pin direction (in; out)
- Current pin setting (0; 1)
********************************************/
const int PIN_STATE_HIGH		= 15;
const int PIN_STATE_LOW			= 16;
const int PIN_DIRECTION_IN		= 17;
const int PIN_DIRECTION_OUT		= 18;

// Pin property constants
const int PIN_DIRECTION 		= 19;
const int PIN_STATE 			= 20;

#endif
