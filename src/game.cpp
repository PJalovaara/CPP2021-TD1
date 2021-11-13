#include "game.hpp"
#include "tower.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "build_tower_icon.hpp"

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
// #include <QBrush>
// #include <QPen>
// #include <QDebug>

Game::Game() {
    // Creating a scene 
    scene_ = new QGraphicsScene(this);

    // Set the scene
    setScene(scene_); // Visualize this scene
    scene_->setSceneRect(0,0,800,600);

    // Add a grey background for better visibility
    QBrush grayBrush(Qt::gray);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    
    scene_->addRect(0, 0, 800, 600, blackPen, grayBrush);

    BuildTowerIcon* icon = new BuildTowerIcon(this);
    scene_->addItem(icon);
    // Set cursor and build ptr to nullptr
    cursor_ = nullptr;
    build_ = nullptr;
    // Test code with the SniperGoose.pngs
    //SetCursor(":images/SniperGoose.png");
    setMouseTracking(true);

    

    // Create a new tower
    Tower* t = new Tower(scene_);
    //t->UpdateAttackRadius(2000);
    t->setPos(200,150);

    // Create an enemy
    Enemy* e = new Enemy();
    scene_->addItem(e);

 
    // Add tower to the scene 
    scene_->addItem(t);

    setFixedSize(800, 600);
    // No vertical nor horizontal scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

// QGraphicsScene* Game::GetScene(){
//     return scene_;
// }

QGraphicsScene* Game::GetScene() {
    return scene_;
};
    
QGraphicsPixmapItem* Game::GetCursor() {
    return cursor_;
};

void Game::mouseMoveEvent(QMouseEvent* event) {
    if(cursor_) {
        cursor_->setPos(event->pos());
    }
};

void Game::SetCursor(QString filename) {
    if(cursor_) {
        scene_->removeItem(cursor_);
        delete cursor_;
    }
    cursor_ = new QGraphicsPixmapItem();
    QPixmap p = QPixmap(filename);
    p = p.scaled(200, 100, Qt::KeepAspectRatio);
    cursor_->setPixmap(p);
    scene_->addItem(cursor_);
};

void Game::ResetCursor() {
    if(cursor_) {
        scene_->removeItem(cursor_);
        delete cursor_;
    }
    cursor_ = nullptr;
};

void Game::SetBuild(Tower* newBuild) {
    build_ = newBuild;
};

void Game::mousePressEvent(QMouseEvent* event) {
    if(build_){
        scene_->addItem(build_);
        build_->setPos(event->pos());
        ResetCursor();
        build_ = nullptr;
    } else {
        QGraphicsView::mousePressEvent(event);
    }
};

Tower* Game::GetBuild() {
    return build_;
};