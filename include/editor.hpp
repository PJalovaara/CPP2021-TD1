#ifndef TD_EDITOR
#define TD_EDITOR

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QString>
#include <QList>
#include <QPointF>

#include "editor.hpp"

class Editor : public QGraphicsView {
    Q_OBJECT
public:
    // member functions
    Editor(QWidget* parent = 0);
    void SetCursor(QString filename);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    
    void closeEvent(QCloseEvent *event);
    QGraphicsScene* GetScene();
    QGraphicsPixmapItem* GetCursor();
    void ResetCursor();
    void CreatePath();

public slots:
    void SavePathToFile();
    void TogglePathMode();

private:
    QGraphicsScene* scene_;
    QGraphicsPixmapItem* cursor_ = nullptr;
    QList<QList<QPointF>> paths_;
    int path_index_ = -1;
    bool in_path_mode_ = false;
};


#endif