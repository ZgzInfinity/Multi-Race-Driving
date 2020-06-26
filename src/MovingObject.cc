

#include "../include/MovingObject.h"
#include "../include/Motorbike.h"

MovingObject::MovingObject(){}


template <typename T>
T MovingObject<T>::selectMovingObject(const int typeOfVehicle, const float max_speed, const float speed_factor,
                                      const float acceleration, const float scaleX, const float scaleY,
                                      const int counter, const string vehicleName, const float posX, const int rectangle)
{
    if (typeOfVehicle == 1){
        vehicle = Motorbike(max_speed, speed_factor, acceleration, scaleX, scaleY, counter, vehicleName, posX, rectangle);
    }
}

