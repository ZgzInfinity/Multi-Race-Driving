
#include "../include/Soundtrack.h"



/**
* Constructor of the data type Soundtrack
* @param title is the name of the soundtrack
* @param vol is the level volume of the sound
* @param loop is a flag to control if the soundtrack is going to be reproduced in loop or not
*/
Soundtrack::Soundtrack(const string name, const int vol, const bool loop){
    title = name;
    volume = vol;
    inLoop = loop;
}



/**
* Get the name of the soundtrack
*/
string Soundtrack::getTitle(){
    return title;
}



/**
* Get the volume of the soundtrack
*/
int Soundtrack::getVolume(){
    return volume;
}



/**
* Check if the soundtrack is played in loop or not
*/
bool Soundtrack::isInLoop(){
    return inLoop;
}
