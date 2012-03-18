#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "PlayerShip.hpp"
#include "MainScene.hpp"
#include "cinder/Rect.h"
#include <list>

#define FPS 60.0f
#define BAR_HEIGHT 30
#define BAR_WIDTH 400
#define COVER_WIDTH ( BAR_WIDTH - 21 )
#define COVER_HEIGHT ( BAR_HEIGHT - 21 )

using namespace std;
using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;

Vec2f stars[500];
Rectf bar;
Rectf cover;
float life;

void MainScene::onLoad()
{
    life = 1;
    ps.init();
    pause.init();
    for( int i = 0; i < 500; i++ )
    {
        stars[i] = Vec2f(Rand::randFloat(ci::app::AppBasic::get()->getWindowWidth()), Rand::randFloat(ci::app::AppBasic::get()->getWindowWidth()));
    }
    lifeBar = Texture(loadImage(loadResource("lifeBarLight.png")));
    lifeCover = Texture(loadImage(loadResource("lifeCover.png")));
    bar = Rectf( Vec2f(30, 720), Vec2f(30 + BAR_WIDTH, 720 + BAR_HEIGHT) );
    
}

void MainScene::mouseDown( MouseEvent &event ) {
    //ps.pg.firing = true;
    //mMouseLoc = event.getPos();
}

void MainScene::mouseUp( MouseEvent &event ){
    //ps.pg.firing = false;
}

void MainScene::mouseMove( MouseEvent &event ) {
    //mMouseLoc = event.getPos();
}

void MainScene::mouseDrag( MouseEvent &event ) {
    //mMouseLoc = event.getPos();
}

void MainScene::update()
{
    ps.update();
    cover = Rectf( Vec2f(42, 731), Vec2f(42 + COVER_WIDTH * life, 731 + COVER_HEIGHT) );//have to fix this shit
    life -= 0.001;
}

void MainScene::draw()
{
    gl::color(1.f,1.f,1.f);
    for( int i = 0; i < 500; i++ )
    {
        drawSolidCircle( stars[i], Rand::randFloat( 1.3f ));
    }
    ps.draw();
    
    cinder::gl::draw( lifeBar, bar );
    gl::color(44/255.0f,230/255.0f,131/255.0f,0.5f);
    //cinder::gl::draw( lifeCover, cover );
    drawSolidRect(cover);
}

void MainScene::onKeyUp(KeyEvent &e){
    if ( e.getCode() == KeyEvent::KEY_ESCAPE ) {
        getManager()->push(&pause);
    }
    else{
        ps.onKeyUp(e);
    }
}

void MainScene::onKeyDown(KeyEvent &e){
    ps.onKeyDown(e);
}
