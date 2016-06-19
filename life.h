#ifndef LIVE_H
#define LIVE_H

#include <gameitem.h>

#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTransform>
#include <QtMath>
#include <QDebug>

class life : public b2ContactListener
{
public:
    life();

    void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
};

#endif // LIVE_H
