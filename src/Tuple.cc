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
 * Module Tuple implementation file
 */

#include <sstream>
#include "../include/Tuple.h"

using namespace std;



/**
 * Default constructor
 */
Tuple::Tuple(){}



/**
 * Creates a tuple of one element
 * @param p1 is the first component of the tuple
 */
Tuple::Tuple(string p1){
    length = 1;
    lindaTuple[0] = p1;
};



/**
 * Creates a tuple of two elements
 * @param p1 is the first component of the tuple
 * @param p2 is the second component of the tuple
 */
Tuple::Tuple(string p1, string p2){
    length = 2;
    lindaTuple[0] = p1;
    lindaTuple[1] = p2;
};



/**
 * Creates a tuple of three elements
 * @param p1 is the first component of the tuple
 * @param p2 is the second component of the tuple
 * @param p3 is the third component of the tuple
 */
Tuple::Tuple(string p1, string p2, string p3){
    length = 3;
    lindaTuple[0] = p1;
    lindaTuple[1] = p2;
    lindaTuple[2] = p3;
};



/**
 * Creates a tuple of four elements
 * @param p1 is the first component of the tuple
 * @param p2 is the second component of the tuple
 * @param p3 is the third component of the tuple
 * @param p4 is the fourth component of the tuple
 */
Tuple::Tuple(string p1, string p2, string p3, string p4){
    length = 4;
    lindaTuple[0] = p1;
    lindaTuple[1] = p2;
    lindaTuple[2] = p3;
    lindaTuple[3] = p4;
};



/**
 * Creates a tuple of five elements
 * @param p1 is the first component of the tuple
 * @param p2 is the second component of the tuple
 * @param p3 is the third component of the tuple
 * @param p4 is the fourth component of the tuple
 * @param p5 is the fifth component of the tuple
 */
Tuple::Tuple(string p1, string p2, string p3, string p4, string p5){
    length = 5;
    lindaTuple[0] = p1;
    lindaTuple[1] = p2;
    lindaTuple[2] = p3;
    lindaTuple[3] = p4;
    lindaTuple[4] = p5;
};



/**
 * Creates a tuple of six elements
 * @param p1 is the first component of the tuple
 * @param p2 is the second component of the tuple
 * @param p3 is the third component of the tuple
 * @param p4 is the fourth component of the tuple
 * @param p5 is the fifth component of the tuple
 * @param p6 is the sixth component of the tuple
 */
Tuple::Tuple(string p1, string p2, string p3, string p4, string p5, string p6){
    length = 6;
    lindaTuple[0] = p1;
    lindaTuple[1] = p2;
    lindaTuple[2] = p3;
    lindaTuple[3] = p4;
    lindaTuple[4] = p5;
    lindaTuple[5] = p6;
};


/**
 * Creates a tuple with a concrete dimension
 * @param dimension is the number of components of the tuple
 */
Tuple::Tuple(int dimension){
    length = dimension;
};



/**
 * Convert a string formated tuple into a tuple
 * @param t is the string which represents the tuple
 */
void Tuple::from_string(string t){
    // Creation of a string flux
    stringstream ss(t);

    // Control if the format of the tuple is correct
    bool incorrect = false;

    // Store the dimension of the tuple
    int i = length;

    // Get the first element of the tuple
    if(ss.get() == '[')
    {
        // The tuple has the correct format
        string token;
        while(i > 1)
        {
            // Get all the characters until the comma
            getline(ss, token, ',');

            // Insertion of the new component in its correct position
            lindaTuple[length - i] = token;

            // Decrement the number of components to process
            i--;
        }

        // Get the final component of the tuple and store it
        getline(ss, token, ']');
        lindaTuple[length - 1] = token;

    }
    else {
        // Incorrect format of the tuple
        incorrect = true;
    }
};



/**
 * Convert a tuple into a string representation
 * @return
 */
string Tuple::to_string(){
    // Representation of the tuple like a string
    string chain = "[";

    // Iteration throughout the components of the tuple
    for(int i = 0; i < length - 1; i++)
    {
        // Concatenate a new component to the chain
        chain = chain + lindaTuple[i] + ",";
    }
    // Add the final element of the tuple
    chain = chain + lindaTuple[length - 1] + "]";
    return chain;
};



/**
 * Get the component of the tuple stored in a concrete position
 * @param index is the position of the element to get
 */
string Tuple::get(int index){
    return lindaTuple[index - 1];
};



/**
 * Assigns a value to a concrete component o the tuple
 * @param index is the position of the component to be assigned
 * @param field is the value which is going to be stored
 */
void Tuple::set(int index, string field){
    lindaTuple[index - 1] = field;
};



/**
 * Returns the dimension of the tuple
 * @return
 */
int Tuple::size(){
    return length;
};
