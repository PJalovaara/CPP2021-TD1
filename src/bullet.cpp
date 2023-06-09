#include "bullet.hpp"

#include <QPixmap>
#include <QTimer>
#include <qmath.h>
/**
 * @brief Construct a new Bullet object
 * 
 * @param parent Optional QGraphicsItem pointer, default value = 0
 */
Bullet::Bullet(QGraphicsItem* parent) {
    // set graphics
    QPixmap p = QPixmap(":/images/bulletblack.png");
    p = p.scaled(50, 100, Qt::KeepAspectRatio);
    setPixmap(p);  // Set size for the bullet
    setOffset(-p.width() / 2, -p.height() / 2);  // Centering

    // connect a timer to the move() slot
    QTimer* move_timer = new QTimer(this);  // The timer dies when the bullet dies

    // Connect a signal to a slot
    connect(move_timer, SIGNAL(timeout()), this, SLOT(Move()));

    // Initialize the speed, max_range_, bullet_damage_ and distance_traveled of the bullet
    speed_ = 15;
    max_range_ = 100;
    distance_traveled_ = 0;
    bullet_damage_ = 5;

    // every 20 ms the timeout signal will be executed -> the bullet move will be executed every 20 ms
    move_timer->start(20);
}

/**
 * @brief 
 * 
 */
void Bullet::Move() {
    double theta = rotation();  // return the angle in degrees
    double dy = speed_ * qSin(qDegreesToRadians(theta));
    double dx = speed_ * qCos(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);

    // Update the distance traveled and delete the bullet after traversing max_range_
    distance_traveled_ += qSqrt(dx*dx + dy*dy);
    if (distance_traveled_ >= max_range_) {
        delete this;
    }
}

double Bullet::GetMaxRange() {
    return max_range_;
}

void Bullet::SetMaxRange(double range) {
    max_range_ = range;
}

double Bullet::GetDistanceTraveled() {
    return distance_traveled_;
}

void Bullet::SetDistanceTraveled(double dist) {
    distance_traveled_ = dist;
}

int Bullet::GetDamage() {
    return bullet_damage_;
}
