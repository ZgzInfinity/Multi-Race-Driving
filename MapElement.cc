
#include "MapElement.h"


/**
 * Default constructor
 */
MapElement::MapElement(){}



/**
 * Constructor of the data type Step
 * @return an instance of the data type Step
 */
MapElement::MapElement(const int identifier, const int start, const int ending,
                       const float frequency, const float pos_axisX)
{
    // Assignment of the parameters
    id = identifier;
    startPosition = start;
    finalPosition = ending;
    each = frequency;
    xPos = pos_axisX;

}



/**
 * Compares to sprites to determine which is first in the order
 * @param line is the other step to be compared
 * @return true is the instance caller to the method is lower than <<line>>.
 *         Otherwise returns false
 */
bool MapElement::operator < (MapElement& m){
    // Returns which is lower
    return this->startPosition <= m.startPosition && this->finalPosition <= m.finalPosition;
}

