
#include "../include/VehicleSpecifications.h"



VehicleSpecifications::VehicleSpecifications(){}


VehicleSpecifications::VehicleSpecifications(const int topSpeed, const float angleOfTurn, const string motorType,
                                             const float accelerateTime, const float brakingTime)
{
    speed = topSpeed;
    angle = angleOfTurn;
    motor = motorType;
    timeToBrake = brakingTime;
    timeAccelerate = accelerateTime;
}
