
#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <cstring>
#include <SFML/Graphics.hpp>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace sf;


/*
 * SoundEffect data type
 */
class SoundEffect{

    private:

        // Title of the soundtrack
        string title;

    public:


        /**
         * Constructor of the data type Soundtrack
         * @param title is the name of the soundtrack
         */
        SoundEffect(const string name);



        /**
         * Get the name of the soundtrack
         */
        string getTitle();


};

#endif // SOUNDEFFECT_H
