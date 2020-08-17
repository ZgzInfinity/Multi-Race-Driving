#pragma once

/*
 * Module MapElement interface file
 */

#ifndef MAP_ELEMENT_H
#define MAP_ELEMENT_H



/**
 * Represents the visible elements of the landscapes
 */
struct MapElement {

    // Numeric identifier of the element in the landscape
    int codeMapElement;

    // Distance to the road
    float offset;

    // Minimum distance to detect a collision
    float spriteMinX;

    // Maximum distance to detect a collision
    float spriteMaxX;

    // Space from spriteMinX to another minX side
    float spriteToSideX;



    /**
     * Default constructor
     */
    MapElement();

};

#endif // MAP_ELEMENT_H
