#ifndef FinalProject_MainScene_hpp
#define FinalProject_MainScene_hpp

#include "SceneManager.hpp"
#include "PlayerShip.hpp"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;
using namespace app;

class MainScene : public SceneManager::Scene {
	float t;
    virtual void onDeactivate(SceneManager &sm) {
		//delete this;
	}
public:
	MainScene();
	virtual void draw();
	virtual void update();
	//void onKeyUp(ci::app::KeyEvent &e);
    void setup();
    void mouseDown( MouseEvent event );
    void mouseUp( MouseEvent event );
    void mouseMove( MouseEvent event );    
    void mouseDrag( MouseEvent event );
    
    Vec2f mMouseLoc;
    PlayerShip ps;
};

#endif
