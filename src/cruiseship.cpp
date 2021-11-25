#include "cruiseship.hpp"

#include <qmath.h>
#include "koneteekkari.hpp"
#include "fyysikko.hpp"
#include "bullet.hpp"


Cruiseship::Cruiseship(QList<QPointF> pathPoints, Game* game, QGraphicsItem* parent) : Enemy(pathPoints, game) {
    QPixmap p = QPixmap(":/images/cruiseship.png");
    p = p.scaled(50, 100, Qt::KeepAspectRatio); // Set size for the enemy
    setPixmap(p);
    setOffset(-p.width() / 2, -p.height() / 2); // Centering

    enemy_hp_ = 10;
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
                game_->SetMoney(game_->GetMoney() + 10);
                game_->SetMoneyText(QString(" MONEY: ") + QString::number(game_->GetMoney()));

                // Spawn new enemies
                Koneteekkari* k = new Koneteekkari(game_->GetPathPoints(), game_);
                Fyysikko* f = new Fyysikko(game_->GetPathPoints(), game_);
                game_->GetScene()->addItem(k);
                game_->GetScene()->addItem(f);

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