#pragma once

#ifndef KEYWORD_MAPPER_H
#define KEYWORD_MAPPER_H

#include <iostream>
#include <SFML/Graphics.hpp>

const int KEYWORDS_MAPPED = 75;

using namespace std;
using namespace sf;

struct KeywordMapper {
    // Maps of the keywords available in the game
    sf::Keyboard::Key mapperCodeKeyWord[KEYWORDS_MAPPED];
    string mapperIdKeyWord[KEYWORDS_MAPPED];

    /**
     * Constructor por defecto.
     */
    KeywordMapper();

    int lookForKeyBoard(const string key);

    int lookForKeyBoardId(const Keyboard::Key key);
};

#endif // KEYWORD_MAPPER_H
