
/*
 * Module Step interface file
 */

#ifndef STEP_H
#define STEP_H

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "MapElement.h"

using namespace sf;
using namespace std;


const float SCALE_RESOLUTION = 280.0f;


/*
 * Hit coefficients types
 */
enum HitThresholdObject {
    // Collision in the center
    HIT_CENTER,
    // Collision in the left
    HIT_LEFT,
    // Collision in the right
    HIT_RIGHT,
    // Collision in the sides but not in the center
    HIT_SIDES
};


    /**
     * Rectángulo horizontal cuyo centro está ubicado en las coordenadas (x, y, z), es decir, puede tener elevación (z).
     * En el centro del rectángulo estará la carretera que puede tener una curvatura dependiendo del coeficiente de
     * curvatura (curve) que tenga.
     * Además, puede contener un objeto en cada lateral de la carretera (spriteLeft, spriteRight).
     */
    struct Step {

        // Coordinates in 3d of the rectangle step
        float position_3d_x, position_3d_y, position_3d_z;

        // Coordinates in 2d of the screen
        float position_2d_x, position_2d_y, position_2d_w;

        // Direction of the possible curve of the rectangle
        float directionCurve;

        // Possible elevation of the rectangle
        float clip;

        // Scaling factor to draw the rectangle
        float scalingValue;

        // Color of the rectangle
        bool mainColor;

        // Elements of the map
        MapElement spriteNearLeft, spriteNearRight, spriteFarLeft, spriteFarRight;

        // Background position
        float bgX;

        // Offsets
        float offsetX, yOffsetX;



        /**
         * Default constructor
         */
        explicit Step();



        /**
         * Sets the coordinates on the screen that correspond to the rectangle and its scale. This function must be
         * call to update the rectangle if the position of the map has been changed and.
         * @param camX is the coordinate of the rectangle in axis X
         * @param camY is the coordinate of the rectangle in axis Y
         * @param camZ is the coordinate of the rectangle in axis Z
         * @param camD is the deep of the rectangle in the screen
         * @param width is the width dimension of the rectangle
         * @param height is the height dimension of the rectangle
         * @param rW is the with of the road
         * @param zOffset is the offset in the axis Z
         */
        void project(float camX, float camY, float camZ, float camD, float width, float height, float rW, float zOffset);



        /**
         * Draw the map element in the screen of the game
         * @param w is the console window of the game
         * @param objs is a vector with all the map elements textures
         * @param hitCoeff is a vector with all the hits coefficients
         * @param hitCoeffType is the hit coefficient of the element to draw
         * @param scaleCoeff is the scaling factor of the element to draw
         * @param object is the element to draw in the screen
         * @param left control if the object has to be drawn on the left or on the right of the screen
         */
        void drawSprite(RenderTexture &w, const std::vector<sf::Texture> &objs, const std::vector<float> &hitCoeff,
                        const std::vector<HitThresholdObject> &hitCoeffType, const std::vector<float> &scaleCoeff,
                        MapElement &object, bool left) const;
    };


      #endif // STEP_H;
