#include "game.hpp"
#include "tower.hpp"
#include "square_tower.hpp"
#include "bullet.hpp"

#include <QGraphicsRectItem>
// #include <QBrush>
// #include <QPen>
// #include <QDebug>

Game::Game() {
    // Creating a scene 
    scene = new QGraphicsScene(this);

    // Set the scene
    setScene(scene); // Visualize this scene
    scene->setSceneRect(0,0,800,600);

    // Create a new tower
    Tower* t = new Tower(this);
    t->UpdateAttackRadius(2000);
    t->setPos(200,150);


    // QBrush redBrush(Qt::red);
    // QPen blackPen(Qt::black);
    // blackPen.setWidth(6);
    
    // scene->addRect(0, 0, 200, 200, blackPen, redBrush);

    // SquareTower* st = new SquareTower();
    // st->setRect(50,50, 50, 50);
    // scene->addItem(st);
    // st->setFlag(QGraphicsItem::ItemIsFocusable);
    // st->setFocus();

 
    
    // Add tower to the scene 
    scene->addItem(t);

    setFixedSize(800, 600);
    // No vertical nor horizontal scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

}

// QGraphicsScene* Game::GetScene(){
//     return scene_;
// }

void Game::mousePressEvent(QMouseEvent* event){
    // Create the bullet
    Bullet* bullet = new Bullet();
    bullet->setPos(event->pos());
    bullet->setRotation(30); // Rotate 30 degrees clockwise
    scene->addItem(bullet);
    //qDebug() << "Mouse pressed";
}