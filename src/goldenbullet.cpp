#include "goldenbullet.hpp"


GoldenBullet::GoldenBullet(QGraphicsItem* parent) : Bullet(parent) {
    // set graphics
    QPixmap p = QPixmap(":/images/bulletgold.png");
    setPixmap(p.scaled(30, 100, Qt::KeepAspectRatio)); // Set size for the bullet
};