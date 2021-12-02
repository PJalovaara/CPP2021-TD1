#include "cruiseship.hpp"

#include <qmath.h>
#include "koneteekkari.hpp"
#include "kylteri.hpp"
#include "fyysikko.hpp"
#include "bullet.hpp"

#include <QDebug>

Cruiseship::Cruiseship(QList<QList<QPointF>> paths, Game* game, QGraphicsItem* parent) : Enemy(game) {
    QPixmap p = QPixmap(":/images/cruiseship.png");
    p = p.scaled(50, 100, Qt::KeepAspectRatio); // Set size for the enemy
    setPixmap(p);
    setOffset(-p.width() / 2, -p.height() / 2); // Centering

    enemy_hp_ = 50; // Has higher hp than an average enemy
    speed_ = 1;
    damage_ = 50;
    price_ = 100;

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


void Cruiseship::MoveForward() {
    // If close to dest, rotate towards the next dest
    // TO DO: If enemy reaches final destination, player loses HP
    QLineF ln(pos(), dest_);

    // Getting hit by a bullet destroys the enemy
    // List of items within the attack_area
    QList<QGraphicsItem*> colliding_items = this->collidingItems();

    for(auto item : colliding_items) {
        // Do dynamic casting to deduce whether we have a tower or an enemy
        Bullet* bullet = dynamic_cast<Bullet*>(item);
        if(bullet) { // If cast is successful
            // Decrease the enemy hp by the bullet damage 
            enemy_hp_ -= bullet->GetDamage();
            if(enemy_hp_ <= 0) { // If enemy dies
                // Update the money system
                game_->SetMoney(game_->GetMoney() + price_);
                game_->UpdateMoneyText();

                // Spawn new enemies where the cruiseship got destroyed
                QList<QPointF> path_points_left(path_points_.mid(point_index_ - 1, path_points_.length()));
                path_points_left[0] = pos();
                QList<QList<QPointF>> path_left;
                path_left << path_points_left;

                Fyysikko* f = new Fyysikko(path_left, game_);
                f->setPos(f->pos().x() + 10, f->pos().y()); // Some offset
                f->RotateToFacePoint(f->GetDest());
                Kylteri* kyl = new Kylteri(path_left, game_);
                f->setPos(f->pos().x(), f->pos().y() + 12); // Some offset
                f->RotateToFacePoint(f->GetDest());

                Koneteekkari* k = new Koneteekkari(path_left, game_);

                game_->GetScene()->addItem(k);
                game_->GetScene()->addItem(f);
                game_->GetScene()->addItem(kyl);

                // Free the memory
                delete this;
                return;
            }
            

            delete bullet;
        }
    }
    
    // If enemy reaches final destination, the player loses hp and the memory is freed
    if(ln.length() < 50 && point_index_ >= path_points_.length() - 1) {
        delete this;
        QProgressBar* health_bar = game_->GetHealthBar();
        int current_health = health_bar->value();
        health_bar->setValue(current_health - damage_);
        health_bar->setFormat(" HP: " + QString::number(current_health - damage_));
        return;
    }

    // Rotate to face the next point
    if(ln.length() < 10 && point_index_ < path_points_.length() - 1){ // Check the size of the radius
        point_index_++;
        dest_ = path_points_[point_index_];
        RotateToFacePoint(dest_);
    }
    
    // Move enemy forwards with its current angle
    double theta = rotation(); // return the angle in degrees
    double dy = speed_ * qSin(qDegreesToRadians(theta));
    double dx = speed_ * qCos(qDegreesToRadians(theta));
    setPos(x() + dx, y() + dy);
};


QList<QPointF> Cruiseship::ChoosePath(QList<QList<QPointF>> paths) {
    return paths[0];
};