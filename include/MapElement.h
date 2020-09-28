/*
 * Copyright (c) 2020 Rubén Rodríguez
 *
 * This file is part of Multi Race Driving.
 * Multi Race Driving is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Multi Race Driving is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Multi Race Driving.  If not, see <https://www.gnu.org/licenses/>.
 */



/*
 * ----------------------------------------------
 * Multi Race Driving: A general and customized
 * platform for 2.5D racing games
 * Author: ZgzInfinity
 * Date: 28-09-20
 * ----------------------------------------------
 */



/*
 * Module MapElement interface file
 */

#pragma once

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
