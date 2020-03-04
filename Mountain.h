
#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include <SFML/Graphics.hpp>

using namespace sf;


/*
 * Step data type
 */
struct Mountain{

    // Attributes of the type of data

    // Starting position of the mountain in the scene
    int startMountainPos;

    // Ending position of the mountain in the scene
    int finalMountainPos;

    // Pending of the mountain
    float atenuationMountain;

    // Height of the mountain
    int heightMountain;



   /**
     * Default constructor
     */
    Mountain();



    /**
     * Constructor of the data type Step
     * @return an instance of the data type Step
     */
    Mountain(const int start, const int ending, const float atenuation, const int height);



    /**
     * Compares to sprites to determine which is first in the order
     * @param line is the other step to be compared
     * @return true is the instance caller to the method is lower than <<line>>.
     *         Otherwise returns false
     */
    bool operator < (Mountain& m);


};

#endif // MOUNTAIN_H
