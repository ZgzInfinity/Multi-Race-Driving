
#ifndef MAP_ELEMENT_H
#define MAP_ELEMENT_H

#include <cstring>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


/*
 * Step data type
 */
struct MapElement{

    // Attributes of the type of data

    // Identifier of the element
    int id;

    // Starting position of the curves in the road
    int startPosition;

    // Ending position of the curves in the road
    int finalPosition;

    // Path of the map element
    string path;

    // Frequency of appearance
    int each;

    // Position in axis X
    float xPos;


    /**
     * Default constructor
     */
    MapElement();



    /**
     * Constructor of the data type IntervalCurve
     * @return an instance of the data type InternalCurve
     */
    MapElement(const int identifier, const int start, const int ending,
               const float frequency, const float pos_axisX);




    /**
     * Compares to sprites to determine which is first in the order
     * @param line is the other step to be compared
     * @return true is the instance caller to the method is lower than <<line>>.
     *         Otherwise returns false
     */
     bool operator < (MapElement& iC);


};

#endif // INTERNAL_CURVE_H
