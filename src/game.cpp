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
#include <QPalette>

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

Game::Game(QList<QList<QPointF>> paths) {
    // Creating a scene and a timer to spawn enemies on the pathPoints path
    scene_ = new QGraphicsScene(this);
    enemy_spawn_timer_ = new QTimer(this);
    paths_ = paths;

    // Set the scene
    setScene(scene_); // Visualize this scene
    scene_->setSceneRect(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);

    // Add a grey background for better visibility
    QBrush grayBrush(Qt::gray);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    scene_->addRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, blackPen, grayBrush);

    // Initialize update and delete buttons and the red selection rectangle
    upgrade_button_ = nullptr;
    delete_button_ = nullptr;
    selected_tower_rect_ = nullptr;

    // Create start and clear buttons
    QPushButton* start_button = new QPushButton(QString("START"), this);
    QPushButton* clear_button = new QPushButton(QString("CLEAR"), this);

    start_button->move(WINDOW_WIDTH / 2 - start_button->width() / 2, 10);
    clear_button->move(WINDOW_WIDTH / 2 - start_button->width() / 2, 40);
    

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
    money_text_->setText(QString(" MONEY: $") + QString::number(money_));
    money_text_->setReadOnly(true);
    money_text_->setStyleSheet("QLineEdit {color: black; font: bold; background: rgba(0, 0, 0, 50);}");

     // Initialize the wave and last_wave and create text
    wave_ = 0;
    last_wave_ = 50;
    wave_text_ = new QLineEdit(this);
    wave_text_->move(10, WINDOW_HEIGHT - health_bar_->height() - money_text_->height() - wave_text_->height());
    wave_text_->setText(QString(" WAVE: ") + QString::number(wave_) + QString("/") + QString::number(last_wave_));
    wave_text_->setReadOnly(true);
    wave_text_->setStyleSheet("QLineEdit {color: black; font: bold; background: rgba(0, 0, 0, 50);}");


    // Create a path for the enemies
    CreatePaths();

    // Add the build icons and their prices
    BuildMamaIcon* mama_icon = new BuildMamaIcon(this);
    mama_icon->setPos(50,50);
    scene_->addItem(mama_icon);
    QLineEdit* mama_price_text = new QLineEdit(this);
    mama_price_text->setReadOnly(true);
    mama_price_text->setAlignment(Qt::AlignCenter);
    mama_price_text->setText(QString("$") + QString::number(100));
    mama_price_text->move(0, 100);
    mama_price_text->setStyleSheet("QLineEdit {color: black; font: bold; background: rgba(0, 0, 0, 50); width: 100 px}");

    BuildSniperIcon* sniper_icon = new BuildSniperIcon(this);
    sniper_icon->setPos(50, 170);
    scene_->addItem(sniper_icon);
    QLineEdit* sniper_price_text = new QLineEdit(this);
    sniper_price_text->setReadOnly(true);
    sniper_price_text->setAlignment(Qt::AlignCenter);
    sniper_price_text->setText(QString("$") + QString::number(200));
    sniper_price_text->move(0, 200);
    sniper_price_text->setStyleSheet("QLineEdit {color: black; font: bold; background: rgba(0, 0, 0, 50); width: 100 px}");


    // Set cursor and build ptr to nullptr and turn on mouse tracking
    cursor_ = nullptr;
    build_ = nullptr;
    setMouseTracking(true);

    // Creates 5 enemies, one every second
    connect(start_button, SIGNAL(clicked()), this, SLOT(StartWave()));

    // Connect CLEAR button to the slot ClearTowers
    connect(clear_button, SIGNAL(clicked()), this, SLOT(ClearTowers()));
    
    // Initialize sound effects
    enemy_dies_sfx_.setSource(QUrl::fromLocalFile(":/sfx/antinblop.wav"));
    cruiseship_dies_sfx_.setSource(QUrl::fromLocalFile(":/sfx/aadanblop.wav"));


    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // No vertical nor horizontal scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    // Test code: Create a cruiseship and dokaani
    Cruiseship* cruiseship = new Cruiseship(paths_, this);
    scene_->addItem(cruiseship);

    // Dokaani* dok = new Dokaani(path_points_, this);
    // scene_->addItem(dok);
}

Game::~Game() {
    ClearTowers();
};


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
        // Find the closest tower to the click position
        QPointF clickPos = event->pos();
        double closest_dist = 100;
        closest_tower_ = nullptr;
        for(auto tower : towers_) {
            QLineF ln(tower->pos(), clickPos);
            if(ln.length() < closest_dist) {
                closest_dist = ln.length();
                closest_tower_ = tower;
            }
        }
        if(closest_tower_ && !upgrade_button_) {
            // Create update and delete buttons here

            // Top left corner coordinates
            int x_coord = closest_tower_->x() - closest_tower_->GetWidth() / 2;
            int y_coord = closest_tower_->y() - closest_tower_->GetHeight() / 2;

            selected_tower_rect_ = new QGraphicsRectItem(x_coord, y_coord, closest_tower_->GetWidth(), closest_tower_->GetHeight());
            QPen redPen(Qt::red);
            redPen.setWidth(2);
            selected_tower_rect_->setPen(redPen);
            scene_->addItem(selected_tower_rect_);

            upgrade_button_ = new QPushButton(QString("UPGRADE ($50)"), this);
            delete_button_ = new QPushButton(QString("DELETE"), this);
            int upgrade_x = x_coord + closest_tower_->GetWidth() > WINDOW_WIDTH ? x_coord - upgrade_button_->width() : x_coord + closest_tower_->GetWidth();
            int upgrade_y = y_coord < 0 ? 0 : y_coord;
            int delete_y = y_coord + closest_tower_->GetHeight() > WINDOW_HEIGHT ? WINDOW_HEIGHT - delete_button_->height() : y_coord + closest_tower_->GetHeight() - delete_button_->height();
            upgrade_button_->move(upgrade_x, upgrade_y);
            delete_button_->move(upgrade_x, delete_y);
            upgrade_button_->show();
            delete_button_->show();

            connect(upgrade_button_, SIGNAL(clicked()), this, SLOT(UpgradeTower()));
            connect(delete_button_, SIGNAL(clicked()), this, SLOT(RemoveTower()));
        } else {
            if(upgrade_button_) {
                delete upgrade_button_;
                upgrade_button_ = nullptr;
            }
            if(delete_button_) {
                delete delete_button_;
                delete_button_ = nullptr;
            }
            if(selected_tower_rect_) {
                delete selected_tower_rect_;
                selected_tower_rect_ = nullptr;
            }
        }
        QGraphicsView::mousePressEvent(event);
    }
};

Tower* Game::GetBuild() {
    return build_;
};

void Game::StartWave() {
    wave_++;
    CreateEnemies();
}

void Game::CreateEnemies() {
    enemies_spawned_ = 0;
    max_no_of_enemies_ = 5;
    connect(enemy_spawn_timer_, SIGNAL(timeout()), this, SLOT(SpawnFyysikko()));
    enemy_spawn_timer_->start(1000); // spawn an enemy every 1000 ms
};

void Game::SpawnFyysikko() {
    Enemy* enemy = new Fyysikko(paths_, this);
    scene_->addItem(enemy);
    enemies_spawned_ += 1;

    // Have we spawned enough enemies?
    if(enemies_spawned_ >= max_no_of_enemies_) {
        enemy_spawn_timer_->disconnect();
    }
}


void Game::CreatePaths() {
    for(auto path_points : paths_){
        for(int i = 0; i < path_points.size() - 1; i++){
            QLineF line(path_points[i], path_points[i+1]);
            QGraphicsLineItem* lineItem = new QGraphicsLineItem(line);

            QPen pen;
            pen.setWidth(50); // Width of the drawn path/line
            pen.setColor(Qt::darkBlue); // Set the color of the path
            lineItem->setPen(pen);

            scene_->addItem(lineItem);
        }
    }
};

void Game::ClearTowers() {
    for(auto tower : towers_) {
        closest_tower_ = tower;
        RemoveTower();
    }
    towers_.clear();
};

QProgressBar* Game::GetHealthBar() {
    return health_bar_;
};


int Game::GetMoney() {
    return money_;
};

void Game::UpdateMoneyText() {
    money_text_->setText(QString(" MONEY: $") + QString::number(GetMoney()));
};


void Game::SetMoney(int new_money) {
    money_ = new_money;
};

QList<QList<QPointF>> Game::GetPaths() {
    return paths_;
};

void Game::UpgradeTower() {
    if(money_ - 50 >= 0) {
        closest_tower_->UpgradeAttackRadius(closest_tower_->GetAttackRadius() + 20);
        money_ -= 50;
        UpdateMoneyText();
    }
};

void Game::RemoveTower() {
    if(delete_button_) {
        delete delete_button_;
    }
    if(upgrade_button_) {
        delete upgrade_button_;
    }
    if(selected_tower_rect_) {
        delete selected_tower_rect_;
    }
    delete_button_ = nullptr;
    upgrade_button_ = nullptr;
    selected_tower_rect_ = nullptr;
    towers_.removeOne(closest_tower_);
	scene_->removeItem(closest_tower_);
    closest_tower_ = nullptr;
};

void Game::PlayEnemyDiesSfx() {
    enemy_dies_sfx_.play();
};

void Game::PlayCruiseshipDiesSfx() {
    cruiseship_dies_sfx_.play();
};