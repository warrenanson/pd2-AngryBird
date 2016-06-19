#ifndef BIRD_YELLOW_H
#define BIRD_YELLOW_H

#include <gameitem.h>
#include <bird.h>

#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>

class bird_yellow : public Bird
{
public:
    bird_yellow(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    void effect();
};

#endif // BIRD_YELLOW_H
