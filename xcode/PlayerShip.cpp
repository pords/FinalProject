#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <iostream>

#include "PlayerShip.hpp"

#define DT .5f
#define THING 1/2.f
#define FRAMENO 1
#define SIZE 64
#define H_SPEED 10
#define V_SPEED 10

float t = 0;

PlayerShip::PlayerShip()
{
    //mMouseLoc = Vec2f(600,400);
    location = Vec2f(600,400);
    tween = 0;
    state = 0;
}

void PlayerShip::init()
{
    shipTexture = Texture( loadImage( loadResource( "ShipMap.png" ) ) );
    pg.init();
}

void PlayerShip::update()
{
    //t += 1/ci::app::AppBasic::get()->getFrameRate(); 
    loc = mMouseLoc;
    mMouseLoc = location;
    
    if( state&1 )
    {
        location += Vec2f(H_SPEED, 0);
        tween = 1;
    }
    if( state&2 )
    {
        location -= Vec2f(H_SPEED, 0);
        tween = -1;
    }
    
    if( state&4 )
    {
        location += Vec2f(0, V_SPEED);
    }
    if( state&8 )
    {
        location -= Vec2f(0, V_SPEED);
    }
    
    if( (state&3) == 0 ){
        tween = 0;
    }
    pg.update(location);
}

void PlayerShip::draw()
{
    cinder::gl::draw( shipTexture, Area(Vec2f(SIZE*(floor(tween)+FRAMENO), 0), Vec2f(SIZE*(floor(tween)+FRAMENO) + SIZE, SIZE)), Rectf(mMouseLoc - Vec2f(SIZE/2,0), mMouseLoc + Vec2f(SIZE/2,SIZE)) );
    
    pg.draw();
}

void PlayerShip::onKeyDown(KeyEvent &e)
{
    if ( e.getCode() == KeyEvent::KEY_RIGHT ) {
        state |= 1;
    }
    
    if( e.getCode() == KeyEvent::KEY_LEFT ){
        state |= 2;
    }
    
    if( e.getCode() == KeyEvent::KEY_UP ){
        state |= 8;
    }
    
    if( e.getCode() == KeyEvent::KEY_DOWN ){
        state |= 4;
    }
    
    if( e.getCode() == KeyEvent::KEY_SPACE ){
        pg.firing = true;
    }
}

void PlayerShip::onKeyUp(KeyEvent &e)
{
    if ( e.getCode() == KeyEvent::KEY_RIGHT ) {
        state &= 14;    
    }
    
    if( e.getCode() == KeyEvent::KEY_LEFT ){
        state &= 13;
    }
    
    if( e.getCode() == KeyEvent::KEY_UP ){
        state &= 7;
    }
    
    if( e.getCode() == KeyEvent::KEY_DOWN ){
        state &= 11;
    }
    
    if( e.getCode() == KeyEvent::KEY_SPACE ){
        pg.firing = false;
    }
}