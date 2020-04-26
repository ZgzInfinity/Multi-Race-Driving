
#ifndef LAND_SCAPE_H
#define LAND_SCAPE_H


#include <vector>
#include <iostream>
#include <cstring>
#include <chrono>
#include "Step.h"
#include "Configuration.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace sf;
using namespace rapidxml;

const int MAX_ELEMENTS = 20;


#define BGS 0.525F // Background size
#define ROADW 2000 // Road Width
#define RUMBLECOEFF 0.1f // Ruble size = Road size * Rumble coeff
#define M_PI 3.1415926535897932384


struct LandScape {

        // Texture of the background
        Texture bg;

        // Objects
        vector<sf::Texture> objects;
        vector<float> hitCoeff;
        vector<Step> newLines;

        // Colors
        vector<Color> roadColor;
        vector<Color> grassColor;
        vector<Color> rumbleColor;

        // Camera
        float posX, posY;

        // Next map
        LandScape *next;


        /**
         * @param c
         * @param path
         * @param bgName
         * @param objectNames
         * @param random
         */
        LandScape(const std::string path, bool random);



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
        void addLine(float x, float y, float &z, float prevY, float curve, bool mainColor, Step::SpriteInfo &spriteNearLeft,
                     Step::SpriteInfo &spriteNearRight, Step::SpriteInfo &spriteFarLeft, Step::SpriteInfo &spriteFarRight,
                     int& stepsRead, int& eachNearLeft, int& eachNearRight, int& eachFarLeft, int&eachFarRight, const int startPos,
                     int& codeNearLeft, int& codeNearRight, int& codeFarLeft, int& codeFarRight, bool& generateRandomNearLeft,
                     bool& generateRandomNearRight, bool& generateRandomFarLeft, bool& generateRandomFarRight, float& startPointOffset,
                     int& startingPointPos, int& codeStartPoint, bool& startPointDrawn, float& leftOffset, float& checkPointOffset,
                     int& checkPointPos, int& codeCheckPoint, bool& checkPointDrawn, float& goalPointOffset, int& goalPointPos,
                     int& codeGoalPoint, bool& goalPointDrawn);


        void parseBackgroundScene(string pathFile);


        void processRoadPart(xml_node<> * child, float& curveCoeff, float& elevation, bool& mainColor,
                             int elevationIndex, int& elevationLines, bool flatTerrain, float& cordX,
                             float& cordY, float& cordZ);


        /**
         * Añade un mapa a continuación del actual.
         * @param map
         */
        void addNextMap(LandScape *map);

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


        /**
         * Parses all the configuration of the background written in the xml
         * configuration file of the scene
         * @param child is a node of the xml file that points to the background information
         */
        inline void parseBackgroundScene(xml_node<> * child);


        /**
         * Get the interval coordinates of any element of the scene
         * @param child is a pointer to the xml fils that points to a curve, mountain or sprite
         * @param objectCode controls what kind of element is been processed
         * @param startPos is going to store the initial interval position of the element of the scene
         * @param finalPos is going to store the initial interval position of the element of the scene
         */
        inline void getIntervalCoordinates(xml_node<> *child, int objectCode, int& startPos, int& finalPos);



        /**
         * Parses all the configuration of the colors of the grass, the rumble of the road and the middle of the road
         * configuration file of the scene
         * @param child is a node of the xml file that points to the color of the middle of the road information
         * @param colorRed is where is going to be stored the value of the red channel in RGB color space read from the file
         * @param colorGreen is where is going to be stored the value of the green channel in RGB color space read from the file
         * @param colorBlue is where is going to be stored the value of the blue channel in RGB color space read from the file
         */
        inline void parseColors(xml_node<> * child, int& colorRed, int& colorGreen, int& colorBlue);




        inline void parseColorGrassRoadScene(xml_node<> * child);

};

#endif // LAND_SCAPE_H
