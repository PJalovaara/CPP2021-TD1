#include "dokaani.hpp"
#include "bullet.hpp"
#include <qmath.h>


Dokaani::Dokaani(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent) : Enemy(game) {
    QPixmap p = QPixmap(":/images/dokaani.png");
    p = p.scaled(180, 180, Qt::KeepAspectRatio); // Set size for the enemy
    setPixmap(p);
    setOffset(-p.width() / 2, -p.height() / 2); // Centering

    // Destroying a dokaani is difficult and dokaani getting to destination damages the goose a lot
    enemy_hp_ = 30;
    damage_ = 30;
    price_ = 75;
    speed_ = 3;

        // Set the points in the path
    path_points_ = ChoosePath(paths);

    // Set initial pos and initial destination
    this->setPos(path_points_[0]); // Start from the first point in the path
    point_index_ = 1;
    dest_ = path_points_[point_index_];

    RotateToFacePoint(dest_);
};

void Dokaani::Death() {
    game_->SetMoney(game_->GetMoney() + price_);
    game_->UpdateMoneyText();
    game_->PlayDokaaniDiesSfx();
};


QList<QPointF> Dokaani::ChoosePath(QList<QList<QPointF>> paths) {
    // Chooses the longest path
    int max_path_length = 0;
    int max_path_length_index = 0;
    for(int path_index = 0; path_index < paths.size(); path_index++) {
        QList<QPointF> path = paths[path_index];
        int path_length = 0;
        for(int i = 0; i < path.size() - 1; i++) {
            QLineF ln(path[i], path[i+1]);
            path_length += ln.length();
        }
        if(path_length > max_path_length) {
            max_path_length = path_length;
            max_path_length_index = path_index;
        }
    }
    return paths[max_path_length_index];
};