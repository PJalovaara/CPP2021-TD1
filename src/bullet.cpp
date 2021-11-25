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

    // Initialize the speed, max_range_, bullet_damage_ and distance_traveled of the bullet
    speed_ = 30;
    max_range_ = 100;
    distance_traveled_ = 0;
    bullet_damage_ = 5;

    // every 40 ms the timeout signal will be executed -> the bullet move will be executed every 40 ms
    move_timer->start(40);
}


void Bullet::Move() {
    double theta = rotation(); // return the angle in degrees
    double dy = speed_ * qSin(qDegreesToRadians(theta));
    double dx = speed_ * qCos(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);

    // Update the distance traveled and delete the bullet after traversing max_range_ 
    distance_traveled_ += qSqrt(dx*dx + dy*dy);
    if(distance_traveled_ >= max_range_) {
        delete this;
    }
}

double Bullet::GetMaxRange() {
    return max_range_;
};

void Bullet::SetMaxRange(double range) {
    max_range_ = range;
};

double Bullet::GetDistanceTraveled() {
    return distance_traveled_;
};

void Bullet::SetDistanceTraveled(double dist) {
    distance_traveled_ = dist;
};

int Bullet::GetDamage() {
    return bullet_damage_;
};