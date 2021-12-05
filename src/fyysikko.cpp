#include "fyysikko.hpp"

#include <QDebug>

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
};


// Chooses the shortest path
QList<QPointF> Fyysikko::ChoosePath(QList<QList<QPointF>> paths) {
    int min_path_length = 0;
    int min_path_length_index = 0;
    for(int path_index = 0; path_index < paths.size(); path_index++) {
        QList<QPointF> path = paths[path_index];
        int path_length = 0;
        for(int i = 0; i < path.size() - 1; i++) {
            QLineF ln(path[i], path[i+1]);
            path_length += ln.length();
        }
        if(path_index == 0) {
            min_path_length = path_length;
        }
        if(path_length < min_path_length) {
            min_path_length = path_length;
            min_path_length_index = path_index;
        }
    }
    return paths[min_path_length_index];
};