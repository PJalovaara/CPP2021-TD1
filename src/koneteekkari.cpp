#include "koneteekkari.hpp"

#include <QRandomGenerator>

Koneteekkari::Koneteekkari(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent) : Enemy(game) {
    QPixmap p = QPixmap(":/images/kone1.png");
    p = p.scaled(50, 100, Qt::KeepAspectRatio);  // Set size for the enemy
    setPixmap(p);
    setOffset(-p.width() / 2, -p.height() / 2);  // Centering

    enemy_hp_ = 20;
    damage_ = 15;
    price_ = 10;
    speed_ = 2;

        // Set the points in the path
    path_points_ = ChoosePath(paths);

    // Set initial pos and initial destination
    this->setPos(path_points_[0]);  // Start from the first point in the path
    point_index_ = 1;
    dest_ = path_points_[point_index_];

    RotateToFacePoint(dest_);
}

// Chooses the path at random
QList<QPointF> Koneteekkari::ChoosePath(QList<QList<QPointF>> paths) {
    int rand_idx = QRandomGenerator::global()->bounded(static_cast<int>(paths.size()));
    return paths[rand_idx];
}
