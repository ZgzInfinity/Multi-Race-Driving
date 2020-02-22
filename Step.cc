
#include "Step.h"

/**
 * Constructor of the data type Step
 * @return an instance of the data type Step
 */
Step::Step(){
    // Not sprite by default
    spriteX = 0.f;
    // Not curve by default
    directionCurve = 0;
    // Initialization of the coordinates in the three axis
    position_3d_x = 0, position_3d_y = 0, position_3d_z = 0;
}



/**
 * Projects a point in 3d in the equivalent 2d plane
 * @param camX is the coordinate in the axis X
 * @param camY is the coordinate in the axis Y
 * @param camZ is the coordinate in the axis Z
 */
void Step::project(int camX, int camY, int camZ){
    // Calculation of the scale between the 3d and 2d
    scalingValue = camD / (position_3d_z - camZ);
    // Assignment of the coordinates in 2d
    position_2d_x = (1 + scalingValue * (position_3d_x - camX)) * WIDTH / 2;
    position_2d_y = (1 - scalingValue * (position_3d_y - camY)) * HEIGHT / 2;
    position_2d_w = scalingValue * WIDTH_ROAD  * WIDTH / 2;
}



/**
 * Draw a sprite in the console game
 * @param app is the console game where the user is playing
 */
void Step::drawSprite(RenderWindow &app){
    // Creation of a new sprite
    Sprite s = character;
    // Get the dimensions of the image which contains the texture of the sprite
    int w = s.getTextureRect().width;
    int h = s.getTextureRect().height;

    // Calculation of the limit pointers of the texture
    float destX = position_2d_x + scalingValue * spriteX * WIDTH / 2;
    float destY = position_2d_y + 4;
    float destW  = w * position_2d_w / 266;
    float destH  = h * position_2d_w / 266;

    // Offset in both dimension X and Y
    destX += destW * spriteX;
    destY += destH * (-1);

    float clipH = destY + destH - clip;

    if (clipH < 0){
        clipH = 0;
    }

    if (clipH < destH){
        // Assign the new retangle dimensions
        s.setTextureRect(IntRect(0, 0, w, h - h * clipH / destH));
        // Assign the new scale
        s.setScale(destW / w,destH / h);
        // Assign the position to draw
        s.setPosition(destX, destY);
        // Draw the sprite in the screen
        app.draw(s);
    }
}



/**
 * Compares to sprites to determine which is first in the order
 * @param line is the other step to be compared
 * @return true is the instance caller to the method is lower than <<line>>.
 *         Otherwise returns false
 */
bool Step::operator < (Step& line_2){
    // Returns which is lower
    if (this->spriteY != line_2.spriteY){
        return this->spriteY < line_2.spriteY;
    }
    else {
        return this->spriteX < line_2.spriteX;
    }
}
