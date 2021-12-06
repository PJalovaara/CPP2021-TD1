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
#include "buildicon.hpp"
#include "mamagoose.hpp"
#include "snipergoose.hpp"
#include "basicgoose.hpp"
#include "poopergoose.hpp"
#include "shotgungoose.hpp"
#include "cruiseship.hpp"
#include "fyysikko.hpp"
#include "kylteri.hpp"
#include "koneteekkari.hpp"
#include "dokaani.hpp"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700

// TODO: GameOver text etc, GameOver prohibits you from building more towers, Unlimited waves?

Game::Game(QList<QList<QPointF>> paths, QWidget* parent) : QGraphicsView(parent) {
    // Creating a scene and a timer to spawn enemies on the pathPoints path
    scene_ = new QGraphicsScene(this);
    enemy_spawn_timer_ = new QTimer(this);
    paths_ = paths;

    // Init booleans
    game_over_ = false;
    wave_in_progress_ = false;

    // Set the scene
    setScene(scene_);  // Visualize this scene
    scene_->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Add a grey background for better visibility
    QBrush grayBrush(Qt::gray);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    scene_->addRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, blackPen, grayBrush);

    // Initialize update and delete buttons and the red selection rectangle
    upgrade_button_ = nullptr;
    delete_button_ = nullptr;
    selected_tower_rect_ = nullptr;

    // Create a health bar for the player
    health_bar_ = new QProgressBar(this);
    health_bar_->move(10, WINDOW_HEIGHT - health_bar_->height());
    health_bar_->setValue(100);
    health_bar_->setAlignment(Qt::AlignVCenter);
    health_bar_->setFormat(" HP: " + QString::number(health_bar_->value()));
    QString style_sheet = QString("QProgressBar::chunk {background-color: rgb(50,150,50); width: 20 px;} QProgressBar {color: black; font: bold;}");
    health_bar_->setStyleSheet(style_sheet);

    // Initialize the amount of money to 200 and create a text for the player money
    money_ = 500;
    money_text_ = new QLineEdit(this);
    money_text_->move(10, WINDOW_HEIGHT - health_bar_->height() - money_text_->height());
    UpdateMoneyText();
    money_text_->setReadOnly(true);
    money_text_->setStyleSheet("QLineEdit {color: black; font: bold; background: rgba(0, 0, 0, 50);}");

     // Initialize the wave and last_wave and create text
    wave_ = 0;
    wave_text_ = new QLineEdit(this);
    wave_text_->move(10, WINDOW_HEIGHT - health_bar_->height() - money_text_->height() - wave_text_->height());
    UpdateWaveText();
    wave_text_->setReadOnly(true);
    wave_text_->setStyleSheet("QLineEdit {color: black; font: bold; background: rgba(0, 0, 0, 50);}");

    // Create start and clear buttons
    start_button_ = new QPushButton(QString("START WAVE"), this);
    clear_button_ = new QPushButton(QString("CLEAR TOWERS"), this);

    start_button_->move(10, WINDOW_HEIGHT - health_bar_->height() - money_text_->height() - wave_text_->height() - start_button_->height());
    clear_button_->move(10, WINDOW_HEIGHT - health_bar_->height() - money_text_->height() - wave_text_->height() - start_button_->height() - clear_button_->height());

    connect(start_button_, SIGNAL(clicked()), this, SLOT(StartWave()));
    connect(clear_button_, SIGNAL(clicked()), this, SLOT(ClearTowers()));


    // Create a path for the enemies
    CreatePaths();

    // Add the build icons and their prices
    BuildIcon<BasicGoose>* basic_icon = new BuildIcon<BasicGoose>(":/images/basicgoose.png", 100, this);
    basic_icon->setPos(50,50);
    scene_->addItem(basic_icon);
    QLineEdit* basic_price_text = new QLineEdit(this);
    basic_price_text->setReadOnly(true);
    basic_price_text->setAlignment(Qt::AlignCenter);
    basic_price_text->setText(QString("$") + QString::number(100));
    basic_price_text->move(0, basic_icon->pixmap().height());
    basic_price_text->setStyleSheet("QLineEdit {color: black; font: bold; background: rgba(0, 0, 0, 50); width: 100 px}");

    BuildIcon<PooperGoose>* pooper_icon = new BuildIcon<PooperGoose>(":/images/poopergoose.png", 200, this);
    pooper_icon->setPos(basic_icon->pos().x() + basic_icon->pixmap().width() + 10, 50);
    scene_->addItem(pooper_icon);
    QLineEdit* pooper_price_text = new QLineEdit(this);
    pooper_price_text->setReadOnly(true);
    pooper_price_text->setAlignment(Qt::AlignCenter);
    pooper_price_text->setText(QString("$") + QString::number(200));
    pooper_price_text->move(pooper_icon->pos().x() - pooper_price_text->width() / 2, pooper_icon->pixmap().height());
    pooper_price_text->setStyleSheet("QLineEdit {color: black; font: bold; background: rgba(0, 0, 0, 50); width: 100 px}");

    BuildIcon<ShotgunGoose>* shotgun_icon = new BuildIcon<ShotgunGoose>(":/images/shotgungoose.png", 400, this);
    shotgun_icon->setPos(pooper_icon->pos().x() + pooper_icon->pixmap().width() + 10, 50);
    scene_->addItem(shotgun_icon);
    QLineEdit* shotgun_price_text = new QLineEdit(this);
    shotgun_price_text->setReadOnly(true);
    shotgun_price_text->setAlignment(Qt::AlignCenter);
    shotgun_price_text->setText(QString("$") + QString::number(400));
    shotgun_price_text->move(shotgun_icon->pos().x() - shotgun_price_text->width() / 2, shotgun_icon->pixmap().height());
    shotgun_price_text->setStyleSheet("QLineEdit {color: black; font: bold; background: rgba(0, 0, 0, 50); width: 100 px}");

    BuildIcon<SniperGoose>* sniper_icon = new BuildIcon<SniperGoose>(":/images/snipergoose.png", 500, this);
    sniper_icon->setPos(shotgun_icon->pos().x() + shotgun_icon->pixmap().width() + 10, 50);
    scene_->addItem(sniper_icon);
    QLineEdit* sniper_price_text = new QLineEdit(this);
    sniper_price_text->setReadOnly(true);
    sniper_price_text->setAlignment(Qt::AlignCenter);
    sniper_price_text->setText(QString("$") + QString::number(500));
    sniper_price_text->move(sniper_icon->pos().x() - sniper_price_text->width() / 2, sniper_icon->pixmap().height());
    sniper_price_text->setStyleSheet("QLineEdit {color: black; font: bold; background: rgba(0, 0, 0, 50); width: 100 px}");

    BuildIcon<MamaGoose>* mama_icon = new BuildIcon<MamaGoose>(":/images/mamagoose.png", 5000, this);
    mama_icon->setPos(sniper_icon->pos().x() + sniper_icon->pixmap().width() + 10, 50);
    scene_->addItem(mama_icon);
    QLineEdit* mama_price_text = new QLineEdit(this);
    mama_price_text->setReadOnly(true);
    mama_price_text->setAlignment(Qt::AlignCenter);
    mama_price_text->setText(QString("$") + QString::number(5000));
    mama_price_text->move(mama_icon->pos().x() - mama_price_text->width() / 2, mama_icon->pixmap().height());
    mama_price_text->setStyleSheet("QLineEdit {color: black; font: bold; background: rgba(0, 0, 0, 50); width: 100 px}");

    // Set cursor and build ptr to nullptr and turn on mouse tracking
    cursor_ = nullptr;
    build_ = nullptr;
    setMouseTracking(true);

    // Initialize sound effects
    enemy_dies_sfx_.setSource(QUrl::fromLocalFile(":/sfx/antinblop.wav"));
    enemy_dies_sfx_.setVolume(0.3f);
    cruiseship_dies_sfx_.setSource(QUrl::fromLocalFile(":/sfx/aadanblop.wav"));
    dokaani_dies_sfx_.setSource(QUrl::fromLocalFile(":/sfx/dokaani_dies.wav"));
    dokaani_dies_sfx_.setVolume(0.2f);
    honk_sfx_.setSource(QUrl::fromLocalFile(":/sfx/honk.wav"));
    chaching_sfx_.setSource(QUrl::fromLocalFile(":/sfx/cha-ching.wav"));
    chaching_sfx_.setVolume(0.3f);
    game_over_sfx_.setSource(QUrl::fromLocalFile(":/sfx/game_over.wav"));

    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // No vertical nor horizontal scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // connect enemy spawning
    connect(enemy_spawn_timer_, SIGNAL(timeout()), this, SLOT(SpawnEnemy()));
}

Game::~Game() {
    ClearTowers();
}

QGraphicsScene* Game::GetScene() {
    return scene_;
}

QGraphicsPixmapItem* Game::GetCursor() {
    return cursor_;
}

QList<Tower*> Game::GetTowers() {
    return towers_;
}

bool Game::IsGameOver() {
    return game_over_;
}

void Game::mouseMoveEvent(QMouseEvent* event) {
    if (cursor_) {
        cursor_->setPos(event->pos());
    }
}

void Game::SetCursor(QString filename) {
    if (cursor_) {
        scene_->removeItem(cursor_);
        delete cursor_;
    }
    cursor_ = new QGraphicsPixmapItem();
    QPixmap p = QPixmap(filename);
    p = p.scaled(200, 100, Qt::KeepAspectRatio);
    cursor_->setPixmap(p);
    cursor_->setOffset(-p.width() / 2, -p.height() / 2);  // Centering
    scene_->addItem(cursor_);
}

void Game::ResetCursor() {
    if (cursor_) {
        scene_->removeItem(cursor_);
        delete cursor_;
    }
    cursor_ = nullptr;
}

void Game::SetBuild(Tower* newBuild) {
    chaching_sfx_.play();
    build_ = newBuild;
}

void Game::mousePressEvent(QMouseEvent* event) {
    if (!game_over_) {
        if (build_) {
            scene_->addItem(build_);
            towers_ << build_;  // Add the new tower to the list of towers
            build_->setPos(event->pos());
            ResetCursor();
            build_ = nullptr;
        } else {
            // Find the closest tower to the click position
            QPointF clickPos = event->pos();
            double closest_dist = 100;
            closest_tower_ = nullptr;
            for (auto tower : towers_) {
                QLineF ln(tower->pos(), clickPos);
                if (ln.length() < closest_dist) {
                    closest_dist = ln.length();
                    closest_tower_ = tower;
                }
            }
            if (closest_tower_ && !upgrade_button_) {
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
                delete upgrade_button_;
                upgrade_button_ = nullptr;
                delete delete_button_;
                delete_button_ = nullptr;
                delete selected_tower_rect_;
                selected_tower_rect_ = nullptr;
            }
            QGraphicsView::mousePressEvent(event);
        }
    }
}

Tower* Game::GetBuild() {
    return build_;
}

void Game::StartWave() {
    if (!wave_in_progress_) {
        wave_++;
        UpdateWaveText();
        wave_in_progress_ = true;
        no_of_enemies_ = 0;
        int spawn_period = std::max(1000 - wave_*30, 10);
        enemy_spawn_timer_->start(spawn_period); 
    }
}

// The following piece of code is only for the intellectually gifted
void Game::SpawnEnemy() {
    no_of_enemies_ += 1;
    switch (wave_ % 5) {
        case 1:  // student wave
            if (no_of_enemies_ <= 3*wave_) {
                switch (no_of_enemies_ % 3) {
                    case 1 :
                        scene_->addItem(new Fyysikko(paths_, this));
                        break;
                    case 2 :
                        if (wave_ >= 10) {
                            scene_->addItem(new Dokaani(paths_, this));
                        } else {
                            scene_->addItem(new Koneteekkari(paths_, this));
                        }
                        break;
                    case 0 :
                        scene_->addItem(new Kylteri(paths_, this));
                        break;
                }
            } else {  // last enemy of the wave
                enemy_spawn_timer_->stop();
                wave_in_progress_ = false;
            }
            break;
        case 2:  // kone wave
            if (no_of_enemies_ <= wave_) {
                if (wave_ >= 10) {
                    scene_->addItem(new Cruiseship(paths_, this));
                    no_of_enemies_ += 1;
                } else {
                    scene_->addItem(new Koneteekkari(paths_, this));
                }
            } else {  // last enemy of the wave
                enemy_spawn_timer_->stop();
                wave_in_progress_ = false;
            }
            break;
        case 3: 
            if (no_of_enemies_ <= 2*wave_) {
                switch (no_of_enemies_ % 9) {
                    case 1 :
                        scene_->addItem(new Koneteekkari(paths_, this));
                        break;
                    case 2 :
                        if (wave_ >= 10) {
                            scene_->addItem(new Dokaani(paths_, this));
                        } else {
                            scene_->addItem(new Koneteekkari(paths_, this));
                        }
                        break;
                    case 3 :
                        scene_->addItem(new Fyysikko(paths_, this));
                        break;
                    case 4 :
                        if (wave_ >= 10) {
                            scene_->addItem(new Cruiseship(paths_, this));
                        } else {
                            scene_->addItem(new Fyysikko(paths_, this));
                        }
                        break;
                    case 5 :
                        scene_->addItem(new Fyysikko(paths_, this));
                        break;
                    case 6 :
                        scene_->addItem(new Kylteri(paths_, this));
                        break;
                    case 7 :
                        if (wave_ >= 10) {
                            scene_->addItem(new Cruiseship(paths_, this));
                        } else {
                            scene_->addItem(new Kylteri(paths_, this));
                        }
                        break;
                    case 8 :
                        scene_->addItem(new Kylteri(paths_, this));
                        break;
                    case 0 :
                        scene_->addItem(new Dokaani(paths_, this));
                        break;
                }
            } else {  // last enemy of the wave
                enemy_spawn_timer_->stop();
                wave_in_progress_ = false;
            }
            break;
        case 4:  // student couples wave
            if (no_of_enemies_ <= 2*wave_) {
                switch (no_of_enemies_ % 6) {
                    case 1 :
                        scene_->addItem(new Fyysikko(paths_, this));
                        break;
                    case 2 :
                        scene_->addItem(new Fyysikko(paths_, this));
                        break;
                    case 3 :
                        if (wave_ >= 10) {
                            scene_->addItem(new Dokaani(paths_, this));
                        } else {
                            scene_->addItem(new Koneteekkari(paths_, this));
                        }
                        break;
                    case 4 :
                        scene_->addItem(new Koneteekkari(paths_, this));
                        break;
                    case 5 :
                        if (wave_ >= 10) {
                            scene_->addItem(new Cruiseship(paths_, this));
                        } else {
                            scene_->addItem(new Kylteri(paths_, this));
                        }
                        break;
                    case 0 :
                        scene_->addItem(new Kylteri(paths_, this));
                        break;
                }
            } else {  // last enemy of the wave
                enemy_spawn_timer_->stop();
                wave_in_progress_ = false;
            }
            break; 
        case 0:  // student couples wave
            if (no_of_enemies_ <= 2*wave_) {
                switch (no_of_enemies_ %10) {
                    case 1 :
                        scene_->addItem(new Fyysikko(paths_, this));
                        break;
                    case 2 :
                        scene_->addItem(new Kylteri(paths_, this));
                        break;
                    case 5 :
                        scene_->addItem(new Fyysikko(paths_, this));
                        break;
                    case 6 :
                        scene_->addItem(new Fyysikko(paths_, this));
                        break;
                    case 0 :
                        scene_->addItem(new Cruiseship(paths_, this));
                        break;
                    default :
                        scene_->addItem(new Koneteekkari(paths_, this));
                        break;
                }
            } else {  // last enemy of the wave
                enemy_spawn_timer_->stop();
                wave_in_progress_ = false;
            }
            break;
    }
}

void Game::CreatePaths() {
    for (auto path_points : paths_) {
        for (int i = 0; i < path_points.size() - 1; i++) {
            QLineF line(path_points[i], path_points[i+1]);
            QGraphicsLineItem* lineItem = new QGraphicsLineItem(line);

            QPen pen;
            pen.setWidth(50);  // Width of the drawn path/line
            pen.setColor(Qt::darkBlue);  // Set the color of the path
            lineItem->setPen(pen);

            scene_->addItem(lineItem);
        }
    }
}

void Game::ClearTowers() {
    for (auto tower : towers_) {
        closest_tower_ = tower;
        RemoveTower();
    }
    towers_.clear();
}

QProgressBar* Game::GetHealthBar() {
    return health_bar_;
}

int Game::GetMoney() {
    return money_;
}

void Game::UpdateMoneyText() {
    money_text_->setText(QString(" MONEY: $") + QString::number(GetMoney()));
}

void Game::UpdateWaveText() {
    wave_text_->setText(QString(" WAVE: ") + QString::number(wave_));
}

void Game::SetMoney(int new_money) {
    money_ = new_money;
}

QList<QList<QPointF>> Game::GetPaths() {
    return paths_;
}

void Game::UpgradeTower() {
    if (money_ - 50 >= 0) {
        closest_tower_->UpgradeAttackRadius(closest_tower_->GetAttackRadius() + 20);
        money_ -= 50;
        UpdateMoneyText();
    }
}

void Game::RemoveTower() {
    delete delete_button_;
    delete upgrade_button_;
    delete selected_tower_rect_;
    delete_button_ = nullptr;
    upgrade_button_ = nullptr;
    selected_tower_rect_ = nullptr;
    towers_.removeOne(closest_tower_);
    scene_->removeItem(closest_tower_);
    closest_tower_ = nullptr;
}

void Game::PlayEnemyDiesSfx() {
    enemy_dies_sfx_.play();
}

void Game::PlayCruiseshipDiesSfx() {
    cruiseship_dies_sfx_.play();
}

void Game::PlayDokaaniDiesSfx() {
    dokaani_dies_sfx_.play();
}

void Game::PlayHonkSfx() {
    honk_sfx_.play();
}

void Game::GameOver() {
    if (!game_over_) {
        game_over_ = true;
        game_over_sfx_.play();

        // Add a grey rectangle over everything
        QColor alphaBlack = Qt::black;
        alphaBlack.setAlphaF(0.5);
        QBrush grayBrush(alphaBlack);
        QPen blackPen(alphaBlack);
        blackPen.setWidth(1);
        scene_->addRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, blackPen, grayBrush);

        // Game over text
        QLineEdit* game_over_text = new QLineEdit(this);
        game_over_text->setReadOnly(true);
        game_over_text->setAlignment(Qt::AlignCenter);
        game_over_text->setText(QString("GAME OVER"));
        game_over_text->setStyleSheet("QLineEdit {color: white; font: bold; background: rgba(0, 0, 0, 0)}");
        QFont font = game_over_text->font();
        font.setPointSize(50);
        game_over_text->setFont(font);
        game_over_text->setFixedSize(600, 100);
        game_over_text->move(WINDOW_WIDTH / 2 - game_over_text->width() / 2,  WINDOW_HEIGHT / 2 - game_over_text->height() / 2);
        game_over_text->show();

        QLineEdit* stats_text = new QLineEdit(this);
        stats_text->setAlignment(Qt::AlignCenter);
        stats_text->setReadOnly(true);
        stats_text->setStyleSheet("QLineEdit {color: white; font: bold; background: rgba(0, 0, 0, 0)}");
        font = stats_text->font();
        font.setPointSize(20);
        stats_text->setFont(font);
        stats_text->setFixedSize(600, 100);
        stats_text->setText(QString("You made it to wave number ") + QString::number(wave_));
        stats_text->move(WINDOW_WIDTH / 2 - stats_text->width() / 2,  WINDOW_HEIGHT / 2 - stats_text->height() / 2 + 80);
        stats_text->show();

        // Release memory
        delete start_button_;
        delete clear_button_;
        delete upgrade_button_;
        delete delete_button_;
        delete selected_tower_rect_;
        start_button_ = nullptr;
        clear_button_ = nullptr;
        upgrade_button_ = nullptr;
        delete_button_ = nullptr;
        selected_tower_rect_ = nullptr;
    }
}
