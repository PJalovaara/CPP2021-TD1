#ifndef INCLUDE_EDITOR_HPP_
#define INCLUDE_EDITOR_HPP_

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsItem>
#include <QString>
#include <QList>
#include <QPointF>

#include "editor.hpp"

/**
 * @brief A level editor that can be used to create custom levels.
 *
 * Levels are saved in a serialized binary format which can be read by the Menu class.
 * 
 */
class Editor : public QGraphicsView {
    Q_OBJECT

 public:
    // member functions
    explicit Editor(QWidget* parent = 0);
    ~Editor();
    
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


#endif  // INCLUDE_EDITOR_HPP_
