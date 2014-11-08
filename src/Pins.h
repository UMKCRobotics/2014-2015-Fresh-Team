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
const int PIN_GO_BUTTON 		= 10;
const int PIN_ROUND_SELECT 		= 11;
const int PIN_PART_SELECT		= 12;

/********************************************
Output Pins
- LED's for showing robot state
********************************************/
const int PIN_READY				= 13;
const int PIN_END				= 14;

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