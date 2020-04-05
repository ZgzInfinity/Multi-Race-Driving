
#ifndef SOUNDTRACK_H
#define SOUNDTRACK_H

#include <cstring>
#include <SFML/Graphics.hpp>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace sf;


/*
 * Soundtrack data type
 */
class Soundtrack{

    private:

        // Title of the soundtrack
        string title;

        // Volume level to reproduce the soundtrack
        int volume;

        //  Control if the soundtrack is going to be reproduced in loop or not
        bool inLoop;


    public:


        /**
         * Constructor of the data type Soundtrack
         * @param title is the name of the soundtrack
         * @param vol is the level volume of the sound
         * @param loop is a flag to control if the soundtrack is going to be reproduced in loop or not
         */
        Soundtrack(const string name, const int vol, const bool loop);



        /**
         * Get the name of the soundtrack
         */
         string getTitle();



        /**
         * Get the volume of the soundtrack
         */
         int getVolume();



         /**
         * Check if the soundtrack is played in loop or not
         */
         bool isInLoop();

};

#endif // SOUNDTRACK_H
