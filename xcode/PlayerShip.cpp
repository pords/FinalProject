#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <iostream>

#include "PlayerShip.hpp"

#define DT .5f
#define THING 1/2.f

float t = 0;

PlayerShip::PlayerShip()
{
    mMouseLoc = Vec2f(0,0);
    direction = Straight;
    tween = 0;
    direction = Left;
    
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
            if( tween > -4 ){
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
                tween = -4;
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
            if( tween < 4 ){
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
                tween = 4;
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
        
    //cout << tween << endl;
    pg.update(location);
}

void PlayerShip::draw()
{
    cinder::gl::draw( shipTexture, Area(Vec2f(100*(floor(tween)+4), 0), Vec2f(100*(floor(tween)+4) + 100, 100)), Rectf(mMouseLoc - Vec2f(50,0), mMouseLoc + Vec2f(50,100)) );
    
    pg.draw();
}