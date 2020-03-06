

#include "../include/Checkpoint.h"


/**
 * Default constructor
 */
Checkpoint::Checkpoint(){};



/**
 * Constructor of the data type Checkpoint
 * @return an instance of the data type Checkpoint
 */
Checkpoint::Checkpoint(const string pathFile, const float positionX, const int stepPos){
    path = pathFile;
    posX = positionX;
    stepPosition = stepPos;
}



/**
 * Compares to sprites to determine which is first in the order
 * @param c is the other checkpoint with the instance caller is going to be compared
 * @return true is the instance caller to the method is lower than <<c>>.
 *         Otherwise returns false
 */
bool Checkpoint::operator < (Checkpoint& c){
    return this->stepPosition <= c.stepPosition;
}


