#ifndef PINS_H
#define PINS_H

/********************************************
Motor Pins
- Enables
- Selection (left, right, off)
********************************************/

// Left Motor
const int PIN_MOTOR_E1 			= 4;
const int PIN_MOTOR_L1			= 6;
const int PIN_MOTOR_L2 			= 7;

// Right Motor
const int PIN_MOTOR_E2 			= 5;
const int PIN_MOTOR_L3 			= 8;
const int PIN_MOTOR_L4 			= 9;

/********************************************
Input Pins
- Reading current round and part
- Telling the robot to start
********************************************/
const int PIN_GO_BUTTON_TO 					= 162;
const int PIN_GO_BUTTON_FROM 				= 160;
const int PIN_GO_BUTTON_VCC 				= 161;
const int PIN_GO_BUTTON_GND 				= 150;

const int PIN_ROUND_SELECT_VCC 				= 16;
const int PIN_ROUND_SELECT_SIGNAL 			= 11;
const int PIN_ROUND_SELECT_GND 				= 4;

const int PIN_PART_SELECT_VCC				= 40;
const int PIN_PART_SELECT_SIGNAL			= 3;
const int PIN_PART_SELECT_GND				= 3;

/********************************************
Distance Sensors
- Arranged in the following manner:

    ^FRONT^

    FL  FR
  LF      RF

  LB      RB

- Includes their GND, VCC, and signal pins   
********************************************/


/********************************************
Output Pins
- LED's for showing robot state
- Also includes their GND pins
- If you're not an electrical: an LED just
  needs a potential difference, not an actual
  ground to emit light
********************************************/
const int PIN_READY_LIGHT_VCC			= 13;
const int PIN_READY_LIGHT_GND 			= 13;

const int PIN_END_LIGHT_VCC				= 13;
const int PIN_END_LIGHT_GND 			= 13;

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