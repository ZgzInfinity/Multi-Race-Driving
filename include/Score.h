
#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Configuration.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"

using namespace std;
using namespace rapidxml;

/**
 * Representa un récord de puntuación (score), con el nombre del jugador (name) y su marca de tiempo.
 */
struct Score {
    unsigned long score;
    std::string name;
    int minutes;
    int secs;
    int cents_second;

    /**
     * Constructor por defecto.
     * @param score
     * @param name
     * @param minutes
     * @param secs
     * @param centsSecond
     */
    Score(unsigned long score, const std::string &name, int minutes, int secs, int centsSecond);
};

/**
 * Devuelve todos los récords de puntuación ordenados de mayor a menor puntuación, es decir, el mejor récord estará en
 * la posición 0. El tamaño del vector está comprendido entre 0 (no hay ningún récord) y 7 (hay 7 récords en las
 * posiciones 0 a 6).
 * @return
 */
std::vector<Score> getGlobalScores(Configuration& c, const int typeOfGame);

/**
 * Dados todos los récords de puntuación ordenados de mayor a menor puntuación y una puntuación score, devuelve la
 * posición del nuevo récord (0 a 6) o -1 si no es un nuevo récord.
 * @param globalScores
 * @param score
 * @return
 */
int isNewRecord(const std::vector<Score> &globalScores, unsigned long score);

/**
 * Dados todos los récords de puntuación ordenados de mayor a menor puntuación y un nuevo récord, añade el nuevo récord
 * de puntuación y devuelve true si ha sido almacenado con éxito y false en caso contrario.
 * @param globalScores
 * @param newRecord
 * @return
 */
bool saveNewRecord(const std::vector<Score> &globalScores, const Score &newRecord, const int typeOfGame, Configuration & c);

#endif //SCORE_H
