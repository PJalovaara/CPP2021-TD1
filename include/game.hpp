#ifndef INCLUDE_GAME_HPP_
#define INCLUDE_GAME_HPP_

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QString>
#include <QList>
#include <QPointF>
#include <QTimer>
#include <QLineEdit>
#include <QProgressBar>
#include <QPushButton>
#include <QSoundEffect>

#include "tower.hpp"

/**
 * @brief 
 * 
 */
class Game : public QGraphicsView {
    Q_OBJECT
 public:
    // member functions
    explicit Game(QList<QList<QPointF>> paths, QWidget* parent = 0);
    ~Game();

    void SetCursor(QString filename);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

    bool IsGameOver();
    QProgressBar* GetHealthBar();
    int GetMoney();
    void SetMoney(int new_money);
    void SetPriceText(int icon_x, int icon_height, int price);
    void UpdateMoneyText();
    void UpdateWaveText();
    Tower* GetBuild();
    QList<Tower*> GetTowers();
    void SetBuild(Tower* new_build);
    QGraphicsScene* GetScene();
    QGraphicsPixmapItem* GetCursor();
    void ResetCursor();

    QList<QList<QPointF>> GetPaths();
    void CreatePaths();
    void closeEvent(QCloseEvent *event);

    void PlayEnemyDiesSfx();
    void PlayDokaaniDiesSfx();
    void PlayCruiseshipDiesSfx();
    void PlayHonkSfx();
    void GameOver();

 public slots:
    void SpawnEnemy();
    void ClearTowers();
    void UpgradeTower();
    void RemoveTower();
    void StartWave();

 private:
    QGraphicsScene* scene_;
    Tower* build_;
    QGraphicsPixmapItem* cursor_;
    QTimer* enemy_spawn_timer_;
    int no_of_enemies_;
    QList<QList<QPointF>> paths_;
    QList<Tower*> towers_;
    QProgressBar* health_bar_;
    int money_;
    int wave_;
    QLineEdit* money_text_;
    QLineEdit* wave_text_;
    Tower* closest_tower_;
    QPushButton* upgrade_button_;
    QPushButton* delete_button_;
    QPushButton* start_button_;
    QPushButton* clear_button_;
    QGraphicsRectItem* selected_tower_rect_;
    bool game_over_;
    bool wave_in_progress_;

    QSoundEffect enemy_dies_sfx_;
    QSoundEffect cruiseship_dies_sfx_;
    QSoundEffect dokaani_dies_sfx_;
    QSoundEffect honk_sfx_;
    QSoundEffect chaching_sfx_;
    QSoundEffect game_over_sfx_;
};


#endif  // INCLUDE_GAME_HPP_
