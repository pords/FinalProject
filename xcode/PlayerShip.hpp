#ifndef FinalProject_PlayerShip_h
#define FinalProject_PlayerShip_h

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

#include "PlayerGun.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;

class PlayerShip
{
    enum State { Left, Straight, Right } direction;
public:
    PlayerShip();
    void update(Vec2f location);
    void draw();
    void init();
    
    Vec2f mMouseLoc;
    Vec2f loc;
    //bool direction;
    Texture shipTexture;
    PlayerGun pg;
private:
    float remainingLife;
    float tween;
};

#endif
