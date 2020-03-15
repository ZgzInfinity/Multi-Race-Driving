
#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <cstring>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


/*
 * Step data type
 */
struct Checkpoint{

    // Starting position of the curves in the road
    string path;

    // Ending position of the curves in the road
    float posX;

    // Direction of the curve in the road
    int stepPosition;

    // Offset to control the collision with the player
    float offset;


    /**
     * Default constructor
     */
    Checkpoint();



    /**
     * Constructor of the data type Checkpoint
     * @param pathFile is the path that contains the file with the image of the checkpoint
     * @param positionX is the position in the axis X of the checkpoint
     * @param stepPos is the step of the map where the checkpoint is going to be stored
     * @return an instance of the data type Checkpoint
     */
    Checkpoint(const string pathFile, const float positionX, const int stepPos);



    /**
     * Compares to sprites to determine which is first in the order
     * @param line is the other step to be compared
     * @return true is the instance caller to the method is lower than <<line>>.
     *         Otherwise returns false
     */
     bool operator < (Checkpoint& c);

};

#endif // CHECKPOINT_H
