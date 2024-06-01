#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir) { return new StudentWorld(assetDir); }
Actor* StudentWorld::get_Iceman() { return m_player; }
StudentWorld::~StudentWorld()
{
    for (int x = 0; x < 64; x++) 
    {
        for (int y = 0; y < 60; y++) 
        {
            delete m_ice[x][y];
            m_ice[x][y] = nullptr;
        }
    }

    //ACTOR DESTRUCTOR
    vector<Actor*>::iterator itr = m_actors.begin();
    while (itr != m_actors.end())
    {
        delete (*itr);
        (*itr) = nullptr;
        ++itr;
    }
}

void StudentWorld::update_stage_info() 
{
    int score = getScore();
    int level = getLevel();
    int live = getLives();
    int health = m_player->getHP();
    int water = 0;
    int gold = 0;
    int sonar = 0;

    string info = display_user_interface(score, level, live, health, water, gold, sonar, 0);
    setGameStatText(info);
}

string StudentWorld::display_user_interface(int score, int level, int lives, int health, int squirts, int gold, int sonar, int barrels) {
    stringstream s;

    s.fill('0');
    s << "SC: ";
    s << setw(6) << score;

    s.fill(' ');
    s << " LV: ";
    s << setw(2) << level;

    s << " LVS: ";
    s << setw(1) << lives;

    s << "  HLTH: ";
    s << setw(3) << health * 10;
    s << '%';

    s << "  WTR: ";
    s << setw(2) << squirts;

    s << "  GLD: ";
    s << setw(2) << gold;

    s << "  SNR: ";
    s << setw(2) << sonar;

    s << "  OIL: ";
    s << setw(2) << barrels;

    return s.str();
}

bool StudentWorld::isIce(int x, int y) 
{
    if (m_ice[x][y]->isVisible()) { return true; }
    return false;
}

void StudentWorld::digIce(int x, int y)
{
    if (m_ice[x][y]->isVisible()) 
    { m_ice[x][y]->setVisible(false); }
}

int StudentWorld::init()
{
    m_player = new Iceman(this, 30, 60);
    m_actors.push_back(m_player);
    for (int x = 0; x < 64; x++) 
    {
        for (int y = 0; y < 64; y++) 
        {
            m_ice[x][y] = new Ice(this, x, y);
            if ((x >= 30 && x <= 33) || y > 59)
                m_ice[x][y]->setVisible(false);
        }
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move() 
{
    //FOR BUILDING THE GAME AND STARTING
    update_stage_info();
    if (!isGameOver())
    {
        vector<Actor*>::iterator itr = m_actors.begin();
        while (itr != m_actors.end())
        {
            (*itr)->doSomething();
            ++itr;
        }
        return GWSTATUS_CONTINUE_GAME;
    }
    else
    { return GWSTATUS_PLAYER_DIED; }
}

void StudentWorld::cleanUp() 
{
    for (int x = 0; x < 64; x++) {
        for (int y = 0; y < 60; y++) {
            delete m_ice[x][y];
            m_ice[x][y] = nullptr;
        }
    }

    //ACTOR DESTRUCTOR
    vector<Actor*>::iterator itr = m_actors.begin();
    while (itr != m_actors.end())
    {
        delete (*itr);
        (*itr) = nullptr;
        ++itr;
    }

}