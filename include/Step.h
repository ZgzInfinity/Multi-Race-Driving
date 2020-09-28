
/*
 * ----------------------------------------------
 * Multi Race Driving: A general and customized
 * platform for 2.5D racing games
 * Author: ZgzInfinity
 * Date: 28-09-20
 * ----------------------------------------------
 */



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
 * Horizontal rectangle whose center is located in the coordinates (x, y, z), that is, it can have elevation (z).
 * In the centre of the rectangle will be the road that can have a curvature depending on the
 * curvature (curve) it has.
 * In addition, it may contain an object on each side of the road (spriteLeft, spriteRight).
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
     inline void project(float camX, float camY, float camZ, float camD, float width, float height, float rW, float zOffset){
        scalingValue = camD / (1.0f + position_3d_z + zOffset - camZ);
        position_2d_x = (1.0f + scalingValue * (position_3d_x - camX)) * width / 2.0f;
        position_2d_y = (1.0f - scalingValue * (position_3d_y - camY)) * height / 2.0f;
        position_2d_w = scalingValue * rW * width / 2.0f;
     }



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
     inline void drawSprite(RenderTexture &w, const std::vector<sf::Texture> &objs, const std::vector<float> &hitCoeff,
                           const std::vector<HitThresholdObject> &hitCoeffType, const std::vector<float> &scaleCoeff,
                           MapElement &object, bool left) const
     {
        // Sprite where the texture is going to be drawn
        Sprite s(objs[object.codeMapElement]);

        // Calculation of the dimensions of the object with the scaling factor
        const float width = scaleCoeff[object.codeMapElement] * s.getTextureRect().width;
        const float widthOri = s.getTextureRect().width;
        const float height = scaleCoeff[object.codeMapElement] * s.getTextureRect().height;
        const float heightOri = s.getTextureRect().height;

        // Coordinates of the map element in the screen with its elevation
        float destY = position_2d_y + 4.0f;
        float destW = width * position_2d_w / SCALE_RESOLUTION;
        float destH = height * position_2d_w / SCALE_RESOLUTION;

        //offsetY
        destY += destH * (-1.0f);

        // Calculation the elevation
        float clipH = destY + destH - clip;

        // Elevation
        if (clipH < 0){
            clipH = 0;
        }

        // Check the elevation
        if (clipH < destH) {

            // Scaling the element
            s.setScale(destW / widthOri, destH / heightOri);

            // Right road side
            float destX = position_2d_x + position_2d_w + object.offset * s.getGlobalBounds().width;

            if (left){
                // Left road side
                destX = position_2d_x - position_2d_w - s.getGlobalBounds().width - object.offset * s.getGlobalBounds().width;
            }

            // Set the position and draw in the screen
            s.setPosition(destX, destY);
            w.draw(s);

            // Control the hit coefficient of the map element
            if (hitCoeffType[object.codeMapElement] == HIT_CENTER) {
                // Collision in the center of the map element
                object.spriteMinX = destX + (s.getGlobalBounds().width - s.getGlobalBounds().width * hitCoeff[object.codeMapElement]) / 2.0f;
            }
            else if (hitCoeffType[object.codeMapElement] == HIT_RIGHT) {
                // Collision with the element in the right part
                object.spriteMinX = destX + s.getGlobalBounds().width - s.getGlobalBounds().width * hitCoeff[object.codeMapElement];
            }
            else {
                // Collision in the left and in both sides only
                object.spriteMinX = destX;
            }
            object.spriteMaxX = object.spriteMinX + s.getGlobalBounds().width * hitCoeff[object.codeMapElement];

            // Collision on the sides of the element but not in the center
            if (hitCoeffType[object.codeMapElement] != HIT_SIDES) {
                object.spriteToSideX = 0.0f;
            }
            else {
                object.spriteToSideX = s.getGlobalBounds().width - (object.spriteMaxX - object.spriteMinX);
            }
        }
     }
};


  #endif // STEP_H;
