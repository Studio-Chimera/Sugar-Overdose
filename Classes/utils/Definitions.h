#pragma once
#include <String.h>
#include "menus/MainMenuScene.h"
#include "menus/LevelSelectionScene.h"
#include "menus/OptionsScene.h"
#include "menus/CreditsScene.h"

/*
this file defines all constantes
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

/*********** WAY WITH BUTTONS TEXTS HARD-CODED ***********/
//#define CAPTURE "buttons/Capture.png"

// IDs

// VALUES
#define DISPLAY_TIME_SPLASH_SCENE 1.5
constexpr auto DEFAULT_VOLUME = 0.2;

// STATES


// SOUNDS
#define MAIN_SOUND "sounds/Giedre-PisserDebout.mp3"

// SCENES
enum class CustomScenes { MainMenu, LevelSelectionMenu, OptionsMenu, CreditsMenu };

/*	Open a new menu
* dt: time to replace scene
* customScenes: new scene
* */
void changeScene(float dt, CustomScenes customScenes);