#include "ControllerHelper.h"
USING_NS_CC;
// ###################################################
// Declarations
// ###################################################

ControllerHelper::ControllerHelper()
{}

ControllerHelper::~ControllerHelper()
{}

// ###################################################
// Methods
// ###################################################

void ControllerHelper::addControls(Player* player, int playerNumber)
{
    switch (playerNumber){
        case PLAYER_NUMBER_ONE:
            player->setController(createKeyboard_ZQSD_Controller(player));
            break;
        case PLAYER_NUMBER_TWO:
            player->setController(createKeyboardArrowController(player));
            break;
        case PLAYER_NUMBER_THREE:
            break;
        case PLAYER_NUMBER_FOUR:
            break;
        case PLAYER_IA:
            //player->setIAController();
            break;
    }
}

EventListenerKeyboard* ControllerHelper::createKeyboardArrowController(Player* player)
{
    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        
        if (EventKeyboard::KeyCode::KEY_LEFT_ARROW == keyCode) {
            player->moveLeft();
        } else if (EventKeyboard::KeyCode::KEY_RIGHT_ARROW == keyCode) {
            player->moveRight();
        } else if (EventKeyboard::KeyCode::KEY_UP_ARROW == keyCode) {
            player->moveUp();
        } else if (EventKeyboard::KeyCode::KEY_DOWN_ARROW == keyCode) {
            player->moveDown();
        } else if (EventKeyboard::KeyCode::KEY_ENTER == keyCode) {
            player->plantBomb();
        }
    };

    return listener;
}

EventListenerKeyboard* ControllerHelper::createKeyboard_ZQSD_Controller(Player* player)
{
    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {

        if (EventKeyboard::KeyCode::KEY_A == keyCode) {
            player->moveLeft();
        } else if (EventKeyboard::KeyCode::KEY_D == keyCode) {
            player->moveRight();
        } else if (EventKeyboard::KeyCode::KEY_W == keyCode) {
            player->moveUp();
        } else if (EventKeyboard::KeyCode::KEY_S == keyCode) {
            player->moveDown();
        } else if (EventKeyboard::KeyCode::KEY_SPACE == keyCode) {
            player->plantBomb();
        }
    };

    return listener;
}
