#ifndef DEF_LevelManager
#define DEF_LevelManager

#include <string>
#include <list>
#include "cocos2d.h"

class LevelManager
{
public:

    // ###################################################
    // Declarations
    // ###################################################

    LevelManager();
    ~LevelManager();

    // ###################################################
    // Getters
    // ###################################################

    std::list<std::string> getLevels();

    // ###################################################
    // Setters
    // ###################################################


    // ###################################################
    // Methods
    // ###################################################

    void openLevel(std::string level);



private:
    std::list<std::string> _levels;
};
#endif