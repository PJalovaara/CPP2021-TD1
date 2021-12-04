#include "dokaani.hpp"
#include "bullet.hpp"
#include <qmath.h>


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

void Dokaani::MoveForward() {
    // If close to dest, rotate towards the next dest
    QLineF ln(pos(), dest_);

    // Getting hit by a bullet destroys the enemy
    // List of items within the attack_area
    QList<QGraphicsItem*> colliding_items = this->collidingItems();

    for(auto item : colliding_items) {
        // Do dynamic casting to deduce whether we have a tower or an enemy
        Bullet* bullet = dynamic_cast<Bullet*>(item);
        if(bullet) { // If cast is successful
            enemy_hp_ -= bullet->GetDamage();
            delete bullet;
            if(enemy_hp_ <= 0){ // If enemy dies
                game_->SetMoney(game_->GetMoney() + price_);
                game_->UpdateMoneyText();
                game_->PlayDokaaniDiesSfx();
                delete this;
                return;
            }
        }
    }
    
    // If enemy reaches final destination, the player loses hp and the memory is freed
    if(ln.length() < 30 && point_index_ >= path_points_.length() - 1) {
        QProgressBar* health_bar = game_->GetHealthBar();
        int current_health = health_bar->value();
        if(current_health - damage_ >= 0) {
            health_bar->setValue(current_health - damage_);
            health_bar->setFormat(" HP: " + QString::number(current_health - damage_));
        } else {
            health_bar->setValue(0);
            health_bar->setFormat(" HP: " + QString::number(0));
        }
		delete this;
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