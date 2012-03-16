#ifndef FinalProject_EnterScene_hpp
#define FinalProject_EnterScene_hpp

#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "SceneManager.hpp"

#define PLANE_TRANSITION_DURATION 0.5f

class EnterScene : public SceneManager::Scene {
	float trans;
    MainScene ms;
public:
	EnterScene() : trans(0) {}
	
	virtual void draw() {
		//ci::app::AppBasic *a = ci::app::AppBasic::get();
		
		const float t = trans/PLANE_TRANSITION_DURATION;
		const float x = t*t*(3 - 2 * t);
		
		//ci::gl::color(0.0f,0.0f,0.0f, 0.55f * x);
		
		cinder::gl::draw( Texture(loadImage(loadResource("BigPlane.png"))), ci::Vec2f(-850 , -425) + ci::Vec2f(700,489) * x );

        //ci::gl::drawStringRight("Game Paused", ci::Vec2f(120 * x,100));
	}
	
	virtual void update() {
        if( trans < PLANE_TRANSITION_DURATION ){
            trans += 1/ci::app::AppBasic::get()->getFrameRate();
        }
        else{
            trans = PLANE_TRANSITION_DURATION;
        }
	}
	virtual void onKeyUp(ci::app::KeyEvent &e) {
		if ( e.getCode() == ci::app::KeyEvent::KEY_KP_ENTER || e.getCode() == ci::app::KeyEvent::KEY_RETURN  ) {
			//ci::app::AppBasic::get().quit();
            getManager()->push(&ms);
		}
	}
};

#endif
