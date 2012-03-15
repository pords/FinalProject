#ifndef FinalProject_Header_h
#define FinalProject_Header_h

#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "SceneManager.hpp"

#define PAUSESCENE_TRANSITION_DURATION 0.7f

class PauseScene : public SceneManager::Scene {
	SceneManager::Scene *base;
	float trans;
	enum State { In, Active, Out } state;
public:
	PauseScene(SceneManager::Scene *base) : base(base), trans(0), state(In) {}
	
	virtual void draw() {
		if ( base ){
			base->draw();
        }
		
		ci::app::AppBasic *a = ci::app::AppBasic::get();
		
		const float t = trans/PAUSESCENE_TRANSITION_DURATION;
		const float x = t*t*(3 - 2 * t);
		
		ci::gl::color(0.0f,0.0f,0.0f, 0.55f * x);
		
		ci::gl::drawSolidRect(ci::Rectf(0,0,a->getWindowWidth(), a->getWindowHeight()));
		
		ci::gl::drawStringRight("Game Paused", ci::Vec2f(120 * x,100));
	}
	
	virtual void update() {
		switch ( state ) {
			case In:
				if ( trans < PAUSESCENE_TRANSITION_DURATION )
					trans += 1/ci::app::AppBasic::get()->getFrameRate();
				else {
					trans = PAUSESCENE_TRANSITION_DURATION;
					state = Active;
				}
				break;
			case Active:
				break;
			case Out:
				if ( trans > 0 )
					trans -= 1/ci::app::AppBasic::get()->getFrameRate();
				else {
					trans = 1/ci::app::AppBasic::get()->getFrameRate();
					state = In;
					getManager()->pop();
				}
				break;
		}
		
	}
	virtual void onKeyUp(ci::app::KeyEvent &e) {
		if ( e.getCode() == ci::app::KeyEvent::KEY_SPACE && state != In  ) {
			state = Out;
		}
	}
};


#endif
