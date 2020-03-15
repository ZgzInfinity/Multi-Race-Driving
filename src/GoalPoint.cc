

#include "../include/GoalPoint.h"


/**
 * Default constructor of the data type
 */
GoalPoint::GoalPoint(){};




/**
 * Constructor of the data type GoalPoint
 * @param pathFile is the path that contains the file with the image of the goal point
 * @param positionX is the position in the axis X of the goal point
 * @param stepPos is the step of the map where the goal point is going to be stored
 * @return an instance of the data type GoalPoint
 */
GoalPoint::GoalPoint(const string pathFile, const float positionX, const int stepPos){
    path = pathFile;
    posX = positionX;
    stepPosition = stepPos;
}
