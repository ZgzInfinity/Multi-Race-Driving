
/*
 * ----------------------------------------------
 * Multi Race Driving: A general and customized
 * platform for 2.5D racing games
 * Author: ZgzInfinity
 * Date: 28-09-20
 * ----------------------------------------------
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <mutex>
#include <thread>

using namespace std;

extern mutex mainMutex, multiplayerMutex;

// Variables to control the connection to the Linda server
extern string domain, port;

#endif
