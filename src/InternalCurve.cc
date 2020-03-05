
#include "../include/IntervalCurve.h"


/**
 * Default constructor
 */
IntervalCurve:: IntervalCurve(){}



/**
 * Constructor of the data type Step
 * @return an instance of the data type Step
 */
IntervalCurve::IntervalCurve(const int start, const int ending, const float direction){
    // Assignment of the parameters
    startCurvePosition = start;
    finalCurvePosition = ending;
    directionCurve = direction;
}



/**
 * Compares to sprites to determine which is first in the order
 * @param line is the other step to be compared
 * @return true is the instance caller to the method is lower than <<line>>.
 *         Otherwise returns false
 */
bool IntervalCurve::operator < (IntervalCurve& iC){
    // Returns which is lower
    return this->startCurvePosition <= iC.startCurvePosition && this->finalCurvePosition <= iC.finalCurvePosition;
}
