 /*
 * This file is part of Boreas.
 * Boreas is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Boreas is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Boreas.  If not, see <https://www.gnu.org/licenses/>.
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
 * Module Tuple interface file
 */

#ifndef TUPLE_H
#define TUPLE_H

#include <cstring>
#include <iostream>

using namespace std;



/**
 * Represents the mechanism to share the information
 * in multi player mode
 */
class Tuple{

    // Dimension of the tuple
    int length;

    // Static vector to store the components of the tuple
    string lindaTuple[6];


public:



    /**
     * Default constructor
     */
    Tuple();



    /**
     * Creates a tuple of one element
     * @param p1 is the first component of the tuple
     */
    Tuple(string p1);



    /**
     * Creates a tuple of two elements
     * @param p1 is the first component of the tuple
     * @param p2 is the second component of the tuple
     */
    Tuple(string p1, string p2);



    /**
     * Creates a tuple of three elements
     * @param p1 is the first component of the tuple
     * @param p2 is the second component of the tuple
     * @param p3 is the third component of the tuple
     */
    Tuple(string p1, string p2, string p3);



    /**
     * Creates a tuple of four elements
     * @param p1 is the first component of the tuple
     * @param p2 is the second component of the tuple
     * @param p3 is the third component of the tuple
     * @param p4 is the fourth component of the tuple
     */
    Tuple(string p1, string p2, string p3, string p4);



    /**
     * Creates a tuple of five elements
     * @param p1 is the first component of the tuple
     * @param p2 is the second component of the tuple
     * @param p3 is the third component of the tuple
     * @param p4 is the fourth component of the tuple
     * @param p5 is the fifth component of the tuple
     */
    Tuple(string p1, string p2, string p3, string p4, string p5);



    /**
     * Creates a tuple of six elements
     * @param p1 is the first component of the tuple
     * @param p2 is the second component of the tuple
     * @param p3 is the third component of the tuple
     * @param p4 is the fourth component of the tuple
     * @param p5 is the fifth component of the tuple
     * @param p6 is the sixth component of the tuple
     */
    Tuple(string p1, string p2, string p3, string p4, string p5, string p6);



    /**
     * Creates a tuple with a concrete dimension
     * @param dimension is the number of components of the tuple
     */
    Tuple(int dimension);



    /**
     * Convert a string formated tuple into a tuple
     * @param t is the string which represents the tuple
     */
    void from_string(string t);



    /**
     * Convert a tuple into a string representation
     * @return
     */
    string to_string();



    /**
     * Get the component of the tuple stored in a concrete position
     * @param index is the position of the element to get
     */
    string get(int index);



    /**
     * Assigns a value to a concrete component o the tuple
     * @param index is the position of the component to be assigned
     * @param field is the value which is going to be stored
     */
    void set(int index, string field);



    /**
     * Returns the dimension of the tuple
     * @return
     */
    int size();
};

#endif
