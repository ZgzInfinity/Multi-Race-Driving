
#ifndef INTERNAL_CURVE_H
#define INTERNAL_CURVE_H

#include <SFML/Graphics.hpp>

using namespace sf;


/*
 * Step data type
 */
struct IntervalCurve{

    // Attributes of the type of data

    // Starting position of the curves in the road
    int startCurvePosition;

    // Ending position of the curves in the road
    int finalCurvePosition;

    // Direction of the curve in the road
    float directionCurve;


    /**
     * Default constructor
     */
    IntervalCurve();



    /**
     * Constructor of the data type IntervalCurve
     * @return an instance of the data type InternalCurve
     */
    IntervalCurve(const int start, const int ending, const float direction);


};

#endif // INTERNAL_CURVE_H


