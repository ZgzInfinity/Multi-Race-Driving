
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "Button.h"
#include "SoundPlayer.h"


using namespace std;
using namespace sf;

const int DEFAULT_WIDTH = 921;
const int DEFAULT_HEIGHT = 691;
const int SCREEN_HD_WIDTH = 1280;
const int SCREEN_HD_HEIGHT = 720;
const int FPS = 60;
const int VERTICAL_OFFSET = 20;

const float IMAGE_DEFAULT_OFFSET = 1.3f;

const pair<const int ,const int> SCREEN_DEFAULT = make_pair(DEFAULT_WIDTH, DEFAULT_HEIGHT);
const pair<const int ,const int> SCREEN_1 = make_pair(SCREEN_HD_WIDTH, SCREEN_HD_HEIGHT);
const pair<const int ,const int> SCREEN_2 = make_pair(1366, 768);
const pair<const int ,const int> SCREEN_3 = make_pair(1920, 1080);
const pair<const int ,const int> SCREEN_4 = make_pair(2560, 1440);
const pair<const int ,const int> SCREEN_5 = make_pair(3840, 2160);

enum State {
    ANIMATION,
    START,
    OPTIONS,
    PLAYER_MENU,
    MULTIPLYER_MENU,
    GAME_MODES_MENU,
    VEHICLE_SELECTION,
    LOAD_GAME,
    PLAY_GAME,
    RANKING,
    CLASIFICATION,
    EXIT
};


enum Difficult {
    PEACEFUL, // Without enemies
    EASY,
    NORMAL,
    HARD
};



struct Configuration {

    private:
        const vector<pair<int, int>> resolutions;
        int resIndex;

    public:

        RenderTexture w;
        RenderWindow window;
        float screenScale;
        bool isDefaultScreen;

        Keyboard::Key menuKey;
        Keyboard::Key menuUpKey;
        Keyboard::Key menuDownKey;
        Keyboard::Key menuEnterKey;
        Keyboard::Key accelerateKey;
        Keyboard::Key brakeKey;
        Keyboard::Key leftKey;
        Keyboard::Key rightKey;
        Keyboard::Key soundtrackKey;

        Font fontElapsedTime;

        Font fontTimeToPlay;

        Font fontScore;

        Font speedVehicle;

        Font options;

        const float camD; // Camera depth
        const int renderLen; // Length rendered

        // Difficult level
        Difficult level;

        // Control if the configuration has been changed correctly
        bool modifiedConfig;

        // max AI aggressiveness level: max probability that the ai will be activated
        float maxAggressiveness;
        bool enableAI;

        // Control the view of graphics more retro
        bool enablePixelArt;

        // Control if the options menu has been visited
        bool comeFromOptions;

        // Separation between words in the description of the buttons in axis x and y
        int thresholdDescriptionX, thresholdDescriptionY;

        // Control if the main menu has been read before or not
        bool mainMenuRead;

        // Texture of the background
        Texture textureBackground;
        Sprite sBackground;

        // Colors of the main menu
        vector<Color> colorTexts;
        vector<Color> colorBorders;

        // Vector of the fonts of the main menu
        vector<Font> fontsMainMenu;

        // Vector of contents of the main menu
        vector<string> contents;

        // Control if the player menu has been read before or not
        bool playerMenuRead;

        // Texture of the background
        Texture playerMenuBackground;
        Sprite sPlayerMenuBackground;

        // Texture of the background panel
        Texture playerMenuPanelBack;

        // Color border of the main panel
        Color colorBorderPanelPlayerMenu;

        // Contents of the player menu title
        string contentTitlePlayerMenu;

        // Font of the title text of the menu
        Font fontPlayerMenu;

        // Colors of the main text of the player menu
        Color colorTitleTextPlayerMenu;
        Color colorTitleBorderPlayerMenu;

        // Colors of the description panel of the player menu
        Color colorDescriptionPanelInsidePlayerMenu;
        Color colorDescriptionPanelBorderPlayerMenu;

        // Font of the buttons of the menu
        Font fontMenuPlayerButtons;

        // Vector of buttons of the player menu
        vector<Button> menuPlayerButtons;

        // Color of the font buttons in the menu player
        Color colorFontMenuPlayerButtons;

        // Images that are displayed with the buttons description
        vector<Texture> texturesIconPlayerMenu;
        vector<Sprite> iconButtonsPlayerMenu;

        // Image offset to display the images in the player menu
        float imageOffset;

        // Control if the game modes menu has been read before or not
        bool gameModesMenuRead;

        // Control if the player has visited the options menu before
        bool fromOptions;

        // Texture of the background
        Texture gameModesMenuBackground;
        Sprite sGameModesBackground;

        // Texture of the background panel
        Texture gameModesMenuPanelBack;

        // Color border of the main panel
        Color colorBorderPanelGameModeMenu;

        // Contents of the game modes menu title
        string contentTitleGameModeMenu;

        // Font of the title text of the menu
        Font fontGameModeMenu;

        // Colors of the main text of the game modes menu
        Color colorTitleTextGameModeMenu;
        Color colorTitleBorderGameModeMenu;

        // Colors of the description panel of the game modes menu
        Color colorDescriptionPanelInsideGameModeMenu;
        Color colorDescriptionPanelBorderGameModeMenu;

        // Font of the buttons of the menu
        Font fontMenuGameModeButtons;

        // Vector of buttons of the game modes menu
        vector<Button> gameModeMenuButtons;

        // Color of the font buttons in the game modes menu
        Color colorFontMenuGameModesButtons;

        // Control if the xml configuration file has been read or not
        bool optionsMenuRead;

        // Texture of the background
        Texture optionsMenuBackground;
        Sprite optMenuBackground;

        // Texture of the background main panel
        Texture optionsMenuPanelBack;

        // Color border of the main panel
        Color colorBorderPanelOptionsMenu;

         // Contents of the options menu title
        string contentTitleOptionsMenu;

        // Font of the title text of the menu
        Font fontOptionsMenu;

        // Colors of the main text of the options menu
        Color colorTitleTextOptionsMenu;
        Color colorTitleBorderOptionsMenu;

        // Font of the buttons of the menu
        Font fontMenuOptionsButtons;

        // Vector of buttons of the options menu
        vector<Button> optionsMenuButtons;

        // Color of the font buttons in the options menu
        Color colorFontMenuOptionsButtons;

        // Control if the sound menu has been read before from the xml configuration file
        bool soundMenuRead;

        // Texture of the background
        Texture soundMenuBackground;
        Sprite sdMenuBackground;

        // Texture of the background main panel
        Texture soundMenuPanelBack;

        // Color border of the main panel
        Color colorBorderPanelSoundMenu;

         // Contents of the options menu title
        string contentTitleSoundMenu;

        // Font of the title text of the menu
        Font fontSoundMenu;

        // Colors of the main text of the options menu
        Color colorTitleTextSoundMenu;
        Color colorTitleBorderSoundMenu;

        // Font of the buttons of the menu
        Font fontMenuSoundButtons;

        // Vector of buttons of the sound menu
        vector<Button> soundMenuButtons;

        // Color of the font buttons in the sound menu
        Color colorFontMenuSoundButtons;

        // Control if the graphics menu has been read from its xml file or not
        bool graphicsMenuRead;

        // Texture of the background
        Texture graphicsMenuBackground;
        Sprite ghMenuBackground;

        // Texture of the background main panel
        Texture graphicsMenuPanelBack;

        // Color border of the main panel
        Color colorBorderPanelGraphicsMenu;

         // Contents of the graphics menu title
        string contentTitleGraphicsMenu;

        // Font of the title text of the menu
        Font fontGraphicsMenu;

        // Colors of the main text of the graphics menu
        Color colorTitleTextGraphicsMenu;
        Color colorTitleBorderGraphicsMenu;

        // Font of the buttons of the menu
        Font fontMenuGraphicsButtons;

        // Control of the sound menu has been visited before
        bool comeFromSound;

        // Control of the graphics menu has been visited before
        bool comeFromGraphics;

        // Vector with the fonts of the buttons
        vector<string> contentButtonsGraphics;

        // Vector with the colors of the buttons
        vector<Color> colorButtons;

        // Color of the font buttons in the graphics menu
        Color colorFontMenuGraphicsButtons;

        // Control if the vehicle controllers menu has been read from its xml file or not
        bool vehicleControllersMenuRead;

        // Texture of the background
        Texture vehicleControllersMenuBackground;
        Sprite vehControllersMenuBackground;

         // Texture of the background main panel
        Texture vehicleControllersMenuPanelBack;

        // Color border of the main panel
        Color colorBorderPanelVehicleControllersMenu;

        // Contents of the vehicle controllers menu title
        string contentTitleVehicleControllersMenu;

        // Font of the title text of the menu
        Font fontVehicleControllersMenu;

        // Colors of the main text of the vehicle controllers menu
        Color colorTitleTextVehicleControllersMenu;
        Color colorTitleBorderVehicleControllersMenu;

        // Font of the buttons of the menu
        Font fontMenuVehicleControllersButtons;

        // Vector of buttons of the vehicle controllers menu
        vector<Button> vehicleControllersMenuButtons;

        // Color of the vehicle controllers menu
        Color colorFontVehicleControllersMenu;

        // Control if the pause menu configuration has been read before
        bool pauseMenuRead;

        // Color for for inside and border of the pause menu panel
        Color colorInsidePanelPauseMenu;
        Color colorBorderPanelPauseMenu;

        // Contents of the pause menu title
        string contentTitlePauseMenu;

        // Font of the title text of the menu
        Font fontPauseMenu;

        // Colors of the main text of the pause menu
        Color colorTitleTextPauseMenu;
        Color colorTitleBorderPauseMenu;

        // Font of the buttons of the menu
        Font fontMenuPauseButtons;

        // Vector of buttons of the pause menu
        vector<Button> pauseMenuButtons;

        // Color of the pause menu
        Color colorFontPauseMenu;

        // Color of the font buttons of the pause menu
        Color colorFontMenuPauseButtons;

        // Control if the configuration of the vehicle selection menu has been read
        bool vehicleSelectionMenuRead;

        // Background of the vehicle selection menu
        Texture backgroundSelectionMenu;

        // Color used to paint the background
        Color colorBackground;

        // Content of the title text of the vehicle selection menu
        string contentTitleVehicleSelectionMenu;

        // Font of the vehicle selection menu title
        Font fontVehicleSelectionMenu;

        // Color of the title vehicle selection menu
        Color colorTitleTextVehicleSelectionMenu;

        // Color of the border title vehicle selection menu
        Color colorTitleBorderVehicleSelectionMenu;

        // Font of the title of the vehicle name `panel
        Font fontVehicleSelectionMenuPanelTitle;

        // Color of the vehicle name title
        Color colorTitleTextVehicleSelectionMenuName;

        // Color of the vehicle border title
        Color colorTitleBorderVehicleSelectionMenuName;

        // Color of the border of the vehicle panel
        Color colorBorderVehiclePanel;

        // Font of the title of the vehicle name `panel
        Font fontVehicleSelectionMenuPanelTitleProp;

        // Color of the vehicle name title
        Color colorTitleTextVehicleSelectionMenuProp;

        // Color of the vehicle border title
        Color colorTitleBorderVehicleSelectionMenuNameProp;

        // Color of the border of the properties panel
        Color colorBorderPropertiesPanel;

        // Color of the vehicle selection menu panel properties
        Font fontVehicleSelectionMenuPanelProp;

        // Color of the text vehicle selection properties
        Color colorTextVehicleSelectionProp;

        // Color of the border vehicle selection properties
        Color colorBorderVehicleSelectionProp;

        // Color of the inside of the vehicle properties panel
        Color colorInsideVehicleSelectionMenuPanelProp;

        // Color of the buttons of the menu
        vector<Color> vehicleSelectionMenuColorButtons;


        /**
         * Constructor por defecto.
         */
        Configuration();



        /**
         * Load the configuration of the graphics menu stored in its xml
         * configuration file
         * @param path contains the path of the xml configuration file
         * @param c is the configuration of the game
         */
        void loadGraphicsMenuConfiguration(const string path);



        /**
         * Devuelve true si se ha cambiado la resolución de pantalla.
         * @param r is the module sound player of he graphics the game
         * @return
         */
        State graphicsMenu(SoundPlayer& r);
};


/**
 * Devuelve la fuente para el tiempo.
 * @return
 */
Font initializeFontElapsedTime();

/**
 * Devuelve la fuente para la velocidad.
 * @return
 */
Font initializeFontTimeToPlay();

/**
 * Devuelve la fuente para las opciones.
 * @return
 */
Font initializeFontOptions();


Font initializeFontScore();

#endif // CONFIGURATION_H


