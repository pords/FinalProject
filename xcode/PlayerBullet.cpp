#include <iostream>
#include "PlayerBullet.hpp"
#include "PlayerShip.hpp"

#define SPEED 20

PlayerBullet::PlayerBullet(Vec2f mMouseLoc)
{
    location = mMouseLoc;
    t = getElapsedSeconds();
    isAlive = true;
    static Texture bulletTexture( loadImage( loadResource( "Bullet1.png" ) ) );
}

void PlayerBullet::update()
{
    //location -= Vec2f((sin(getElapsedSeconds()*40)*7),SPEED*(getElapsedSeconds() - t)*60);
    location -= Vec2f(0,SPEED*(getElapsedSeconds() - t)*60);
    t = getElapsedSeconds();
    if(location.y < 0)
    {
        isAlive = false;
    }
}

void PlayerBullet::draw()
{
    color(128,255,255);
    drawSolidCircle( location + Vec2f(Rand::randFloat( 10.0f ) - 5, 0), Rand::randFloat( 10.0f ));
    //float a = Rand::randFloat(10.0f) + 5;
    //float b = Rand::randFloat(10.0f) + 5;
    //cinder::gl::draw( Texture( loadImage( loadResource( "Bullet1.png" ) ) ), Rectf(location - Vec2f(a, a), location + Vec2f(b, b)));
}

void PlayerBullet::collide()
{
    
}

Vec2f PlayerBullet::getLocation()
{
    return location;
}