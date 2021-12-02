#include "menu.hpp"

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

#include "game.hpp"
#include "editor.hpp"

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300

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
    QPushButton* CustomButton = new QPushButton(QString("CUSTOM LEVEL"), this);
	QPushButton* EditorButton = new QPushButton(QString("LEVEL EDITOR"), this);

    Level1Button->move(WINDOW_WIDTH / 2 - Level1Button->width() / 2, 10);
	Level2Button->move(WINDOW_WIDTH / 2 - Level2Button->width() / 2, 40);
    Level3Button->move(WINDOW_WIDTH / 2 - Level3Button->width() / 2, 70);
    Level4Button->move(WINDOW_WIDTH / 2 - Level4Button->width() / 2, 100);
    Level5Button->move(WINDOW_WIDTH / 2 - Level5Button->width() / 2, 130);

    CustomButton->move(WINDOW_WIDTH / 2 - CustomButton->width() / 2 , 160);
	EditorButton->move(WINDOW_WIDTH / 2 - Level5Button->width() / 2, 190);
    
	connect(Level1Button, SIGNAL(clicked()), this, SLOT(StartLevel1()));
	connect(Level2Button, SIGNAL(clicked()), this, SLOT(StartLevel2()));
	connect(Level3Button, SIGNAL(clicked()), this, SLOT(StartLevel3()));
	connect(Level4Button, SIGNAL(clicked()), this, SLOT(StartLevel4()));
	connect(Level5Button, SIGNAL(clicked()), this, SLOT(StartLevel5()));
	connect(CustomButton, SIGNAL(clicked()), this, SLOT(StartCustom()));
	connect(EditorButton, SIGNAL(clicked()), this, SLOT(StartEditor()));


    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // No vertical nor horizontal scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

QGraphicsScene* Menu::GetScene() {
    return scene_;
}

void Menu::mousePressEvent(QMouseEvent* event) {
        QGraphicsView::mousePressEvent(event);
}

QList<QList<QPointF>> Menu::ReadPathsFromFile(const QString& filename) {
	QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);    // read the data serialized from the file
    qint32 n_paths;
	in >> n_paths;
	QList<QList<QPointF>> path_list;
	for (int i = 0; i < n_paths; i++) {
		qint32 n_points;
		in >> n_points;
		QList<QPointF> ith_path;
		for (int j = 0; j < n_points; j++) {
			qint32 point_x;
            qint32 point_y;
			in >> point_x >> point_y;
			ith_path << QPointF(point_x,point_y);
			//qDebug() << "added point:" << QPointF(point_x,point_y);
		}
		path_list << ith_path;
	}
	file.close();
	return path_list;
}

void Menu::StartLevel1() {
	QList<QList<QPointF>> paths = ReadPathsFromFile(":levels/level1.dat");
    Game* game = new Game(paths);
	game->show();
}
void Menu::StartLevel2() {
	QList<QList<QPointF>> paths = ReadPathsFromFile(":levels/level2.dat");
    Game* game = new Game(paths);
	game->show();
}
void Menu::StartLevel3() {
	QList<QList<QPointF>> paths = ReadPathsFromFile(":levels/level3.dat");
    Game* game = new Game(paths);
	game->show();
}
void Menu::StartLevel4() {
	QList<QList<QPointF>> paths = ReadPathsFromFile(":levels/level4.dat");
    Game* game = new Game(paths);
	game->show();
}
void Menu::StartLevel5() {
	QList<QList<QPointF>> paths = ReadPathsFromFile(":levels/level5.dat");
    Game* game = new Game(paths);
	game->show();
}

void Menu::StartCustom() {
	if (QFile::exists("custom_level.dat")) {
		QList<QList<QPointF>> paths = ReadPathsFromFile("custom_level.dat");
		Game* game = new Game(paths);
		game->show();
	} else {
		qDebug() << "Create a custom level in the level editor first!";
	}
}

void Menu::StartEditor() {
	// Level Editor
	// THIS WILL CAUSE A MEMORY LEAK FOR SURE
    Editor* editor = new Editor();
    editor->show();
}

