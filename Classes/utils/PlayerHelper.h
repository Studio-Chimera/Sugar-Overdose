#ifndef DEF_PlayerHelper
#define DEF_PlayerHelper

#include <string>
#include <list>
#include "cocos2d.h"
#include <utils\Player.h>
#include <utils\ControllerHelper.h>

class PlayerHelper
{
public:

    // ###################################################
    // Declarations
    // ###################################################

    PlayerHelper();
    ~PlayerHelper();

    // ###################################################
    // Getters
    // ###################################################

    std::list<Player*> getPlayers();

    // ###################################################
    // Setters
    // ###################################################


    // ###################################################
    // Methods
    // ###################################################

    Player* createPlayer(Vec2* position);
    void setPlayerSprites(Player* player);
    void createSideMoveAnimation(int playerNumber, Player* player);
    void createTopMoveAnimation(int playerNumber, Player* player);
    void createBottomMoveAnimation(int playerNumber, Player* player);

private:
    std::list<Player*> _playersInstances;
};
#endif