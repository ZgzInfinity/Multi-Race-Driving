
#include "IntervalCurve.h"


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


