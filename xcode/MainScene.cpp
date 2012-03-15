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

bool paused = false;

void MainScene::onLoad()
{
    ps.init();
}

void MainScene::mouseDown( MouseEvent &event ) {
    ps.pg.firing = true;
    mMouseLoc = event.getPos();
}

void MainScene::mouseUp( MouseEvent &event ){
    ps.pg.firing = false;
}

void MainScene::mouseMove( MouseEvent &event ) {
    mMouseLoc = event.getPos();
}

void MainScene::mouseDrag( MouseEvent &event ) {
    mMouseLoc = event.getPos();
}

void MainScene::update()
{
    ps.update(mMouseLoc);
}

void MainScene::draw()
{
    gl::color(1.f,1.f,1.f);
    ps.draw();
}

void MainScene::onKeyUp(KeyEvent &e){
    if ( e.getCode() == KeyEvent::KEY_SPACE ) {
        paused = true;
        getManager()->push(&pause);
    }
}
