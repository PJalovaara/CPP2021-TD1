#include "dokaani.hpp"


Dokaani::Dokaani(QList<QPointF> pathPoints, Game* game, QGraphicsItem* parent) : Enemy(pathPoints, game) {
    QPixmap p = QPixmap(":/images/dokaani3.png");
    p = p.scaled(90, 150, Qt::KeepAspectRatio); // Set size for the enemy
    setPixmap(p);
    setOffset(-p.width() / 2, -p.height() / 2); // Centering

    // Destroying a dokaani is difficult and dokaani getting to destination damages the goose a lot
    enemy_hp_ = 25;
    damage_ = 70;
    price_ = 50;
    speed_ = 1;
};