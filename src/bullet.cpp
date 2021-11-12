#include "bullet.hpp"

#include <QPixmap>
#include <QTimer>
#include <qmath.h>

Bullet::Bullet(QGraphicsItem* parent) {
    // set graphics
    QPixmap p = QPixmap(":/images/bulletblack.png");
    setPixmap(p.scaled(50, 100, Qt::KeepAspectRatio)); // Set size for the bullet

    // connect a timer to the move() slot
    QTimer* move_timer = new QTimer(this); // The timer dies when the bullet dies

    // Connect a signal to a slot
    connect(move_timer, SIGNAL(timeout()), this, SLOT(Move())); 

    // every 50 ms the timeout signal will be executed -> the bullet move will be executed every 50 ms
    move_timer->start(50);
}


void Bullet::Move() {
    int STEPSIZE = 30;
    double theta = rotation(); // return the angle in degrees
    double dy = STEPSIZE * qSin(qDegreesToRadians(theta));
    double dx = STEPSIZE * qCos(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);
}