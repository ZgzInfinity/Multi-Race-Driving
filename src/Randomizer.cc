
#include "../include/Randomizer.h"


static thread_local random_device rd;
static thread_local std::mt19937 generator(rd());
static thread_local uniform_real_distribution<float> dist(0.0f, 1.0f);


/**
 * Returns a random number between zero and one
 * @return
 */
float rand_generator_zero_one() {
    return dist(generator);
}



/**
 * Returns a random number between zero and n
 * @param n is the upper bound number to generate the random number
 * @return
 */
int rando_generator_zero_n(int n) {
    return uniform_int_distribution<>(0, n)(generator);
}



/**
 * Returns a integer random number between a lower bound and an upper bound numbers
 * @param lower is the lower bound number of the interval
 * @param upper is the upper bound number of the interval
 * @return
 */
int rand_generator_int(int lower, int upper) {
    return uniform_int_distribution<int>(lower, upper)(generator);
}



/**
 * Returns a float random number between a lower bound and an upper bound numbers
 * @param lower is the lower bound number of the interval
 * @param upper is the upper bound number of the interval
 * @return
 */
float rand_generator_float(float lower, float upper) {
    return uniform_real_distribution<float>(lower, upper)(generator);
}

