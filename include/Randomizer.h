/*
 * Copyright (c) 2020 Andrés Gavín
 * Copyright (c) 2020 Rubén Rodríguez
 *
 * This file is part of Out Run.
 * Out Run is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Out Run is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Out Run.  If not, see <https://www.gnu.org/licenses/>.
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
 * Module Randomizer implementation file
 */

#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <random>

using namespace std;



/**
 * Returns a random number between zero and one
 * @return
 */
float rand_generator_zero_one();



/**
 * Returns a random number between zero and n
 * @param n is the upper bound number to generate the random number
 * @return
 */
int rando_generator_zero_n(int n);



/**
 * Returns a integer random number between a lower bound and an upper bound numbers
 * @param lower is the lower bound number of the interval
  * @param upper is the upper bound number of the interval
 * @return
 */
int rand_generator_int(int lower, int upper);



/**
 * Returns a float random number between a lower bound and an upper bound numbers
 * @param lower is the lower bound number of the interval
 * @param upper is the upper bound number of the interval
 * @return
 */
float rand_generator_float(float lower, float upper);

#endif //RANDOMIZER_H
