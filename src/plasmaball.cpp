#include "plasmaball.hpp"

/**
 * @brief Construct a new Plasma Ball object
 * 
 * @param parent Optional QGraphicsItem pointer, default value = 0
 */
PlasmaBall::PlasmaBall(QGraphicsItem* parent) : Bullet(parent) {
    // set graphics
    QPixmap p = QPixmap(":/images/plasmaball.png");
    p = p.scaled(30, 100, Qt::KeepAspectRatio);
    setPixmap(p);  // Set size for the bullet
    setOffset(-p.width() / 2, -p.height() / 2);  // Centering

    bullet_damage_ = 9;
    speed_ = 20;
}
