#ifndef BIRD_BIG_H
#define BIRD_BIG_H

#include <gameitem.h>
#include <bird.h>

#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>

class bird_big : public Bird
{
public:
    bird_big(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    void effect();
};

#endif // BIRD_BIG_H
