
#include "../include/Mountain.h"


/**
 * Default constructor
 */
Mountain::Mountain(){}



/**
 * Constructor of the data type Step
 * @return an instance of the data type Step
 */
Mountain::Mountain(const int start, const int ending, const float atenuation, const int height){
    // Assignment of the parameters
    startMountainPos = start;
    finalMountainPos = ending;
    atenuationMountain = atenuation;
    heightMountain = height;
}



/**
 * Compares to sprites to determine which is first in the order
 * @param line is the other step to be compared
 * @return true is the instance caller to the method is lower than <<line>>.
 *         Otherwise returns false
 */
bool Mountain::operator < (Mountain& m){
    // Returns which is lower
    return this->startMountainPos <= m.startMountainPos && this->finalMountainPos <= m.finalMountainPos;
}
