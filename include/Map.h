/******************************************************************************
 * @file    Map.hpp
 * @author  Andrés Gavín Murillo, 716358
 * @author  Rubén Rodríguez Esteban, 737215
 * @date    Marzo 2020
 * @coms    Videojuegos - OutRun
 ******************************************************************************/

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Menu.h"
#include "Step.h"

#define XINC 0.05f // x increment

/**
 * Mapa que contiene la textura del paisaje (bg) y la textura de los objetos que se irán mostrando a lo
 * largo del mapa (objects). Además cada objeto tendrá un coeficiente que indicará el porcentaje total del objeto con
 * el que se puede chocar empezando desde el centro [0, 1]. Esto es útil para objetos cuya base es menor a la copa.
 * El suelo está formado por un número limitado de rectángulos horizontales (lines) que tendrán dibujado el trozo de
 * carretera que les corresponda y objetos en los laterales.
 * Dependiendo de la posición de la cámara (posX, posY) el primer rectángulo visible será uno u otro y los objetos se
 * verán más grandes si están más cerca de la pantalla o más pequeños si están más lejos.
 */
class Map {

    private:

        // Background
        sf::Texture bg;

        // Objects
        std::vector<sf::Texture> objects;
        std::vector<float> hitCoeff;
        std::vector<Step> lines;

        // Colors
        Color roadColor[2], grassColor[2];

        // Camera
        float posX, posY;

        // Next map
        Map *next;

    public:



    float getPosX();



    float getPosY();



    /**
     * Devuelve Line n
     * @param n
     * @return
     */
    Step* getLine(int n);



    /**
     * Devuelve Line n
     * @param n
     * @return
     */
    Step getLine(int n) const;



    /**
     * Devuelve Line anterior a n
     * @param n
     * @return
     */
    Step* getPreviousLine(int n);



    /**
     * Devuelve Line anterior a n
     * @param n
     * @return
     */
    Step getPreviousLine(int n) const;

    /**
     * Añade un rectángulo al mapa. Actualiza z para una nueva línea.
     * @param x
     * @param y
     * @param z
     * @param curve
     * @param mainColor
     * @param spriteLeft
     * @param spriteRight
     */
    void addLine(float x, float y, float &z, float prevY, float curve, bool mainColor, const Step::SpriteInfo &spriteLeft,
            const Step::SpriteInfo &spriteRight);

    /**
     * Añade rectángulos desde las instrucciones al mapa desde (x, y, z). Actualiza z para una nueva línea.
     * @param x
     * @param y
     * @param z
     * @param instructions
     */
    void addLines(float x, float y, float &z, const std::vector<std::vector<std::string>> &instructions);

public:

    // Crea un mapa con un paisaje dado el nombre del fichero de la imagen y con unos objetos dados los nombres de los
    // ficheros de las imágenes. El contenido del mapa debe encontrarse en la ruta path. Si random es true se crea el
    // mapa de manera aleatoria, en cambio si random es false se crea el mapa a partir del fichero map.info, que se
    // describe a continuación:
    //      - Se pueden incluir comentarios en cualquier parte, comenzando por /* y terminando por */
    //      - En primer lugar se deben indicar los dos colores de la carretera y los dos del suelo, en RGB y separados
    //        por espacios.
    //      - En segundo lugar se indica el recorrido con objetos, curvas y elevaciones.
    //      - Se pueden incluir fragmentos aleatorios de la iguiente manera:
    //          RANDOM n o_1 o_2 ... o_x
    //        Donde n indica el número de fragmentos y o_i indica el índice del objeto que puede contener(#.png). Por
    //        defecto no hay objeto.
    //      - Finalmente para indicar el final del mapa se debe incluir END.
    //      - Ejemplo de fichero:
    //
    //          /* Mapa 1 */
    //
    //          107 107 107  /* Road RGB color 1 */
    //          105 105 105  /* Road RGB color 2 */
    //           16 200  16  /* Grass RGB color 1 */
    //            0 154   0  /* Grass RGB color 2 */
    //
    //          /*
    //           * ROAD:
    //           *   1º Opcional: +   ;Indica que es un objeto repetido infinitamente hacia la izquierda. Por defecto no se repite.
    //           *   2º Opcional: #   ;Indica el índice del objeto colocado a la izquierda de la carretera (#.png). Por defecto no hay objeto.
    //           *   3º Opcional: #.# ;Indica el offset desde el borde de la carretera hasta el objeto. Por defecto es 0.0.
    //           *   4º Obligado: -   ;Representa la carretera
    //           *   5º Opcional: +   ;Indica que es un objeto repetido infinitamente hacia la derecha. Por defecto no se repite.
    //           *   6º Opcional: #   ;Indica el índice del objeto colocado a la derecha de la carretera (#.png). Por defecto no hay objeto.
    //           *   7º Opcional: #.# ;Indica el offset desde el borde de la carretera hasta el objeto. Por defecto es 0.0.
    //           */
    //          ROAD           -
    //          ROAD     5     -
    //          CURVE 0.5  /* Curva con índice comprendido entre -0.9 y 0.9, negativo si es hacia la izquierda y positivo si es hacia la derecha */
    //          ROAD           -   5
    //          ROAD     5 0.0 -   5 2.0
    //          STRAIGHT  /* Recta */
    //          ROAD   + 5     -
    //          CLIMB 1.0  /* Subida con índice comprendido entre 0.0 y MAX_FLOAT */
    //          ROAD           - + 5 -1.0
    //          FLAT  /* Llano, sin subidas ni bajadas */
    //          ROAD       -
    //          ROAD       -
    //          RANDOM 10 5 4  /* Añade 10 fragmentos aleatorios que pueden contenrr los objetos 5 y 4 */
    //          ROAD       -
    //          ROAD       -
    //          ROAD       -
    //          DROP 1.0  /* Bajada con índice comprendido entre 0.0 y MAX_FLOAT */
    //          ROAD       -
    //          ROAD       -
    //          END  /* Obligatorio */
    //
    /**
     * @param c
     * @param path
     * @param bgName
     * @param objectNames
     * @param random
     */
    Map(const std::string &path, const std::string &bgName, const std::vector<std::string> &objectNames, bool random);

    /**
     * Añade un mapa a continuación del actual.
     * @param map
     */
    void addNextMap(Map *map);

    /**
     * Añade el offset al mapa.
     * @param yOffset
     */
    void setOffset(float yOffset);

    /**
     * Establece la posición de la cámara.
     * @param pos = {x, y}, donde x = 0 es el medio de la carretera, y >= 0 AND y <= MAXLINES
     */
    void updateView(std::pair<float, float> pos);


    /**
     * Dibuja el fragmento del mapa actual dada la posición de la cámara establecida con la función updateView().
     * @param c
     */
    void draw(RenderWindow* app, Configuration* c);


    /**
     * Devuelve true si currentX está fuera de la carretera.
     * @param currentX
     * @return
     */
    bool hasGotOut(float currentX) const;

    /**
     * Devuelve el coeficiente de curvatura correspondiente al rectángulo currentY. El coeficiente es positivo si la
     * curva es hacia la derecha, negativo si es hacia la izquierda y 0 si es una recta.
     * @param currentY
     * @return coeff pertenece [-0.9, 0.9]
     */
    float getCurveCoefficient(float currentY) const;

    /**
     * Devuelve la elevación correspondiente al rectángulo currentY en base al rectángulo previo.
     * @param currentY
     * @return
     */
    Elevation getElevation(float currentY) const;

    /**
     * Devuelve cierto si se ha alcanzado el final del mapa
     * @return
     */
    bool isOver() const;
};


#endif // MAP_H
