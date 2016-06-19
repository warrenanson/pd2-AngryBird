#include "bird_yellow.h"
#include <iostream>
bird_yellow::bird_yellow(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene)
    :Bird(x,y,radius,timer,pixmap,world,scene)
{

}

void bird_yellow::effect()
{
    std::cout << "20" << std::endl;
    g_body->SetLinearVelocity(b2Vec2(g_body->GetLinearVelocity().x*2.5,g_body->GetLinearVelocity().y));
}
