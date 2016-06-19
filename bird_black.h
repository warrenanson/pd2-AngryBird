#ifndef BIRD_BLACK_H
#define BIRD_BLACK_H

#include <gameitem.h>
#include <bird.h>

#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>

class bird_black : public Bird
{
public:
    bird_black(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    void effect();
};

#endif // BIRD_BLACK_H
