#include "bullet.hpp"

#include <QPixmap>
#include <QTimer>
#include <qmath.h>

Bullet::Bullet(QGraphicsItem* parent) {
    // set graphics
    setPixmap(QPixmap(":/images/arrow.png"));

    // connect a timer to the move() slot
    QTimer* move_timer = new QTimer(this); // The timer dies when the bullet dies

    // Connect a signal to a slot
    connect(move_timer, SIGNAL(timeout), this, SLOT(move())); 
     // every 50 ms the timeout signal will be executed -> the bullet move will be executed every 50 ms
    move_timer->start(50);
}

void Bullet::move() {
    int STEPSIZE = 30;
    double theta = rotation(); // return the angle in degrees
    double dy = STEPSIZE * qSin(qDegreesToRadians(theta));
    double dx = STEPSIZE * qCos(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);
}