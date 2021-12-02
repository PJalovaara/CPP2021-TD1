#include "dokaani.hpp"


Dokaani::Dokaani(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent) : Enemy(game) {
    QPixmap p = QPixmap(":/images/dokaani3.png");
    p = p.scaled(90, 150, Qt::KeepAspectRatio); // Set size for the enemy
    setPixmap(p);
    setOffset(-p.width() / 2, -p.height() / 2); // Centering

    // Destroying a dokaani is difficult and dokaani getting to destination damages the goose a lot
    enemy_hp_ = 30;
    damage_ = 70;
    price_ = 75;
    speed_ = 1;

        // Set the points in the path
    path_points_ = ChoosePath(paths);

    // Set initial pos and initial destination
    this->setPos(path_points_[0]); // Start from the first point in the path
    point_index_ = 1;
    dest_ = path_points_[point_index_];

    RotateToFacePoint(dest_);
    speed_ = 3;

    // Connect a timer to the move forward
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MoveForward()));

    // Call the MoveForward function every 40 ms (approx 25 fps)
    timer->start(40);
};

QList<QPointF> Dokaani::ChoosePath(QList<QList<QPointF>> paths) {
    return paths[0];
};