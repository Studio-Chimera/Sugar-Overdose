#pragma once
#include <String.h>
#include "menus/MainMenuScene.h"
#include "menus/LevelSelectionScene.h"
#include "menus/OptionsScene.h"
#include "menus/CreditsScene.h"

/*
this file defines all constantes and reusables functions
*/

// SPRITES - BACKGROUNDS & WINDOWS
#define SPLASH_SCENE "backgrounds&windows/icon_studio_chimera.png"
#define MAIN_MENU ""
#define TITLE "backgrounds&windows/Sugar_Overdose_Title.png"
#define CREDITS "backgrounds&windows/credits.png"

// SPRITES - BUTTONS
#define BUTTON_LEVEL_SELECTION "buttons/button_level_selection.png"
#define BUTTON_LEVEL_SELECTION_PRESSED "buttons/"

#define BUTTON_OPTIONS "buttons/button_options.png"
#define BUTTON_OPTIONS_PRESSED "buttons/"

#define BUTTON_CREDITS "buttons/button_credits.png"
#define BUTTON_CREDITS_PRESSED "buttons/"

#define BUTTON_LEAVE "buttons/button_leave.png"
#define BUTTON_LEAVE_PRESSED "buttons/"

#define BUTTON_PLAY "buttons/button_play.png"
#define BUTTON_PLAY_PRESSED "buttons/"

#define BUTTON_BACK_TO_MAIN_MENU "buttons/button_back_to_main_menu.png"
#define BUTTON_BACK_TO_MAIN_MENU_PRESSED "buttons/"

// IDs

// VALUES NUMBER
#define TIME_DISPLAY_SPLASH_SCENE 1.5
#define STEP_PLAYER 167
#define TIME_EXPLOSION 1.0f 
#define TIME_WALK_ANIMATION 0.1

constexpr auto DEFAULT_VOLUME = 0;

// STATES


// TYPES
#define PLAYER_NUMBER_ONE 1
#define PLAYER_NUMBER_TWO 2
#define PLAYER_NUMBER_THREE 3
#define PLAYER_NUMBER_FOUR 4
#define PLAYER_IA 5

// SOUNDS
#define MAIN_SOUND "sounds/Giedre-PisserDebout.mp3"

// SCENES
enum class CustomScenes { MainMenu, LevelSelectionMenu, OptionsMenu, CreditsMenu };

// DIRECTIONS
#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT 2
#define DIRECTION_TOP 3
#define DIRECTION_BOTTOM 4


/*	Open a new menu
* dt: time to replace scene
* customScenes: new scene
* */
void changeScene(float dt, CustomScenes customScenes);