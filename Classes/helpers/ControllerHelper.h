#ifndef DEF_ControllerHelper
#define DEF_ControllerHelper

#include "cocos2d.h"
#include <entities\Player.h>

class ControllerHelper
{
public:

    // ###################################################
    // Declarations
    // ###################################################

    ControllerHelper();
    ~ControllerHelper();


    // ###################################################
    // Methods
    // ###################################################

    void addControls(Player* player, int type);

private:
    EventListenerKeyboard* createKeyboardArrowController(Player* player);
    EventListenerKeyboard* createKeyboard_ZQSD_Controller(Player* player);
    EventListenerCustom createCustomController();

};
#endif
