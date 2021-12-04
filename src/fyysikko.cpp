#include "fyysikko.hpp"

#include <QRandomGenerator> //delete later

Fyysikko::Fyysikko(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent) : Enemy(game) {
    QPixmap p = QPixmap(":/images/fyssa1.png");
    p = p.scaled(50, 100, Qt::KeepAspectRatio); // Set size for the enemy
    setPixmap(p);
    setOffset(-p.width() / 2, -p.height() / 2); // Centering

    enemy_hp_ = 20;
    damage_ = 30;
    price_ = 30;
    speed_ = 2;

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

QList<QPointF> Fyysikko::ChoosePath(QList<QList<QPointF>> paths) {
    //change later
    int rand_idx = QRandomGenerator::global()->bounded((int)paths.size());
    return paths[rand_idx];
};