
/*
 * ----------------------------------------------
 * Multi Race Driving: A general and customized
 * platform for 2.5D racing games
 * Author: ZgzInfinity
 * Date: 28-09-20
 * ----------------------------------------------
 */



/*
 * Module Step implementation file
 */


#include "../include/Step.h"


/**
 * Default constructor
 */
Step::Step() {
    // Assignment of the attributes
    directionCurve = 0.0f;
    position_3d_x = 0.0f;
    position_3d_y = 0.0f;
    position_3d_z = 0.0f;
    offsetX = 0.0f;
    yOffsetX = 0.0f;
    bgX = 0.0f;
    mainColor = false;
}
