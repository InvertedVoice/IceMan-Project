#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include "GraphObject.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

class Actor;
class GraphObject;
class Ice;
class Iceman;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir) : GameWorld(assetDir), m_player(nullptr) {}
    ~StudentWorld();
    Actor* get_Iceman();
    bool isIce(int x, int y);
    void digIce(int x, int y);
    void update_stage_info();
    string display_user_interface(int score, int level, int lives, int health, int squirts, int gold, int sonar, int barrels);
    int init();
    int move();
    void cleanUp();

private:
    Ice* m_ice[64][64];
    Actor* m_player;
    std::vector<Actor*> m_actors;
};

#endif // STUDENTWORLD_H_