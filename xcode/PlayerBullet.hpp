#ifndef FinalProject_PlayerBullet_hpp
#define FinalProject_PlayerBullet_hpp

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;

class PlayerBullet
{
public:
    PlayerBullet();
    PlayerBullet(Vec2f mMouseLoc);
    void update();
    void draw(Texture bullet);
    void collide();
    Vec2f getLocation();
    bool isAlive;
    
    //Texture bullet( loadImage( loadResource( "Bullet1.png" ) ) );
    //Texture * bulletTexture;
    //void init();
private:
    float damage;
    Vec2f location;
    double t;
    double curr;
};

#endif