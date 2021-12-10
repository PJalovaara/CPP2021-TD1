#include "poop.hpp"

/**
 * @brief Construct a new Poop object
 * 
 * @param parent Optional QGraphicsItem pointer, default value = 0
 */
Poop::Poop(QGraphicsItem* parent) : Bullet(parent) {
    // set graphics
    QPixmap p = QPixmap(":/images/poop.png");
    p = p.scaled(30, 100, Qt::KeepAspectRatio);
    setPixmap(p);  // Set size for the bullet
    setOffset(-p.width() / 2, -p.height() / 2);  // Centering

    speed_ = 10;
    bullet_damage_ = 0;
}
