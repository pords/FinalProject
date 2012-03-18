#ifndef FinalProject_EnterScene_hpp
#define FinalProject_EnterScene_hpp

#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include "SceneManager.hpp"
#include "cinder/Font.h"
#include "cinder/Color.h"
#include "cinder/Rect.h"
#include "MainScene.hpp"

#define PLANE_TRANSITION_DURATION 0.4f
#define TRANSITION_DURATION ( 0.5f + PLANE_TRANSITION_DURATION )
#define BLINK_DURATION .17f

class EnterScene : public SceneManager::Scene {
    bool isContinuing;
	float trans;
    MainScene ms;
    Font s;
    Font k;
    Texture bg;
    Texture planes;
    Texture play;
    Texture high;
    Texture quit;
    Texture cglow;
    Texture playgame;
    Texture continuegame;
    Texture quitgame;
    Texture highscores;
    Texture titleTexture;
    float time;
    float scale;
    
    enum State{Play, High, Quit, Transition} selected;
public:
	EnterScene() : trans(0), s(loadResource("AGENCYR.TTF"), 160), k("HelveticaNeue-Ultralight", 120), selected(Play), time(0), scale(1) {}
    
    void init(){
        bg = Texture(loadImage(loadResource("bg.png")));
        planes = Texture(loadImage(loadResource("planes.png")));
        play = Texture(loadImage(loadResource("playglow.png")));
        high = Texture(loadImage(loadResource("highglow.png")));
        quit = Texture(loadImage(loadResource("quitglow.png")));
        cglow = Texture(loadImage(loadResource("continueglow.png")));
        playgame = Texture(loadImage(loadResource("playgame.png")));
        continuegame = Texture(loadImage(loadResource("continue.png")));
        quitgame = Texture(loadImage(loadResource("quitgame.png")));
        highscores = Texture(loadImage(loadResource("highscores.png")));
        titleTexture = Texture(loadImage(loadResource("beyondinfinity.png")));
        
        isContinuing = false;
    }
    
    void onActivate()
    {
        trans = 0;
        selected = Play;
    }
	
	virtual void draw() {
		ci::app::AppBasic *a = ci::app::AppBasic::get();
        float t = trans/PLANE_TRANSITION_DURATION;
		float x = t*t*(3 - 2 * t);
        
        ColorA menu(118/255.f, 118/255.f, 118/255.f, 1.f * x);
        ColorA title(95/255.f, 95/255.f, 95/255.f, 1.f * x);
		
        ci::gl::color(1.f,1.f,1.f);
		cinder::gl::draw( bg, ci::Vec2f(0,0) );
        cinder::gl::draw( planes, ci::Vec2f(-596, -470) + Vec2f(596, 470) * x );
                
		cinder::gl::draw( titleTexture, ci::Vec2f(505,55) );
        
        //ci::gl::drawStringRight("Title Something", ci::Vec2f(1235, 85), title, s);
        
        /*if (isContinuing) {
            ci::gl::drawStringRight("continue", ci::Vec2f(1235 ,305), 
                                    menu, k);
        }
        else{
            ci::gl::drawStringRight("play game", ci::Vec2f(1235 ,305), 
                                    menu, k);
        }
        ci::gl::drawStringRight("high scores", ci::Vec2f(1235 ,465), 
                           menu, k);
        ci::gl::drawStringRight("quit game", ci::Vec2f(1235 ,625), 
                                menu, k);*/
        if (isContinuing) {
            ci::gl::draw(continuegame, ci::Vec2f(821+ 9,297+ 9));
         }
         else{
             ci::gl::draw(playgame, ci::Vec2f(738 + 9,297 + 9));   
         }
         ci::gl::draw(highscores, ci::Vec2f(675+ 9,457+ 9));
         ci::gl::draw(quitgame, ci::Vec2f(753+ 9,617+ 9));
        
        Rectf rect (ci::Vec2f(738,297), ci::Vec2f(738 + 502,297 + 127));
        switch(selected)
        {
            case Play:
                color(1.f, 1.f,1.f,1.f * sin((time+=BLINK_DURATION)) * .5f + .5f);
                if (isContinuing) {
                    ci::gl::draw(cglow, ci::Vec2f(821, 297));
                }
                else{
                    ci::gl::draw(play, ci::Vec2f(738,297));   
                }
                break;
            case High:
                color(1.f, 1.f,1.f,1.f * sin((time+=BLINK_DURATION)) * .5f + .5f);
                ci::gl::draw(high, ci::Vec2f(675,457));
                break;
            case Quit:
                color(1.f, 1.f,1.f,1.f * sin((time+=BLINK_DURATION)) * .5f + .5f);
                ci::gl::draw(quit, ci::Vec2f(753,617));
                break;
            case Transition:
                t = trans/TRANSITION_DURATION;
                x = t*t*(3 - 2 * t);
                color(0.f, 0.f, 0.f, 1.f * x);
                ci::gl::drawSolidRect(ci::Rectf(0,0,a->getWindowWidth(), a->getWindowHeight()));
                x = pow(t, 5) + 0.1f;
                color(1.f,1.f,1.f,1.f * (.7-x));
                rect.scaleCentered(Vec2f(10,10) * x);
                if(isContinuing){
                    ci::gl::draw(cglow, rect);
                }
                else
                    ci::gl::draw(play, rect);
                if( t == 1 )
                {
                    getManager()->push(&ms);
                    isContinuing = true;
                }
                break;
        }
        if( time > 6.28 ){
            time = 0;
        }
	}
	
	virtual void update() {
        if( selected != Transition )
        {
            if( trans < PLANE_TRANSITION_DURATION ){
                trans += 1/ci::app::AppBasic::get()->getFrameRate();
            }
            else{
                trans = PLANE_TRANSITION_DURATION;
            }
        }
        else
        {
            if( trans < TRANSITION_DURATION  ){
                trans += 1/ci::app::AppBasic::get()->getFrameRate();
            }
            else{
                trans = TRANSITION_DURATION;
            }
        }
	}
	virtual void onKeyUp(ci::app::KeyEvent &e) {
        switch( selected )
        {
            case Play:
                if ( ( e.getCode() == ci::app::KeyEvent::KEY_KP_ENTER || e.getCode() == ci::app::KeyEvent::KEY_RETURN ) ) {     
                    selected = Transition;
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
            case Transition:
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
            case Transition:
                break;
        }
    }
};

#endif
