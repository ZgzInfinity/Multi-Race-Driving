
#ifndef GOAL_POINT_H
#define GOAL_POINT_H

#include <cstring>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


/*
 * Step data type
 */
struct GoalPoint{

    // Starting position of the curves in the road
    string path;

    // Ending position of the curves in the road
    float posX;

    // Direction of the curve in the road
    int stepPosition;

    // Offset to control the collision with the player
    float offset;


    /**
     * Default constructor of the data type
     */
     GoalPoint();



    /**
     * Constructor of the data type GoalPoint
     * @param pathFile is the path that contains the file with the image of the goal point
     * @param positionX is the position in the axis X of the goal point
     * @param stepPos is the step of the map where the goal point is going to be stored
     * @return an instance of the data type GoalPoint
     */
    GoalPoint(const string pathFile, const float positionX, const int stepPos);


};

#endif // STARTING_POINT_H
