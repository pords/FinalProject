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

float t = 0;

PlayerShip::PlayerShip()
{
    //mMouseLoc = Vec2f(0,0);
    direction = Straight;
    tween = 0;
}

void PlayerShip::init()
{
    shipTexture = Texture( loadImage( loadResource( "ShipMap.png" ) ) );
    pg.init();
}

void PlayerShip::update(Vec2f location)
{
    t += 1/ci::app::AppBasic::get()->getFrameRate(); 
    loc = mMouseLoc;
    mMouseLoc = location;

    switch(direction)
    {
            
        case Left:
            if( tween > -FRAMENO ){
                tween-=DT;
                if( loc.x - mMouseLoc.x < 0 && t > THING ){
                    t = 0;
                    direction = Right;
                }
                else if(t > THING){
                    t = 0;
                    direction = Straight;
                }
            }
            else{
                tween = -FRAMENO;
                if( loc.x - mMouseLoc.x < 0 && t > THING ){
                    t = 0;
                    direction = Right;
                }
                else if(t > THING){
                    t = 0;
                    direction = Straight;
                }
            }
            break;
        case Straight:
            if( tween == 0 ){
                if( loc.x - mMouseLoc.x > 0 && t > THING){
                    t = 0;
                    direction = Left;
                }
                else if( loc.x - mMouseLoc.x < 0 && t > THING){
                    t = 0;
                    direction = Right;
                }
                else if(t > THING){
                    t = 0;
                    direction = Straight;
                }
            }
            else if( tween < 0 ){
                tween+=DT;
            }
            else if( tween > 0 ){
                tween-=DT;
            }
            break;
        case Right:
            if( tween < FRAMENO ){
                tween+=DT;
                if( loc.x - mMouseLoc.x > 0 && t > THING){
                    t = 0;
                    direction = Left;
                }
                else if(t > THING){
                    t = 0;
                    direction = Straight;
                }
            }
            else{
                tween = FRAMENO;
                if( loc.x - mMouseLoc.x > 0 && t > THING){
                    t = 0;
                    direction = Left;
                }
                else if(t > THING){
                    t = 0;
                    direction = Straight;
                }
            }
            break;
    }
    
    pg.update(location);
}

void PlayerShip::draw()
{
    cinder::gl::draw( shipTexture, Area(Vec2f(SIZE*(floor(tween)+FRAMENO), 0), Vec2f(SIZE*(floor(tween)+FRAMENO) + SIZE, SIZE)), Rectf(mMouseLoc - Vec2f(SIZE/2,0), mMouseLoc + Vec2f(SIZE/2,SIZE)) );
    
    pg.draw();
}