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

#include "tower.hpp"

class Game : public QGraphicsView{
    Q_OBJECT
public:
    // member functions
    Game();
    void SetCursor(QString filename);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    
    QProgressBar* GetHealthBar();
    int GetMoney();
    void SetMoney(int new_money);
    void SetMoneyText(const QString& text);
    Tower* GetBuild();
    void SetBuild(Tower* new_build);
    QGraphicsScene* GetScene();
    QGraphicsPixmapItem* GetCursor();
    void ResetCursor();

    QList<QPointF> GetPathPoints();
    void CreatePath();
    

public slots:
    void SpawnFyysikko();
    void CreateEnemies();
    void ClearTowers();

private:
    QGraphicsScene* scene_;
    Tower* build_;
    QGraphicsPixmapItem* cursor_;
    QTimer* enemy_spawn_timer_;
    int enemies_spawned_;
    int max_no_of_enemies_;
    QList<QPointF> path_points_;
    QList<Tower*> towers_;
    QProgressBar* health_bar_;
    int money_;
    QLineEdit* money_text_;
};


#endif