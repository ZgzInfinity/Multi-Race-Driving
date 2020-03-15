
#ifndef STARTING_POINT_H
#define STARTING_POINT_H

#include <cstring>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


/*
 * Step data type
 */
struct StartingPoint{

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
     StartingPoint();



    /**
     * Constructor of the data type StartingPoint
     * @param pathFile is the path that contains the file with the image of the starting point
     * @param positionX is the position in the axis X of the starting point
     * @param stepPos is the step of the map where the starting point is going to be stored
     * @return an instance of the data type StartingPoint
     */
    StartingPoint(const string pathFile, const float positionX, const int stepPos);


};

#endif // STARTING_POINT_H

