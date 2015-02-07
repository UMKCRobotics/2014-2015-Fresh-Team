#ifndef PINS_H
#define PINS_H

/********************************************
Motor Pins
- Enables
- Selection (left, right, off)
********************************************/

// Left Motor
const int PIN_MOTOR_L1			= 41;
const int PIN_MOTOR_L2 			= 42;

// Right Motor
const int PIN_MOTOR_L3 			= 18;
const int PIN_MOTOR_L4 			= 17;

/********************************************
Input Pins
- Reading current round and part
- Telling the robot to start
********************************************/
const int PIN_GO_BUTTON_TO 		= 19;
const int PIN_GO_BUTTON_FROM 	= 1;
const int PIN_GO_BUTTON_VCC 	= 9;
const int PIN_GO_BUTTON_GND 	= 21;

const int PIN_ROUND_TYPE_SWITCH = 0; // TODO

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
const int PIN_END_LIGHT_VCC		= 125;
const int PIN_STATUS_LIGHTS_GND	= 123;

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