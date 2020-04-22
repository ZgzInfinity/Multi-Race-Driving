
#include "../include/Step.h"

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

    mainColor = false;
}


Step::SpriteInfo::SpriteInfo() {
    spriteNum = -1;
    offset = spriteMinX = spriteMaxX = 0.0f;
    repetitive = false;
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



void Step::project(float camX, float camY, float camZ, float camD, float width, float height, float rW, float zOffset) {
    scalingValue = camD / (1.0f + position_3d_z + zOffset - camZ);
    position_2d_x = (1.0f + scalingValue * (position_3d_x - camX)) * width / 2.0f;
    position_2d_y = (1.0f - scalingValue * (position_3d_y - camY)) * height / 2.0f;
    position_2d_w = scalingValue * rW  * width / 2.0f;
}


void Step::drawSprite(RenderWindow* w, const vector<Texture> &objs, const vector<float> &coeff, Step::SpriteInfo &object,
                           bool left) {
    Sprite s(objs[object.spriteNum]);
    const int width = s.getTextureRect().width;
    const int h = s.getTextureRect().height;

    float destY = position_2d_y + 4.0f;
    float destW = float(width) * position_2d_w / 266.0f;
    float destH = float(h) * position_2d_w / 266.0f;

    destY += destH * (-1.0f); //offsetY

    float clipH = destY + destH - clip;
    if (clipH < 0)
        clipH = 0;

    if (clipH >= destH) return;
    s.setTextureRect(IntRect(0, 0, width, float(h) - float(h) * clipH / destH));
    s.setScale(destW / float(width), destH / float(h));

    float destX = position_2d_x + position_2d_w + object.offset * s.getGlobalBounds().width; // Right road side

    if (left)
        destX = position_2d_x - position_2d_w - s.getGlobalBounds().width - object.offset * s.getGlobalBounds().width; // Left road side
    s.setPosition(destX, destY);
    w->draw(s);

    object.spriteMinX =
                destX + (s.getGlobalBounds().width - s.getGlobalBounds().width * coeff[object.spriteNum]) / 2.0f;
        object.spriteMaxX = object.spriteMinX + s.getGlobalBounds().width * coeff[object.spriteNum];

}
