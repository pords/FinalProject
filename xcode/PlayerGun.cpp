#include <iostream>
#include "PlayerGun.hpp"

#define BPS 30

PlayerGun::PlayerGun()
{
    firing = false;
    t = 0;
}

void PlayerGun::update(Vec2f mMouseLoc)
{
    if(firing)
    {
        if(getElapsedSeconds() - t > 1.0/BPS)
        {
            bullets.push_back(PlayerBullet(mMouseLoc));
            t = getElapsedSeconds();
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

void PlayerGun::draw()
{
    for( list<PlayerBullet>::iterator p = bullets.begin(); p != bullets.end(); ++p ){
        p->draw();
    }
}

/*void PlayerGun::mouseDown( MouseEvent event ) {
    firing = true;
    mMouseLoc = event.getPos();
}

void PlayerGun::mouseUp( MouseEvent event ){
    firing = false;
}*/
