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
public:
    PlayerShip();
    void update();
    void draw();
    void init();
    void onKeyDown(KeyEvent &e);
    void onKeyUp(KeyEvent &e);
    
    Vec2f location;
    Vec2f mMouseLoc;
    Vec2f loc;
    //bool direction;
    Texture shipTexture;
    PlayerGun pg;
    
    int state; //UDLRF
private:
    float remainingLife;
    float tween;
};

#endif
