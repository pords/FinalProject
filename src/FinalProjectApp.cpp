#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "PlayerShip.hpp"
#include <list>

#define FPS 60.0f

using namespace std;
using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;



class FinalProjectApp : public AppBasic {
public:
    void prepareSettings( Settings *settings );
	void setup();
    void mouseDown( MouseEvent event);
    void mouseMove( MouseEvent event );
	void mouseDrag( MouseEvent event );	
	void mouseUp( MouseEvent event );	
	void update();
	void draw();    
    
    Vec2f mMouseLoc;
    PlayerShip ps;
};

void FinalProjectApp::prepareSettings( Settings *settings ){
	settings->setWindowSize( 800, 600 );
    settings->setFrameRate( FPS );
    //settings->setFullScreen();
}


void FinalProjectApp::setup()
{
    enableAlphaBlending();
    hideCursor();
    ps.init();
    /*ps.pg.firing = false;
    ps.pg.t = 0;*/
}

void FinalProjectApp::mouseDown( MouseEvent event ) {
    ps.pg.firing = true;
    mMouseLoc = event.getPos();
}

void FinalProjectApp::mouseUp( MouseEvent event ){
    ps.pg.firing = false;
}

void FinalProjectApp::mouseMove( MouseEvent event ) {
    mMouseLoc = event.getPos();
}

void FinalProjectApp::mouseDrag( MouseEvent event ) {
    //mouseDown( event );
    //mouseMove( event );
    
    //ps.pg.firing = true;
    
    mMouseLoc = event.getPos();
    
    //ps.update(mMouseLoc);//to delete
}

void FinalProjectApp::update()
{
    /*if(firing)
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
    }*/
    
    ps.update(mMouseLoc);
}

void FinalProjectApp::draw()
{
	clear( Color( 0, 0, 0 ) );
    ps.draw();
    /*for( list<PlayerBullet>::iterator p = bullets.begin(); p != bullets.end(); ++p ){
        p->draw();
    }*/
}


CINDER_APP_BASIC( FinalProjectApp, RendererGl )
