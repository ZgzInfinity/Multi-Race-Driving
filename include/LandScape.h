
#ifndef LAND_SCAPE_H
#define LAND_SCAPE_H


#include <vector>
#include <iostream>
#include <cstring>
#include "Step.h"
#include "IntervalCurve.h"
#include "Mountain.h"
#include "MapElement.h"
#include "Checkpoint.h"
#include "StartingPoint.h"
#include "GoalPoint.h"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace std;
using namespace sf;
using namespace rapidxml;

const int MAX_ELEMENTS = 20;



struct LandScape {

        // Vector of Steps of the scene where there are sprites accessed by children classes
        vector<Step> stepsWithSprite;

        // Vector of interval of curves of the scene
        vector<IntervalCurve> curvesInScene;

        // Vector of interval of curves of the scene
        vector<IntervalCurve> curves;

        // Vector of mountains of the the scene
        vector<Mountain> mountains;

        // Vector with the paths of the sprites
        vector<string> spritePaths;

        // Texture of the background
        Texture bg;

        // Sprite where the image of the background is going to be loaded
        Sprite sBackground;

        // Name of the circuit
        string name;

        // Texture and sprite vectors
        Texture t[MAX_ELEMENTS];
        Sprite object[MAX_ELEMENTS];

        // Colors to represent the road
        vector<Color> colors_grass;

        // Colors to represent the rumble
        vector<Color> colors_rumble;

        // Colors to represent the middle of the road
        vector<Color> colors_middle;

        // Unique color of the road
        Color color_road;

        // Elements of the map
        vector<MapElement> elementsOfMap;

        // Vector of textures loaded
        vector<bool>textures = vector<bool>(MAX_ELEMENTS);

        // Vector of steps to do
        vector<Step> lines = vector<Step>(MAX_SPACE_DIMENSION);

        // Vector of the checkpoints of the scene
        vector<Checkpoint> checkpointsScene;

        // Texture of the checkpoint
        Texture tCheckpoint;

        // Starting position point of the scene
        StartingPoint startPoint;

        // Texture of the starting point
        Texture tStartingPoint;

        // Starting position point of the scene
        GoalPoint goalPoint;

        // Texture of the starting point
        Texture tGoalPoint;


        /**
         * Constructor of the data type
         * @param path is the path of the xml file which contains the scene to render
         */
        LandScape(char* path);



        /**
         * Get the sprite which contains the background
         */
        Sprite getBackGround();



        /**
         * Assigns the sprite of the background
         * @param sBack is the sprite which contains the background to assign
         */
        void setBackGround(Sprite sBack);



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
         * Parses all the information referent to the sprites of the landscape
         * @param child is a pointer to a node of the xml file that contains the all the
         * information of the sprites
         */
        inline void parseSpritesScene(xml_node<> * child);



        /**
         * Parses all the configuration of the curves written in the xml configuration file of the scene
         * @param child is a node of the xml file that points to the curves information
         */
        inline void parseCurvesScene(xml_node<> * child);



        /**
         * Parses all the configuration of the mountains written in the xml configuration file of the scene
         * @param child is a node of the xml file that points to the mountains information
         */
        inline void parseMountainsScene(xml_node<> * child);



        /**
         * Parses the configuration of the checkpoints of the scene which stored in its configuration file
         * @param child is a node of the xml file that points to the mountains information
         * @param path is the relative path of the image that contains the image of the checkpoint
         */
        inline void parseCheckpoints(xml_node<> * child);



        /**
         * Parses the information referent to the goal point of the scene
         * @param child is a node pointer of the xml configuration file that points to the
         * data of the goal point
         */
        inline void parseGoalPoint(xml_node<> * child);



        /**
         * Parses the information referent to the starting point of the scene
         * @param child is a node pointer of the xml configuration file that points to the
         * data of the starting point
         */
        inline void parseStartPoint(xml_node<> * child);



        /**
         * Parses all the configuration of the color of the road written in the xml
         * configuration file of the scene
         * @param child is a node of the xml file that points to the color of the road information
         */
        inline void parseColorRoadScene(xml_node<> * child);



        /**
         * Parses all the configuration of the colors of the grass, the rumble of the road and the middle of the road
         * configuration file of the scene
         * @param child is a node of the xml file that points to the color of the middle of the road information
         * @param colorRed is where is going to be stored the value of the red channel in RGB color space read from the file
         * @param colorGreen is where is going to be stored the value of the green channel in RGB color space read from the file
         * @param colorBlue is where is going to be stored the value of the blue channel in RGB color space read from the file
         */
        inline void parseColors(xml_node<> * child, int& colorRed, int& colorGreen, int& colorBlue);



        /**
         * Parses all the configuration of the color of the road written in the xml
         * configuration file of the scene
         * @param child is a node of the xml file that points to the color of the grass information
         */
        inline void parseColorGrassScene(xml_node<> * child);



        /**
         * Parses all the configuration of the color of the rumble of the road written in the xml
         * configuration file of the scene
         * @param child is a node of the xml file that points to the color of the rumble of road information
         */
        inline void parseColorRumbleScene(xml_node<> * child);



        /**
         * Parses all the configuration of the color of the middle of the road written in the xml
         * configuration file of the scene
         * @param child is a node of the xml file that points to the color of the middle of the road information
         */
        inline void parseColorMiddleScene(xml_node<> * child);



        /**
         * Renders all the landscape with all the elements already parsed and stored
         */
        inline void renderLandScape();



        /**
         * Load the background of the landscape
         */
        inline void loadBackground(const string path, const int lowerLeft, const int upperLeft,
                                   const int lowerRight, const int upperRight, const int x_center,
                                   const int y_center);



        /**
         * Get the element of the map which the nearest to the actual position
         * @param position_axis_Y is the actual coordinate of the player in the axis Y
         */
        Step checkingPossibleCollision(const int position_axis_Y);



        /**
         * Determines if there is a curve to print or not in the position of the map pos
         * @param pos is the position of the map to evaluate if there is a curve or not
         * @param curve is the possible curve in which interval of coordinates is located pos
         * @param exists is a boolean to control if there is curve to print or not in the position of the map pos
         */
        void lookForCurveToPrint(int& pos, IntervalCurve& curve, bool& exist);



        /**
         * Determines if there is a curve or not in the position of the map pos
         * @param pos is the position of the map to evaluate if there is a curve or not
         * @param curve is the possible curve in which interval of coordinates is located pos
         * @param exists is a boolean to control if there is curve or not in the position of the map pos
         */
        void lookForCurve(int& pos, IntervalCurve& curve, bool& exist);



        /**
         * Determines if there is a mountain or not in the position of the map pos
         * @param pos is the position of the map to evaluate if there is a mountain or not
         * @param m is the possible mountain in which interval of coordinates is located pos
         * @param exists is a boolean to control if there is mountain or not in the position of the map pos
         */
        void lookForMountain(int& pos, Mountain& m, bool& exist);



        /**
         * Determines if there is a mountain or not in the position of the map pos
         * @param m is a vector where all the possible sprites to print are going to be kept
         * @param exists is a boolean to control if there are sprites or not in the position of the map pos
         */
        void lookForMapElement(int& pos, vector<MapElement>& m, bool& exist);



        /**
         * Determines if there is checkpoint or not in the actual step of the map
         * @param step is the actual step of the map where is going to be evaluated if there
         * is or not checkpoint
         * @param c is the possible checkpoint that can be in the actual step of the map
         * @param exists is a boolean that controls if there is or not a checkpoint in the actual step
         */
        void lookForCheckpoint(int& step, Checkpoint& c, bool& exists);



        /**
         * Order the curves and the mountains of the map using the coordinates of the map X and Y
         */
        void orderElementsInLandScape();



        /**
         * Print the possible curve of the map which can be stored in the position of the map i
         * @param i is the step or position index of the map where is going to be evaluated if
         * there is or not curve
         */
        void printCurves(int i);



        /**
         * Print the possible mountain of the map which can be stored in the position of the map i
         * @param i is the step or position index of the map where is going to be evaluated if
         * there is or not mountain
         */
        void printMountains(int i);



        /**
         * Print the possible sprite of the map which can be stored in the position of the map i
         * @param i is the step or position index of the map where is going to be evaluated if
         * there is or not sprite
         */
        void printSprites(int i);



        /**
         * Print the possible checkpoint of the map which can be stored in the position of the map i
         * @param i is the step or position index of the map where is going to be evaluated if
         * there is or not a checkpoint
         */
        void printCheckpoints(int i);



        /**
         * Print the possible starting point of the map which can be stored in the position of the map i
         * @param i is the step or position index of the map where is going to be evaluated if
         * there is or not a starting point
         */
        void printStartingPoints(int i);



        /**
         * Print the possible goal point of the map which can be stored in the position of the map i
         * @param i is the step or position index of the map where is going to be evaluated if
         * there is or not a goal point
         */
        void printGoalPoints(int i);



        /**
         * Render the landscape appearance and the step of the map
         * @param n is the index of the map position to be processed
         * @param grass is the color which is going to be used to paint the grass of the scene
         * @param rumble is the color which is going to be used to paint the rumble of the scene
         * @param middle is the color which is going to be used to paint the middle road of the scene
         * @param road is the color which is going to be used to paint the road of the scene
         */
        void paintScene(const int n, Color& grass, Color& rumble, Color& middle, Color& road);
};

#endif // LAND_SCAPE_H
