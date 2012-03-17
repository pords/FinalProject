#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "PlayerShip.hpp"
#include "MainScene.hpp"
#include <list>

#define FPS 60.0f

using namespace std;
using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;

Vec2f stars[500];

void MainScene::onLoad()
{
    ps.init();
    pause.init();
    for( int i = 0; i < 500; i++ )
    {
        stars[i] = Vec2f(Rand::randFloat(ci::app::AppBasic::get()->getWindowWidth()), Rand::randFloat(ci::app::AppBasic::get()->getWindowWidth()));
    }
    lifeBar = Texture(loadImage(loadResource("lifeBar.png")));
    lifeCover = Texture(loadImage(loadResource("lifeBar.png")));
    
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
}

void MainScene::draw()
{
    gl::color(1.f,1.f,1.f);
    for( int i = 0; i < 500; i++ )
    {
        //drawSolidCircle( stars[i], Rand::randFloat( 1.3f ));
    }
    ps.draw();
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
