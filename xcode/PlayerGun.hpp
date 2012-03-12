#ifndef FinalProject_PlayerGun_hpp
#define FinalProject_PlayerGun_hpp

#include "PlayerBullet.hpp"
#include <list>

class PlayerGun
{
public:
    PlayerGun();
    void update(Vec2f mMouseLoc);
    void draw();
    bool firing;
    
    list<PlayerBullet> bullets;
    double t;
};

#endif