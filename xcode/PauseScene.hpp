#ifndef FinalProject_Header_h
#define FinalProject_Header_h

#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "SceneManager.hpp"

#define PAUSESCENE_TRANSITION_DURATION 0.3f
#define XPOS 875

class PauseScene : public SceneManager::Scene {
	SceneManager::Scene *base;
	float trans;
	enum State { In, Active, Out } state;
    enum Selected {Resume, Back, Quit} selected;
    Texture pauseTexture;
    Texture pointer;
    Font k;
    Selected prev;
    float thingy;
public:
	PauseScene(SceneManager::Scene *base) : base(base), trans(0), state(In), k("HelveticaNeue-Ultralight", 48), selected(Resume), thingy(0) {}
    
    void init()
    {
        pauseTexture = Texture(loadImage(loadResource("pause.png")));
        pointer = Texture(loadImage(loadResource("pointer.png")));
    }
    
    void onActivate()
    {
        selected = Resume;
    }
	
	virtual void draw() {
		if ( base ){
			base->draw();
        }
		
		ci::app::AppBasic *a = ci::app::AppBasic::get();
		
		const float t = trans/PAUSESCENE_TRANSITION_DURATION;
		const float x = t*t*(3 - 2 * t);
		
        ColorA c(213/255.f, 213/255.f, 213/255.f, 1.f * x);
		ci::gl::color(0.0f,0.0f,0.0f, 0.75f * x);
		ci::gl::drawSolidRect(ci::Rectf(0,0,a->getWindowWidth(), a->getWindowHeight()));
        
		ci::gl::color(1.0f,1.0f,1.0f, 1.0f * x);
        ci::gl::draw(pauseTexture, Vec2f(0,0));
        
		ci::gl::drawStringRight("resume game", ci::Vec2f(XPOS ,325), c, k);
		ci::gl::drawStringRight("back to main menu", ci::Vec2f(XPOS ,425), c, k);
		ci::gl::drawStringRight("quit game", ci::Vec2f(XPOS ,525), c, k);
        
        switch (selected) {
            case Resume:
                ci::gl::draw(pointer, Vec2f(565,333));
                break;
            case Back:
                ci::gl::draw(pointer, Vec2f(460,433));
                break;
            case Quit:
                ci::gl::draw(pointer, Vec2f(640,533));
                break;
        }
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
        switch( selected )
        {
            case Resume:
                if ( ( e.getCode() == ci::app::KeyEvent::KEY_KP_ENTER || e.getCode() == ci::app::KeyEvent::KEY_RETURN ) && state != In ) {     
                    state = Out;
                }
                break;
            case Back:
                if ( ( e.getCode() == ci::app::KeyEvent::KEY_KP_ENTER || e.getCode() == ci::app::KeyEvent::KEY_RETURN ) ) {                    getManager()->bot()->onActivate();
                    getManager()->m_scenes.erase(getManager()->m_scenes.end() - 2, getManager()->m_scenes.end());
                }
                break;
            case Quit:
                if ( ( e.getCode() == ci::app::KeyEvent::KEY_KP_ENTER || e.getCode() == ci::app::KeyEvent::KEY_RETURN ) ) {            
                    ci::app::AppBasic::get()->quit();
                }
                break;
        }
    }
    
    void onKeyDown(ci::app::KeyEvent &e)
    {
        switch( selected )
        {
            case Resume:
                if( e.getCode() == ci::app::KeyEvent::KEY_DOWN ){
                    prev = Resume;
                    selected = Back;
                }
                else if( e.getCode() == ci::app::KeyEvent::KEY_UP ){
                    prev = Resume;
                    selected = Quit;
                }
                break;
            case Back:
                if( e.getCode() == ci::app::KeyEvent::KEY_DOWN ){
                    prev = Back;
                    selected = Quit;
                }
                else if( e.getCode() == ci::app::KeyEvent::KEY_UP ){
                    prev = Back;
                    selected = Resume;
                }
                break;
            case Quit:
                if( e.getCode() == ci::app::KeyEvent::KEY_UP ){
                    prev = Quit;
                    selected = Back;
                }
                else if( e.getCode() == ci::app::KeyEvent::KEY_DOWN ){
                    prev = Quit;
                    selected = Resume;
                }
                break;
        }
    }
};


#endif
