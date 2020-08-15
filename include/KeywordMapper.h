
/*
 * Module KeywordMapper interface file
 */


#pragma once

#ifndef KEYWORD_MAPPER_H
#define KEYWORD_MAPPER_H

#include <iostream>
#include <SFML/Graphics.hpp>

const int KEYWORDS_MAPPED = 75;

using namespace std;
using namespace sf;



/**
 * Represents the association between the numeric codes of
 * the keywords and their names
 */
struct KeywordMapper {

    // Maps of the keywords available in the game
    sf::Keyboard::Key mapperCodeKeyWord[KEYWORDS_MAPPED];

    // Names of the keywords
    string mapperIdKeyWord[KEYWORDS_MAPPED];



    /**
     * Constructor por defecto.
     */
    KeywordMapper();



    /**
     * Returns the numeric code of key identified by its name
     * if it exists. Otherwise returns a negative number
     * @param key is a key identified by its name
     */
    int lookForKeyBoard(const string key);



    /**
     * Returns the numeric code of key identified by its name
     * if it exists. Otherwise returns a negative number
     * @param key is a key identified by its name
     */
    int lookForKeyBoardId(const Keyboard::Key key);

};

#endif // KEYWORD_MAPPER_H
