#include <iostream>
#include "PlayerGun.hpp"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

#define BPS 5

PlayerGun::PlayerGun()
{
    firing = false;
    t = 0;
}

void PlayerGun::update(Vec2f mMouseLoc)
{
    t += 1/ci::app::AppBasic::get()->getFrameRate(); 
    if(firing)
    {
        if( t > 1.0/BPS)
        {
            bullets.push_back(PlayerBullet(mMouseLoc, Vec2f(cos(pi/3), -sin(pi/3))));
            bullets.push_back(PlayerBullet(mMouseLoc, Vec2f(cos(pi/6), -sin(pi/6))));
            bullets.push_back(PlayerBullet(mMouseLoc, Vec2f(cos(pi/4), -sin(pi/4))));
            bullets.push_back(PlayerBullet(mMouseLoc, Vec2f(cos(pi/2), -sin(pi/2))));
            bullets.push_back(PlayerBullet(mMouseLoc, Vec2f(cos(3*pi/4), -sin(3*pi/4))));
            bullets.push_back(PlayerBullet(mMouseLoc, Vec2f(cos(5*pi/6), -sin(5*pi/6))));
            bullets.push_back(PlayerBullet(mMouseLoc, Vec2f(cos(2*pi/3), -sin(2*pi/3))));
            t = 0;
        }
    }
    
    for( list<PlayerBullet>::iterator p = bullets.begin(); p != bullets.end(); ++p ){
        p->update();
        if( !p->isAlive )
        {
            bullets.erase(p);
        }
    }
}

void PlayerGun::init()
{
    bulletTexture = Texture(loadImage(loadResource("Bullet1.png")));
}

void PlayerGun::draw()
{
    for( list<PlayerBullet>::iterator p = bullets.begin(); p != bullets.end(); ++p ){
        p->draw(bulletTexture);
    }
}

/*void PlayerGun::mouseDown( MouseEvent event ) {
    firing = true;
    mMouseLoc = event.getPos();
}

void PlayerGun::mouseUp( MouseEvent event ){
    firing = false;
}*/
