#include "Actor.h"
#include "GameWorld.h"
#include "GameConstants.h"
#include "StudentWorld.h"

//ACTOR DEFINITION
Actor::Actor(StudentWorld* world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, int hp) :m_world(world), m_HP(hp), GraphObject(imageID, startX, startY, dir, size, depth) {}
Actor::~Actor() {}
StudentWorld* Actor::getWorld() {return m_world;}
int Actor::getHP() const {return m_HP;}
void Actor::setHP(int value) {m_HP = value;}
bool Actor::m_isDead() {return ((m_HP <= 0) ? true : false);}
void Actor::doSomething() {};

//ICEMAN DEFINITION
Iceman::Iceman(StudentWorld* world, int startX, int startY, int imageID, int hp, int water, int sonarCharge, int goldNugget) :Actor(world, imageID, startX, startY, right, 1.0, 0, hp), m_water(water), m_sonarCharge(sonarCharge), m_goldNugget(goldNugget)
{ setVisible(true); }
int Iceman::getWater() { return m_water; }
int Iceman::getSonarCharge() { return m_sonarCharge; }
int Iceman::getGoldNugget() { return m_goldNugget; }
void Iceman::setWater(int value) { m_water = value; }
void Iceman::setSonarCharge(int value) { m_sonarCharge = value; }
void Iceman::setGoldNugget(int value) { m_goldNugget = value; }

//ICEMAN DEFINITION - MOVEMENT
void Iceman::moveToDir(Direction d)
{
    const int MAX_UP = 60;
    const int MAX_DOWN = 0;
    const int MAX_LELF = 0;
    const int MAX_RIGHT = 60;
    switch (d)
    {
    case none:
        break;
    case left:
        if (getDirection() != left)
            setDirection(d);
        else
        {
            if (getX() != MAX_LELF)
                moveTo(getX() - 1, getY());
        }
        break;
    case right:
        if (getDirection() != right)
            setDirection(d);
        else
        {
            if (getX() != MAX_RIGHT)
                moveTo(getX() + 1, getY());
        }
        break;
    case up:
        if (getDirection() != up)
            setDirection(d);
        else
        {
            if (getY() != MAX_UP)
                moveTo(getX(), getY() + 1);
        }
        break;
    case down:
        if (getDirection() != down)
            setDirection(d);
        else
        {
            if (getY() != MAX_DOWN)
                moveTo(getX(), getY() - 1);
        }
        break;
    }
}

bool Iceman::dig()
{
    if (getWorld()->isIce(getX(), getY() + 3) || getWorld()->isIce(getX() + 1, getY() + 3) || getWorld()->isIce(getX() + 2, getY() + 3) || getWorld()->isIce(getX() + 3, getY() + 3) || getWorld()->isIce(getX(), getY()) || getWorld()->isIce(getX() + 1, getY()) || getWorld()->isIce(getX() + 2, getY()) || getWorld()->isIce(getX() + 3, getY()) || getWorld()->isIce(getX(), getY()) || getWorld()->isIce(getX(), getY() + 1) || getWorld()->isIce(getX(), getY() + 2) || getWorld()->isIce(getX(), getY() + 3) || getWorld()->isIce(getX() + 3, getY()) || getWorld()->isIce(getX() + 3, getY() + 1) || getWorld()->isIce(getX() + 3, getY() + 2) || getWorld()->isIce(getX() + 3, getY() + 3))
    {
        getWorld()->digIce(getX(), getY() + 3);
        getWorld()->digIce(getX() + 1, getY() + 3);
        getWorld()->digIce(getX() + 2, getY() + 3);
        getWorld()->digIce(getX() + 3, getY() + 3);
        getWorld()->digIce(getX(), getY());
        getWorld()->digIce(getX() + 1, getY());
        getWorld()->digIce(getX() + 2, getY());
        getWorld()->digIce(getX() + 3, getY());
        getWorld()->digIce(getX(), getY());
        getWorld()->digIce(getX(), getY() + 1);
        getWorld()->digIce(getX(), getY() + 2);
        getWorld()->digIce(getX(), getY() + 3);
        getWorld()->digIce(getX() + 3, getY());
        getWorld()->digIce(getX() + 3, getY() + 1);
        getWorld()->digIce(getX() + 3, getY() + 2);
        getWorld()->digIce(getX() + 3, getY() + 3);
        return true;
    }
    return false;
}

void Iceman::doSomething()
{
    if (m_isDead()) { return; }
    if (dig()) { getWorld()->playSound(SOUND_DIG); }

    int key;
    if (getWorld()->getKey(key) == true)
    {
        switch (key)
        {
        case none:
            break;
        case KEY_PRESS_LEFT:
            moveToDir(left);
            break;
        case KEY_PRESS_RIGHT:
            moveToDir(right);
            break;
        case KEY_PRESS_UP:
            moveToDir(up);
            break;
        case KEY_PRESS_DOWN:
            moveToDir(down);
            break;
        case KEY_PRESS_SPACE:
            break;
        case KEY_PRESS_ESCAPE:
            while (getWorld()->getLives() != 0)
                getWorld()->decLives();
            break;
        case KEY_PRESS_TAB:
            break;
        }
    }
}
Iceman::~Iceman() {}

//ICE DEFINITION
Ice::Ice(StudentWorld* world, int startX, int startY, int imageID, Direction dir, double size, unsigned int depth, int hp) :Actor(world, imageID, startX, startY, dir, size, depth, hp) { setVisible(true); };
Ice::~Ice() { setVisible(false); };
void Ice::doSomething() {}
