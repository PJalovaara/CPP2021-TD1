#include <enemy.hpp>

#include <QPixmap>
#include <QTimer>
#include <QString>
#include <qmath.h>
#include <QDebug>

#include <bullet.hpp>

Enemy::Enemy(QList<QPointF> pathPoints, Game* game, QGraphicsItem* parent) {
    game_ = game;
    // Set graphics
    QPixmap p = QPixmap(":/images/fyssa1.png");
    p = p.scaled(50, 100, Qt::KeepAspectRatio); // Set size for the enemy
    setPixmap(p);
    setOffset(-p.width() / 2, -p.height() / 2); // Centering

    // Initialize enemy damage, enemy hp and price
    enemy_hp_ = 5;
    damage_ = 10;
    price_ = 10;

    // Set the points in the path
    path_points_ = pathPoints;

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
    
void Enemy::RotateToFacePoint(QPointF p) {
    QLineF ln(pos(), p);
    // Note that ln.angle() will return the the angle in counterclockwise direction but setRotation is clockwise
    setRotation(-ln.angle()); //-ln.angle()
};


void Enemy::MoveForward() {
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
            if(enemy_hp_ <= 0){ // If enemy dies
                game_->SetMoney(game_->GetMoney() + price_);
                game_->SetMoneyText(QString(" MONEY: ") + QString::number(game_->GetMoney()));
                delete this;
                return;
            }
            delete bullet;
        }
    }
    
    // If enemy reaches final destination, the player loses hp and the memory is freed
    if(ln.length() < 30 && point_index_ >= path_points_.length() - 1) {
        delete this;
        QProgressBar* health_bar = game_->GetHealthBar();
        int current_health = health_bar->value();
        if(current_health - damage_ >= 0) {
            health_bar->setValue(current_health - damage_);
            health_bar->setFormat(" HP: " + QString::number(current_health - damage_));
        } else {
            health_bar->setValue(0);
            health_bar->setFormat(" HP: " + QString::number(0));
        }
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

QPointF Enemy::GetDest() {
    return dest_;
};


