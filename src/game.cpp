#include "game.hpp"

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QPixmap>
#include <QLineF>
#include <QBrush>
#include <QPen>
#include <QPushButton>
#include <QProgressBar>
#include <QLineEdit>
#include <QDebug>

#include "tower.hpp"
#include "bullet.hpp"
#include "enemy.hpp"
#include "build_mama_icon.hpp"
#include "build_sniper_icon.hpp"
#include "mamagoose.hpp"
#include "snipergoose.hpp"
#include "cruiseship.hpp"
#include "fyysikko.hpp"
#include "kylteri.hpp"
#include "koneteekkari.hpp"
#include "dokaani.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Game::Game() {
    // Creating a scene and a timer to spawn enemies on the pathPoints path
    scene_ = new QGraphicsScene(this);
    enemy_spawn_timer_ = new QTimer(this);
    path_points_ << QPoint(800,0) << QPoint(400,300) << QPoint(800, 600);

    // Set the scene
    setScene(scene_); // Visualize this scene
    scene_->setSceneRect(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);

    // Add a grey background for better visibility
    QBrush grayBrush(Qt::gray);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    scene_->addRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, blackPen, grayBrush);

    // Create start and clear buttons
    QPushButton* startButton = new QPushButton(QString("START"), this);
    QPushButton* clearButton = new QPushButton(QString("CLEAR"), this);

    startButton->move(WINDOW_WIDTH / 2 - startButton->width() / 2, 10);
    clearButton->move(WINDOW_WIDTH / 2 - startButton->width() / 2, 40);
    

    // Create a health bar for the player
    health_bar_ = new QProgressBar(this);
    health_bar_->move(10, WINDOW_HEIGHT - health_bar_->height());
    health_bar_->setValue(100);
    health_bar_->setAlignment(Qt::AlignVCenter);
    health_bar_->setFormat(" HP: " + QString::number(health_bar_->value()));
    QString style_sheet = QString("QProgressBar::chunk {background-color: rgb(50,150,50); width: 20 px;} QProgressBar {color: black; font: bold;}");
    health_bar_->setStyleSheet(style_sheet);

    // Initialize the amount of money to 200 and create a text for the player money
    money_ = 200;
    money_text_ = new QLineEdit(this);
    money_text_->move(10, WINDOW_HEIGHT - health_bar_->height() - money_text_->height());
    money_text_->setText(QString(" MONEY: ") + QString::number(money_));


    // Create a path for the enemies
    CreatePath();

    // Add the build icons
    BuildMamaIcon* mama_icon = new BuildMamaIcon(this);
    mama_icon->setPos(50,50);
    scene_->addItem(mama_icon);

    BuildSniperIcon* sniper_icon = new BuildSniperIcon(this);
    sniper_icon->setPos(50,150);
    scene_->addItem(sniper_icon);


    // Set cursor and build ptr to nullptr and turn on mouse tracking
    cursor_ = nullptr;
    build_ = nullptr;
    setMouseTracking(true);

    // Creates 5 enemies, one every second
    connect(startButton, SIGNAL(clicked()), this, SLOT(CreateEnemies()));

    // Connect CLEAR button to the slot ClearTowers
    connect(clearButton, SIGNAL(clicked()), this, SLOT(ClearTowers()));
    
 

    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // No vertical nor horizontal scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    // Test code: Create a cruiseship
    // Cruiseship* cruiseship = new Cruiseship(path_points_, this);
    // scene_->addItem(cruiseship);

    Dokaani* dok = new Dokaani(path_points_, this);
    scene_->addItem(dok);
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
    cursor_->setOffset(-p.width() / 2, -p.height() / 2); // Centering
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
        towers_ << build_; // Add the new tower to the list of towers
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
    enemies_spawned_ = 0;
    max_no_of_enemies_ = 5;
    connect(enemy_spawn_timer_, SIGNAL(timeout()), this, SLOT(SpawnFyysikko()));
    enemy_spawn_timer_->start(1000); // spawn an enemy every 1000 ms
};

void Game::SpawnFyysikko() {
    Enemy* enemy = new Fyysikko(path_points_, this);
    scene_->addItem(enemy);
    enemies_spawned_ += 1;

    // Have we spawned enough enemies?
    if(enemies_spawned_ >= max_no_of_enemies_) {
        enemy_spawn_timer_->disconnect();
    }
}


void Game::CreatePath() {
    for(int i = 0; i < path_points_.size() - 1; i++){
        QLineF line(path_points_[i], path_points_[i+1]);
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

QProgressBar* Game::GetHealthBar() {
    return health_bar_;
};


int Game::GetMoney() {
    return money_;
};

void Game::SetMoneyText(const QString& text) {
    money_text_->setText(text);
};


void Game::SetMoney(int new_money) {
    money_ = new_money;
};

QList<QPointF> Game::GetPathPoints() {
    return path_points_;
};