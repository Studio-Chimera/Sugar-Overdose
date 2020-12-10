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

void ControllerHelper::addControls(Player* player, std::string type)
{
	if (type == "player")
	{
		player->setController(createKeyboardController(player));
	}
	else if (type== "IA") {
		//player->setController();
	}
	else {
		//throw error
	}

}

EventListenerCustom createCustomController()
{

}

EventListenerKeyboard* createKeyboardController(Player* player)
{
    auto listener = EventListenerKeyboard::create();

    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_Q:
            player->moveLeft();
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            player->moveRight();
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_Z:
            player->moveTop();
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
        case EventKeyboard::KeyCode::KEY_S:
            player->moveBottom();
            break;
        }
    };

    return listener;
}


