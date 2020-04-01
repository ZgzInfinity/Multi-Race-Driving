
#include "../include/Slot.h"

/**
 * Default constructor of the data type
 */
Slot::Slot(const int posXSlot, const int posYSlot, const int sizeXSlot, const int sizeYSlot, const int borderPan,
           const string textContent, Font& fontVehicleName, const int posXText, const int posYText,
           const int borderText, const int sizeText, const Color colorTS, const Color colorTBS, const Color colorTUS,
           const Color colorTBUS, const Color colorS, const Color colorBS, const Color colorUS, const Color colorBUS,
           const int posXVehicle, const int posYVehicle, vector<Texture>& vehicleTextures)
{

    shape.setPosition(posXSlot, posYSlot);
    shape.setSize(sf::Vector2f(sizeXSlot, sizeYSlot));
    shape.setOutlineThickness(borderPan);

    vehicleName.setFont(fontVehicleName);
    vehicleName.setString(textContent);
    vehicleName.setOutlineThickness(borderText);
    vehicleName.setCharacterSize(sizeText);
    vehicleName.setStyle(Text::Bold | Text::Underlined);
    vehicleName.setPosition(posXText, posYText);

    vehicleSprite.setPosition(posXVehicle, posYVehicle);
    texturesOfVehicle = vehicleTextures;

    colorSelected = colorS;
    colorUnSelected = colorUS;
    colorBorderSelected = colorBS;
    colorBorderUnSelected = colorBUS;
    colorTextSelected = colorTS;
    colorTextUnSelected = colorTUS;
    colorTextBorderSelected = colorTBS;
    colorTextBorderUnSelected = colorTBUS;

    actualTextureVehicle = 0;
}
