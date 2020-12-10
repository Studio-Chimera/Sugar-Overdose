#ifndef DEF_ControllerHelper
#define DEF_ControllerHelper

#include "cocos2d.h"
#include <utils\Player.h>

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

    void addControls(Player* player, std::string type);

};
#endif