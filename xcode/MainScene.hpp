#ifndef FinalProject_MainScene_hpp
#define FinalProject_MainScene_hpp

#include "SceneManager.hpp"
#include "PlayerShip.hpp"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;

class MainScene : public SceneManager::Scene {
	float t;
    virtual void onDeactivate(SceneManager &sm) {
		//delete this;
	}
    
    Texture bulletTexture;
    //static Texture bulletTexture( loadImage( loadResource( "Bullet1.png" ) ) );
public:
	MainScene();
	virtual void draw();
	virtual void update();
	//void onKeyUp(ci::app::KeyEvent &e);
    void setup();
    void mouseDown( MouseEvent &event );
    void mouseUp( MouseEvent &event );
    void mouseMove( MouseEvent &event );    
    void mouseDrag( MouseEvent &event );
    virtual void onLoad();
    
    Vec2f mMouseLoc;
    PlayerShip ps;
};

#endif
