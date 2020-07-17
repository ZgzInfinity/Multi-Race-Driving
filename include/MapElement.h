#pragma once

/*
 * Module MapElement interface file
 */

#ifndef MAP_ELEMENT_H
#define MAP_ELEMENT_H


struct MapElement {
    int codeMapElement;
    float offset, spriteMinX, spriteMaxX, spriteToSideX; // spriteToSideX is the space from spriteMinX to another minX side


    /**
     * Default constructor
     */
    MapElement();
};

#endif // MAP_ELEMENT_H
