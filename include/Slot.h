
#ifndef SLOT_H
#define SLOT_H

#include <cstring>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


/*
 * Slot data type
 */
struct Slot{

    // Rectangle that represents the slot in the menu
    RectangleShape shape;

    // Vector of textures of the vehicles
    vector<Texture> texturesOfVehicle;

    // Sprite of the vehicle
    Sprite vehicleSprite;

    // Name of the vehicle
    Text vehicleName;

    // Colors for the slot
    Color colorSelected, colorUnSelected, colorBorderSelected, colorBorderUnSelected;

    // Colors for the text of the slot
    Color colorTextSelected, colorTextUnSelected, colorTextBorderSelected, colorTextBorderUnSelected;

    // Actual sprite to show
    int actualTextureVehicle;


    /**
     * Default constructor of the data type
    */
    Slot(const int posXSlot, const int posYSlot, const int sizeXSlot, const int sizeYSlot, const int borderPan,
         const string textContent, Font& fontVehicleName, const int posXText, const int posYText, const int borderText,
         const int sizeText, const Color colorTS, const Color colorTBS, const Color colorTUS, const Color colorTBUS,
         const Color colorS, const Color colorBS, const Color colorUS, const Color colorBUS, const int posXVehicle,
         const int posYVehicle, vector<Texture>& vehicleTextures);


};

#endif // SLOT_H
