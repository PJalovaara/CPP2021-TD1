#include "game.hpp"

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QPixmap>
#include <QLineF>
#include <QBrush>
#include <QPen>
#include <QPushButton>

#include "tower.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "build_mama_icon.hpp"
#include "build_sniper_icon.hpp"
#include "mamagoose.hpp"
#include "snipergoose.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Game::Game() {
    // Creating a scene and a timer to spawn enemies on the pathPoints path
    scene_ = new QGraphicsScene(this);
    enemySpawnTimer_ = new QTimer(this);
    pathPoints_ << QPoint(800,0) << QPoint(400,300) << QPoint(800, 600);

    // Set the scene
    setScene(scene_); // Visualize this scene
    scene_->setSceneRect(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);

    // Add a grey background for better visibility
    QBrush grayBrush(Qt::gray);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    scene_->addRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, blackPen, grayBrush);

    // Create a start button
    QPushButton* startButton = new QPushButton(QString("START"), this);
    QPushButton* clearButton = new QPushButton(QString("CLEAR"), this);

    startButton->move(WINDOW_WIDTH / 2 - startButton->width() / 2, 10);
    clearButton->move(WINDOW_WIDTH / 2 - startButton->width() / 2, 40);

    // Create a path for the enemies
    CreatePath();

    // Add the build icons
    BuildMamaIcon* mama_icon = new BuildMamaIcon(this);
    scene_->addItem(mama_icon);

    BuildSniperIcon* sniper_icon = new BuildSniperIcon(this);
    sniper_icon->setPos(0,100);
    scene_->addItem(sniper_icon);


    // Set cursor and build ptr to nullptr
    cursor_ = nullptr;
    build_ = nullptr;
    // Test code with the SniperGoose.pngs
    //SetCursor(":images/SniperGoose.png");
    setMouseTracking(true);

    // Creates 5 enemies, one every second
    connect(startButton, SIGNAL(clicked()), this, SLOT(CreateEnemies()));

    // Connect CLEAR button to the slot ClearTowers
    connect(clearButton, SIGNAL(clicked()), this, SLOT(ClearTowers()));
    
 

    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // No vertical nor horizontal scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


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
        towers_ << build_;
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

void Game::CreateEnemies() {
    enemiesSpawned_ = 0;
    maxNoOfEnemies_ = 5;
    connect(enemySpawnTimer_, SIGNAL(timeout()), this, SLOT(SpawnEnemy()));
    enemySpawnTimer_->start(1000); // spawn an enemy every 1000 ms
};

void Game::SpawnEnemy() {
    Enemy* enemy = new Enemy(pathPoints_);
    enemy->setPos(pathPoints_[0]); // Start from the first point of the path
    scene_->addItem(enemy);
    enemiesSpawned_ += 1;

    // Have we spawned enough enemies?
    if(enemiesSpawned_ >= maxNoOfEnemies_) {
        enemySpawnTimer_->disconnect();
    }
}


void Game::CreatePath() {
    for(int i = 0; i < pathPoints_.size() - 1; i++){
        QLineF line(pathPoints_[i], pathPoints_[i+1]);
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(line);

        QPen pen;
        pen.setWidth(50); // Width of the drawn path/line
        pen.setColor(Qt::darkBlue); // Set the color of the path
        lineItem->setPen(pen);

        scene_->addItem(lineItem);
    }
};

void Game::ClearTowers() {
    for(auto i : towers_) {
        delete i;
    }
    towers_.clear();
};