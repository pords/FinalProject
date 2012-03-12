#ifndef FinalProject_SceneManager_hpp
#define FinalProject_SceneManager_hpp

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace gl;

class PlayerBullet
{
public:
    PlayerBullet();
    PlayerBullet(Vec2f mMouseLoc);
    void update();
    void draw();
    void collide();
    Vec2f getLocation();
    bool isAlive;
private:
    float damage;
    Vec2f location;
    double t;
    double curr;
};

#endif
