#include "bird_big.h"
#include <iostream>
bird_big::bird_big(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,radius,timer,pixmap,world,scene)
{
    b2FixtureDef fixturedef;

    fixturedef.density = 20.0f;
}

void bird_big::effect()
{
    std::cout << "40" << std::endl;
    g_body->SetLinearVelocity(b2Vec2(0,-40));
}
