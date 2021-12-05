#include "poop.hpp"

Poop::Poop(QGraphicsItem* parent) : Bullet(parent) {
    // set graphics
    QPixmap p = QPixmap(":/images/poop.png");
    p = p.scaled(30, 100, Qt::KeepAspectRatio);
    setPixmap(p);  // Set size for the bullet
    setOffset(-p.width() / 2, -p.height() / 2);  // Centering

    bullet_damage_ = 0;
}
