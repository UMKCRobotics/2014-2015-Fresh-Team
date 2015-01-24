#ifndef PINS_H
#define PINS_H

/********************************************
Motor Pins
- Enables
- Selection (left, right, off)
********************************************/

// Left Motor
const int PIN_MOTOR_E1 			= 134; //88; // 134 	136 	138
const int PIN_MOTOR_L1			= 136; //56; 
const int PIN_MOTOR_L2 			= 138; //104;

// Right Motor
const int PIN_MOTOR_E2 			= 135; //55; // 135 	137 	139
const int PIN_MOTOR_L3 			= 137; //57;
const int PIN_MOTOR_L4 			= 139; //105;

/********************************************
Input Pins
- Reading current round and part
- Telling the robot to start
********************************************/
const int PIN_GO_BUTTON_TO 		= 162;
const int PIN_GO_BUTTON_FROM 	= 160;
const int PIN_GO_BUTTON_VCC 	= 161;
const int PIN_GO_BUTTON_GND 	= 150;

/********************************************
Distance Sensors
- Arranged in the following manner:

    ^FRONT^

    FL  FR
  LF      RF

  LB      RB

- Includes their GND, VCC, and signal pins   
********************************************/
// TODO

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