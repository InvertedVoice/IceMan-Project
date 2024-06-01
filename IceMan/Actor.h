#ifndef ACTOR_H_
#define ACTOR_H_
#include "GraphObject.h"

class StudentWorld;

//ACTOR
class Actor : public GraphObject
{
public:
    Actor(StudentWorld* world, int imageID, int startX, int startY, Direction dir, double size, unsigned int depth, int hitPoints);
    ~Actor();
    StudentWorld* getWorld();
    int getHP() const;
    void setHP(int value);
   virtual void doSomething();
    bool m_isDead();

private:
    StudentWorld* m_world;
    int m_HP;
};

//ICEMAN
const int DEFAULT_HITPOINTS = 10;
const int DEFAULT_WATER = 5;
const int DEFAULT_SONARCHARGE = 1;
const int DEFAULT_GOLDNUGGET = 0;

class Iceman : public Actor
{
public:
    Iceman(StudentWorld* world, int startX, int startY, int imageID = IID_PLAYER, int hp = DEFAULT_HITPOINTS, int water = DEFAULT_WATER, int sonarCharge = DEFAULT_SONARCHARGE, int goldNugget = DEFAULT_GOLDNUGGET);
    ~Iceman();
    virtual void doSomething() override;
    bool dig();
    void moveToDir(Direction d);
    int getWater();
    int getSonarCharge();
    int getGoldNugget();
    void setWater(int value);
    void setSonarCharge(int value);
    void setGoldNugget(int value);

private:
    int m_water; 
    int m_sonarCharge; 
    int m_goldNugget;
};

//PROTESTER
class Protester : public Actor
{
public:
    Protester(StudentWorld* world, int startX, int startY, int imageID, Direction dir, double size, unsigned int depth, int hitPoints);
    virtual void doSomething() override;
    ~Protester();
};

//BOULDER
class Boulder : public Protester
{
public:
    Boulder(StudentWorld* world, int startX, int startY, int imageID = IID_BOULDER, Direction dir = down, double size = 1.0, unsigned int depth = 1, int hitPoints = 1);
    ~Boulder();
    virtual void doSomething() override;
    bool ifState_stable();
    bool ifState_waiting();
    bool ifState_falling();
    void setState_stable();
    void setState_wating();
    void setState_falling();
private:
    double radius;
    double damage;
    bool watingState;
    bool stableState;
    bool fallingState;
};

//Declare Collectible
class Collectible : public GraphObject
{
public:
    Collectible(StudentWorld* world, int imageID, int startX, int startY);
    ~Collectible();
};
//


//Declare Ice
class Ice : public Actor
{
public:
    Ice(StudentWorld* world, int startX, int startY, int imageID = IID_ICE, Direction dir = right, double size = 0.25, unsigned int depth = 3, int hitPoints = 1);
    ~Ice();
    void doSomething();
};
#endif // ACTOR_H_