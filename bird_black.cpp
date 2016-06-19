#include "bird_black.h"
#include <iostream>
bird_black::bird_black(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,radius,timer,pixmap,world,scene)
{

}

void bird_black::effect()
{    std::cout << "30" << std::endl;
    g_body->SetLinearVelocity(b2Vec2(-15,-1));
}
