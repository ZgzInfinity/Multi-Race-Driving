
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
