#include "cruiseship.hpp"

#include <QDebug>
#include <qmath.h>

#include "koneteekkari.hpp"
#include "kylteri.hpp"
#include "fyysikko.hpp"
#include "bullet.hpp"


Cruiseship::Cruiseship(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent) : Enemy(game) {
    QPixmap p = QPixmap(":/images/cruiseship.png");
    p = p.scaled(200, 200, Qt::KeepAspectRatio);  // Set size for the enemy
    setPixmap(p);
    setOffset(-p.width() / 2, -p.height() / 2);  // Centering

    enemy_hp_ = 50;  // Has higher hp than an average enemy
    speed_ = 1;
    damage_ = 50;
    price_ = 100;

    // Set the points in the path
    path_points_ = ChoosePath(paths);

    // Set initial pos and initial destination
    this->setPos(path_points_[0]);  // Start from the first point in the path
    point_index_ = 1;
    dest_ = path_points_[point_index_];

    RotateToFacePoint(dest_);
}

void Cruiseship::Death() {
    // Update the money system
    game_->SetMoney(game_->GetMoney() + price_);
    game_->UpdateMoneyText();
    // Play "blop" by Aada
    game_->PlayCruiseshipDiesSfx();

    // Spawn new enemies where the cruiseship got destroyed
    QList<QPointF> path_points_left(path_points_.mid(point_index_ - 1, path_points_.length()));
    path_points_left[0] = pos();
    QList<QList<QPointF>> path_left;
    path_left << path_points_left;

    Fyysikko* f = new Fyysikko(path_left, game_);
    f->setPos(f->pos().x() + 10, f->pos().y());  // Some offset
    f->RotateToFacePoint(f->GetDest());
    Kylteri* kyl = new Kylteri(path_left, game_);
    f->setPos(f->pos().x(), f->pos().y() + 12);  // Some offset
    f->RotateToFacePoint(f->GetDest());

    Koneteekkari* k = new Koneteekkari(path_left, game_);

    game_->GetScene()->addItem(k);
    game_->GetScene()->addItem(f);
    game_->GetScene()->addItem(kyl);
}

void Cruiseship::CheckPoop() {
    return;
}


// Chooses the path with the furthest tower
QList<QPointF> Cruiseship::ChoosePath(QList<QList<QPointF>> paths) {
    QList<QPointF> path_with_furthest_tower;
    int furthest_dist = 0;
    if (game_->GetTowers().isEmpty()) {
        return paths[0];
    }
    for (auto path : paths) {
        QPointF first_point = path[0];
        for (auto tower : game_->GetTowers()) {
            QLineF ln(tower->pos(), first_point);
            if (ln.length() > furthest_dist) {
                path_with_furthest_tower = path;
                furthest_dist = ln.length();
            }
        }
    }
    return path_with_furthest_tower;
}
