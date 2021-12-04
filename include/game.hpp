#ifndef TD_GAME
#define TD_GAME

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

class Game : public QGraphicsView{
    Q_OBJECT
public:
    // member functions
    Game(QList<QList<QPointF>> paths);
    ~Game();

    void SetCursor(QString filename);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    
    QProgressBar* GetHealthBar();
    int GetMoney();
    void SetMoney(int new_money);
    void UpdateMoneyText();
    void UpdateWaveText();
    Tower* GetBuild();
    void SetBuild(Tower* new_build);
    QGraphicsScene* GetScene();
    QGraphicsPixmapItem* GetCursor();
    void ResetCursor();

    QList<QList<QPointF>> GetPaths();
    void CreatePaths();

    void PlayEnemyDiesSfx();
    void PlayCruiseshipDiesSfx();
    

public slots:
    void SpawnFyysikko();
    void CreateEnemies();
    void ClearTowers();
    void UpgradeTower();
    void RemoveTower();
    void StartWave();

private:
    QGraphicsScene* scene_;
    Tower* build_;
    QGraphicsPixmapItem* cursor_;
    QTimer* enemy_spawn_timer_;
    int enemies_spawned_;
    int max_no_of_enemies_;
    QList<QList<QPointF>> paths_;
    QList<Tower*> towers_;
    QProgressBar* health_bar_;
    int money_;
    int wave_;
    int last_wave_;
    QLineEdit* money_text_;
    QLineEdit* wave_text_;
    Tower* closest_tower_;
    QPushButton* upgrade_button_;
    QPushButton* delete_button_;
    QGraphicsRectItem* selected_tower_rect_;
    QSoundEffect enemy_dies_sfx_;
    QSoundEffect cruiseship_dies_sfx_;
};


#endif