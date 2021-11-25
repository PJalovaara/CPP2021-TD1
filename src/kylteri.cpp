#include "kylteri.hpp"

Kylteri::Kylteri(QList<QPointF> pathPoints, Game* game, QGraphicsItem* parent) : Enemy(pathPoints, game) {
    QPixmap p = QPixmap(":/images/kylteri1.png");
    p = p.scaled(50, 100, Qt::KeepAspectRatio); // Set size for the enemy
    setPixmap(p);
    setOffset(-p.width() / 2, -p.height() / 2); // Centering

    // Destroying a kylteri gives you more money
    price_ = 20;
};