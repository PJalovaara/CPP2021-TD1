#include "kylteri.hpp"

Kylteri::Kylteri(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent) : Enemy(game) {
    QPixmap p = QPixmap(":/images/kylteri1.png");
    p = p.scaled(50, 100, Qt::KeepAspectRatio); // Set size for the enemy
    setPixmap(p);
    setOffset(-p.width() / 2, -p.height() / 2); // Centering

    // Destroying a kylteri gives you more money
    enemy_hp_ = 5;
    price_ = 40;
    damage_ = 10;
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


// Chooses the path with the nearest tower
QList<QPointF> Kylteri::ChoosePath(QList<QList<QPointF>> paths) {
    QList<QPointF> path_with_nearest_tower;
    int shortest_dist = 1000;
    if(game_->GetTowers().isEmpty()) {
        return paths[0];
    }
    for(auto path : paths) {
        QPointF first_point = path[0];
        for(auto tower : game_->GetTowers()) {
            QLineF ln(tower->pos(), first_point);
            if(ln.length() < shortest_dist) {
                path_with_nearest_tower = path;
                shortest_dist = ln.length();
            }
        }
    }
    return path_with_nearest_tower;
};