#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "SceneManager.hpp"
#include "MainScene.hpp"
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
	void update();
	void draw();
    
    MainScene ms;
    SceneManager sm;
};

void FinalProjectApp::prepareSettings( Settings *settings ){
	settings->setWindowSize( 800, 600 );
    settings->setFrameRate( FPS );
}


void FinalProjectApp::setup()
{
    enableAlphaBlending();
    hideCursor();
    sm.push(&ms);
}

void FinalProjectApp::mouseDown( MouseEvent event ) {
    ms.mouseDown(event);
}

void FinalProjectApp::mouseUp( MouseEvent event ){
    ms.mouseUp(event);
}

void FinalProjectApp::mouseMove( MouseEvent event ) {
    ms.mouseMove(event);
}

void FinalProjectApp::mouseDrag( MouseEvent event ) {
    ms.mouseDrag(event);
}

void FinalProjectApp::keyUp( KeyEvent e ){
    sm.onKeyUp(e);
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
