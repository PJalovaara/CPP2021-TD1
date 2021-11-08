#include "game.hpp"
#include "tower.hpp"
#include "square_tower.hpp"

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

Game::Game() {
    // Creating a scene 
    scene = new QGraphicsScene(this);

    // Set the scene
    setScene(scene); // Visualize this scene

    // Create a new tower
    Tower* t = new Tower();
    t->UpdateAttackRadius(2000);

    // // Add tower to the scene
    // scene->addItem(t);

    //QGraphicsRectItem* rect = new QGraphicsRectItem();
    // rect->setRect(0,0, 100, 100);

    // QBrush redBrush(Qt::red);
    // QPen blackPen(Qt::black);
    // blackPen.setWidth(6);
    

    scene->addRect(0,0, 200, 200, blackPen, redBrush);

    // SquareTower* st = new SquareTower();
    // st->setRect(50,50, 50, 50);

    // scene->addItem(st);

    // st->setFlag(QGraphicsItem::ItemIsFocusable);
    // st->setFocus();

 
    
    // Add tower to the scene
    scene->addItem(t);
    //scene->addItem(rect);
}