
#ifndef VEHICLE_SPECIFICATIONS_H
#define VEHICLE_SPECIFICATIONS_H

#include <iostream>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Slot.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace sf;
using namespace rapidxml;



/*
 * Step data type
 */
struct VehicleSpecifications{

    // Max speed of the vehicle
    int speed;

    // Angle of turning of the vehicle
    float angle;

    // Kind of motor of the vehicle
    string motor;

    // Time to brake from max speed
    float timeAccelerate;

    // Time to reach top speed
    float timeToBrake;


    VehicleSpecifications();

    VehicleSpecifications(const int topSpeed, const float angleOfTurn, const string motorType,
                          const float accelerateTime, const float brakingTime);

};

#endif // VEHICLE_SPECIFICATIONS_H

