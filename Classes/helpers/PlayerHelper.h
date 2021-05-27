#ifndef DEF_PlayerHelper
#define DEF_PlayerHelper

#include <string>
#include <list>
#include "cocos2d.h"
#include "entities/Player.h"
#include "helpers/ControllerHelper.h"

class PlayerHelper
{
public:

    // ###################################################
    // Declarations
    // ###################################################

    // ###################################################
    // Getters
    // ###################################################

    static PlayerHelper* getInstance();
    std::list<Player*> getPlayers();

    // ###################################################
    // Setters
    // ###################################################

    // ###################################################
    // Methods
    // ###################################################
    
    PlayerHelper();
    ~PlayerHelper();
    Player* createPlayer(float mapHeight, Vec2* position, int newPlayerNumber, Level* level);
    void setPlayerSprites(Player* player);
    void createSideMoveAnimation(int playerNumber, Player* player);
    void createTopMoveAnimation(int playerNumber, Player* player);
    void createBottomMoveAnimation(int playerNumber, Player* player);

    PlayerHelper(PlayerHelper& other) = delete;
    void operator=(const PlayerHelper&) = delete;

private:
    std::list<Player*> _playersInstances;

protected:


    static PlayerHelper* playerHelperInstance;
};
#endif
