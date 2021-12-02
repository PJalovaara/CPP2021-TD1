#include "menu.hpp"
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

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Menu::Menu() {
    // Set the scene
	scene_ = new QGraphicsScene(this);
    setScene(scene_); // Visualize this scene
    scene_->setSceneRect(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);

    // Add a grey background for better visibility
    QBrush grayBrush(Qt::gray);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    scene_->addRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, blackPen, grayBrush);

    QPushButton* Level1Button = new QPushButton(QString("LEVEL 1"), this);
	QPushButton* Level2Button = new QPushButton(QString("LEVEL 2"), this);
	QPushButton* Level3Button = new QPushButton(QString("LEVEL 3"), this);
	QPushButton* Level4Button = new QPushButton(QString("LEVEL 4"), this);
	QPushButton* Level5Button = new QPushButton(QString("LEVEL 5"), this);
    QPushButton* LoadButton = new QPushButton(QString("LOAD LEVEL"), this);

    Level1Button->move(WINDOW_WIDTH / 2 - Level1Button->width() / 2, 10);
	Level2Button->move(WINDOW_WIDTH / 2 - Level2Button->width() / 2, 40);
    Level3Button->move(WINDOW_WIDTH / 2 - Level3Button->width() / 2, 70);
    Level4Button->move(WINDOW_WIDTH / 2 - Level4Button->width() / 2, 100);
    Level5Button->move(WINDOW_WIDTH / 2 - Level5Button->width() / 2, 130);

    LoadButton->move(WINDOW_WIDTH / 2 - LoadButton->width() / 2, 160);
    
	connect(Level1Button, SIGNAL(clicked()), this, SLOT(level1()));
	connect(Level2Button, SIGNAL(clicked()), this, SLOT(level2()));
	connect(Level3Button, SIGNAL(clicked()), this, SLOT(level3()));
	connect(Level4Button, SIGNAL(clicked()), this, SLOT(level4()));
	connect(Level5Button, SIGNAL(clicked()), this, SLOT(level5()));


    cursor_ = nullptr;
    setMouseTracking(true);

    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // No vertical nor horizontal scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


QGraphicsScene* Menu::GetScene() {
    return scene_;
};
    
QGraphicsPixmapItem* Menu::GetCursor() {
    return cursor_;
};

void Menu::mouseMoveEvent(QMouseEvent* event) {
    if(cursor_) {
        cursor_->setPos(event->pos());
    }
};

void Menu::SetCursor(QString filename) {
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

void Menu::ResetCursor() {
    if(cursor_) {
        scene_->removeItem(cursor_);
        delete cursor_;
    }
    cursor_ = nullptr;
};

void Menu::mousePressEvent(QMouseEvent* event) {
        QGraphicsView::mousePressEvent(event);
};

void Menu::level1() {
	QList<QPointF> points;
	points << QPoint(800, 0) << QPoint(400, 300) << QPoint(800, 600);
    Game* game = new Game(points);
	game->show();
}
void Menu::level2() {
	QList<QPointF> points;
	points << QPoint(800, 0) << QPoint(400, 300) << QPoint(800, 600);
    Game* game = new Game(points);
	game->show();
}
void Menu::level3() {
	QList<QPointF> points;
	points << QPoint(800, 0) << QPoint(400, 300) << QPoint(800, 600);
    Game* game = new Game(points);
	game->show();
}
void Menu::level4() {
	QList<QPointF> points;
	points << QPoint(800, 0) << QPoint(400, 300) << QPoint(800, 600);
    Game* game = new Game(points);
	game->show();
}
void Menu::level5() {
	QList<QPointF> points;
	points << QPoint(800, 0) << QPoint(400, 300) << QPoint(800, 600);
    Game* game = new Game(points);
	game->show();
}