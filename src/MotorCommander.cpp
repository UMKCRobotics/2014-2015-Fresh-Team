#include <math.h>
#include "MotorCommander.h"
#include "Pins.h"
#include "Navigation.h"
#include "Interface.h"

MotorCommander::MotorCommander()
{

}

// Moves robot in desired cardinal direction
void MotorCommander::move(Cardinal currentOrientation, Cardinal direction)
{
    if (currentOrientation == direction) {
        moveForward();
    }
    else {
        int x = (direction - currentOrientation);

        if (x == 0)
        {
            moveForward();
        }
        else
        {
            turn(x*90);
        }
    }
}

void MotorCommander::turn(int degrees)
{
    if (degrees < 0)
    {
        // right motor back, left foward
        Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
        Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

        Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
        Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_LOW);
    }
    else
    {
        // left motor back, right motor foward
        Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
        Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);

        Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
        Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
    }

    //arduinoSerial.WriteString(("NotifyOfAngle " + to_string(degrees)).c_str());
}

void MotorCommander::moveForward()
{
    Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
    Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

    Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
    Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
}

void MotorCommander::moveBackward()
{
    Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
    Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);

    Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
    Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_LOW);
}

void MotorCommander::halt()
{
    Interface::setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
    Interface::setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

    Interface::setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
    Interface::setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
}