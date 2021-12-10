#include "goldenbullet.hpp"

/**
 * @brief Construct a new Golden Golden Bullet object
 * 
 * @param parent Optional QGraphicsItem pointer, default value = 0
 */
GoldenBullet::GoldenBullet(QGraphicsItem* parent) : Bullet(parent) {
    // set graphics
    QPixmap p = QPixmap(":/images/bulletgold.png");
    p = p.scaled(30, 100, Qt::KeepAspectRatio);
    setPixmap(p);  // Set size for the bullet
    setOffset(-p.width() / 2, -p.height() / 2);  // Centering

    bullet_damage_ = 40;
    speed_ = 30;
}
