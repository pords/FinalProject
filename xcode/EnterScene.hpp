#ifndef FinalProject_EnterScene_hpp
#define FinalProject_EnterScene_hpp

#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "SceneManager.hpp"
#include "cinder/Font.h"
#include "cinder/Color.h"

#define PLANE_TRANSITION_DURATION 0.4f

class EnterScene : public SceneManager::Scene {
	float trans;
    MainScene ms;
    Font s;
    Font k;
    Texture bg;
    Texture planes;
    Texture play;
    Texture high;
    Texture quit;
    float time;
    
    enum State{Play, High, Quit} selected;
public:
	EnterScene() : trans(0), s(loadResource("AGENCYR.TTF"), 160), k("HelveticaNeue-Ultralight", 120), selected(Play), time(0) {}
    
    void init(){
        bg = Texture(loadImage(loadResource("bg.png")));
        planes = Texture(loadImage(loadResource("planes.png")));
        play = Texture(loadImage(loadResource("playglow.png")));
        high = Texture(loadImage(loadResource("highglow.png")));
        quit = Texture(loadImage(loadResource("quitglow.png")));
    }
	
	virtual void draw() {
		//ci::app::AppBasic *a = ci::app::AppBasic::get();
		
		const float t = trans/PLANE_TRANSITION_DURATION;
		const float x = t*t*(3 - 2 * t);
        
        ColorA menu(118/255.f, 118/255.f, 118/255.f, 1.f * x);
        ColorA title(95/255.f, 95/255.f, 95/255.f, 1.f * x);
		
		//ci::gl::color(0.0f,0.0f,0.0f, 1.f);
		
        ci::gl::color(1.f,1.f,1.f);
		cinder::gl::draw( bg, ci::Vec2f(0,0) );
        cinder::gl::draw( planes, ci::Vec2f(-596, -470) + Vec2f(596, 470) * x );
        
        ci::gl::drawStringRight("Title Something", ci::Vec2f(1235, 85), title, s);
        
        ci::gl::drawStringRight("play game", ci::Vec2f(1235 ,305), 
                           menu, k);
        ci::gl::drawStringRight("high scores", ci::Vec2f(1235 ,465), 
                           menu, k);
        ci::gl::drawStringRight("quit game", ci::Vec2f(1235 ,625), 
                           menu, k);
        switch(selected)
        {
            case Play:
                color(1.f, 1.f,1.f,1.f * sin((time+=.12f)) * .5f + .5f);
                ci::gl::draw(play, ci::Vec2f(738,297));
                break;
            case High:
                color(1.f, 1.f,1.f,1.f * sin((time+=.12f)) * .5f + .5f);
                ci::gl::draw(high, ci::Vec2f(675,457));
                break;
            case Quit:
                color(1.f, 1.f,1.f,1.f * sin((time+=.12f)) * .5f + .5f);
                ci::gl::draw(quit, ci::Vec2f(753,617));
                break;
        }
        if( time > 6.28 ){
            time = 0;
        }
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
        switch( selected )
        {
            case Play:
                if ( ( e.getCode() == ci::app::KeyEvent::KEY_KP_ENTER || e.getCode() == ci::app::KeyEvent::KEY_RETURN ) ) {            getManager()->push(&ms);
                }
                break;
            case High:
                if ( ( e.getCode() == ci::app::KeyEvent::KEY_KP_ENTER || e.getCode() == ci::app::KeyEvent::KEY_RETURN ) ) {            
                    
                }
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
            case Play:
                if( e.getCode() == ci::app::KeyEvent::KEY_DOWN ){
                    time = 0;
                    selected = High;
                }
                else if( e.getCode() == ci::app::KeyEvent::KEY_UP ){
                    time = 0;
                    selected = Quit;
                }
                break;
            case High:
                if( e.getCode() == ci::app::KeyEvent::KEY_DOWN ){
                    time = 0;
                    selected = Quit;
                }
                else if( e.getCode() == ci::app::KeyEvent::KEY_UP ){
                    time = 0;
                    selected = Play;
                }
                break;
            case Quit:
                if( e.getCode() == ci::app::KeyEvent::KEY_UP ){
                    time = 0;
                    selected = High;
                }
                else if( e.getCode() == ci::app::KeyEvent::KEY_DOWN ){
                    time = 0;
                    selected = Play;
                }
                break;
        }
    }
};

#endif
