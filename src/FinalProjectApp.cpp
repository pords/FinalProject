#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "SceneManager.hpp"
#include "MainScene.hpp"
#include "EnterScene.hpp"
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
    void keyUp( KeyEvent e );
    void keyDown( KeyEvent e );
	void update();
	void draw();
    
    EnterScene es;
    SceneManager sm;
};

void FinalProjectApp::prepareSettings( Settings *settings ){
	settings->setWindowSize( 800, 600 );
    settings->setFrameRate( FPS );
    settings->setFullScreen();
}


void FinalProjectApp::setup()
{
    enableAlphaBlending();
    hideCursor();
    es.init();
    sm.push(&es);
}

void FinalProjectApp::mouseDown( MouseEvent event ) {
    sm.mouseDown(event);
}

void FinalProjectApp::mouseUp( MouseEvent event ){
    sm.mouseUp(event);
}

void FinalProjectApp::mouseMove( MouseEvent event ) {
    sm.mouseMove(event);
}

void FinalProjectApp::mouseDrag( MouseEvent event ) {
    sm.mouseDrag(event);
}

void FinalProjectApp::keyUp( KeyEvent e ){
    sm.onKeyUp(e);
}

void FinalProjectApp::keyDown( KeyEvent e ){
    sm.onKeyDown(e);
}

void FinalProjectApp::update()
{
    sm.update();
}

void FinalProjectApp::draw()
{
	clear( Color( 0, 0, 0 ) );
    sm.draw();
}


CINDER_APP_BASIC( FinalProjectApp, RendererGl )
