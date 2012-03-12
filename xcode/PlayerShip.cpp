#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include <iostream>

#include "PlayerShip.hpp"

PlayerShip::PlayerShip()
{
    mMouseLoc = Vec2f(0,0);
    //tween = 0;
}

void PlayerShip::init()
{
    shipTexture = Texture( loadImage( loadResource( "Ship.png" ) ) );
}

void PlayerShip::update(Vec2f location)
{
    loc = mMouseLoc;
    mMouseLoc = location;
    
    /*if( loc.x - mMouseLoc.x < 0  )
    {
        if( tween < 1 )
        {
            tween += 1/60.0f;           
        }
        else
        {
            tween = 1;
        }
    }
    else
    {
        if(tween >= 0)
        {
            tween -= 1/60.0f;
        }
    }*/
    pg.update(location);
}

void PlayerShip::draw()
{
    //drawSolidCircle( mMouseLoc, 30);
    //draw (const Texture &texture, const Area &srcArea, const Rectf &destRect)
    //cinder::gl::draw(shipTexture, mMouseLoc);
    
    //cinder::gl::draw(Texture( loadImage( loadResource( "Ship.png" ) ) ), Area(Vec2f(50,0), Vec2f(75,25)), Rectf(mMouseLoc - Vec2f(25/2,25/2), mMouseLoc + Vec2f(25/2,25/2)));*/
    
    /*if( tween < 0.5 && tween > 0 )
    {   
        cinder::gl::draw(Texture( loadImage( loadResource( "ShipLeft1.png" ) ) ), mMouseLoc - Vec2f(50, 0));
    }
    if( tween < 1 && tween >= 0.5 )
    {
        cinder::gl::draw(Texture( loadImage( loadResource( "ShipLeft2.png" ) ) ), mMouseLoc - Vec2f(50, 0));
    }
    else*/
        cinder::gl::draw( shipTexture, mMouseLoc - Vec2f(50, 0));
    
    pg.draw();
}