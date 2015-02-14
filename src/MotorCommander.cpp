#include "MotorCommander.h"

#include <math.h>
#include "Pins.h"
#include "Navigation.h"

// Define pi here for sake of precision and easy of use
const float pi = 3.14159265358979f;

MotorCommander::MotorCommander()
{

}

// Moves robot in desired cardinal direction
void MotorCommander::move(Robot* robot, Cardinal direction)
{
    if (robot->navigation.getOrientation() == direction){
        moveForward(robot);
    }
    else {
        int x = (robot->navigation.getOrientation() - direction);

        if (x == 0)
        {
            moveForward(robot);
        }
        else
        {
            turn(x*90, robot);
        }
    }
}

void MotorCommander::turn(int degrees, Robot* robot)
{
    if (degrees > 0)
    {
        // left motor back, right foward
        robot->setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
        robot->setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);

        robot->setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
        robot->setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
    }
    else
    {
        // right motor back, left motor foward
        robot->setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
        robot->setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

        robot->setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
        robot->setPinState(PIN_MOTOR_L4, PIN_STATE_LOW);
    }

    // TODO: Send message to Arduino to notify us of when the turn should stop
    robot->arduinoSerial.WriteString(("NotifyOfAngle " + to_string(degrees)).c_str());
}

void MotorCommander::moveForward(Robot* robot)
{
    robot->setPinState(PIN_MOTOR_L1, PIN_STATE_LOW);
    robot->setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

    robot->setPinState(PIN_MOTOR_L3, PIN_STATE_LOW);
    robot->setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
}

void MotorCommander::moveBackward(Robot* robot)
{
    robot->setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
    robot->setPinState(PIN_MOTOR_L2, PIN_STATE_LOW);

    robot->setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
    robot->setPinState(PIN_MOTOR_L4, PIN_STATE_LOW);
}

void MotorCommander::halt(Robot* robot)
{
    robot->setPinState(PIN_MOTOR_L1, PIN_STATE_HIGH);
    robot->setPinState(PIN_MOTOR_L2, PIN_STATE_HIGH);

    robot->setPinState(PIN_MOTOR_L3, PIN_STATE_HIGH);
    robot->setPinState(PIN_MOTOR_L4, PIN_STATE_HIGH);
}