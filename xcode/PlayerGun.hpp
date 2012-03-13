#ifndef FinalProject_PlayerGun_hpp
#define FinalProject_PlayerGun_hpp

#include "PlayerBullet.hpp"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;

class PlayerGun
{
public:
    PlayerGun();
    void update(Vec2f mMouseLoc);
    void draw();
    void init();
    bool firing;
    
    Texture bulletTexture;
    list<PlayerBullet> bullets;
    double t;
};

#endif