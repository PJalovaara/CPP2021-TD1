#include "koneteekkari.hpp"


Koneteekkari::Koneteekkari(QList<QPointF> pathPoints, Game* game, QGraphicsItem* parent) : Enemy(pathPoints, game) {
    QPixmap p = QPixmap(":/images/kone1.png");
    p = p.scaled(50, 100, Qt::KeepAspectRatio); // Set size for the enemy
    setPixmap(p);
    setOffset(-p.width() / 2, -p.height() / 2); // Centering
};