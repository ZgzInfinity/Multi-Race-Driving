
#include "../include/SoundEffect.h"



/**
* Constructor of the data type Soundtrack
* @param title is the name of the soundtrack
*/
SoundEffect::SoundEffect(const string name){
    title = name;
}



/**
* Get the name of the soundtrack
*/
string SoundEffect::getTitle(){
    return title;
}
