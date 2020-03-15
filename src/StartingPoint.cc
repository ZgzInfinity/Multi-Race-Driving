

#include "../include/StartingPoint.h"


/**
 * Default constructor of the data type
 */
StartingPoint::StartingPoint(){};



/**
 * Constructor of the data type StartingPoint
 * @param pathFile is the path that contains the file with the image of the starting point
 * @param positionX is the position in the axis X of the starting point
 * @param stepPos is the step of the map where the starting point is going to be stored
 * @return an instance of the data type StartingPoint
 */
StartingPoint::StartingPoint(const string pathFile, const float positionX, const int stepPos){
    path = pathFile;
    posX = positionX;
    stepPosition = stepPos;
}

