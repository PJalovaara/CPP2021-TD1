#include "editor.hpp"

#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsLineItem>
#include <QPixmap>
#include <QLineF>
#include <QBrush>
#include <QPen>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

Editor::Editor() {
    // create and set scene
    scene_ = new QGraphicsScene(this);
    setScene(scene_); // Visualize this scene
    scene_->setSceneRect(0,0,WINDOW_WIDTH, WINDOW_HEIGHT);

    // create toggle button for path creation
    QPushButton* toggleButton = new QPushButton(QString("TOGGLE PATH CREATION"), this);
    toggleButton->move(WINDOW_WIDTH / 2 - toggleButton->width() / 2, 10);
    connect(toggleButton, SIGNAL(clicked()), this, SLOT(TogglePathMode()));

    // create toggle button for path creation
    QPushButton* saveButton = new QPushButton(QString("SAVE TO FILE"), this);
    saveButton->move(WINDOW_WIDTH / 2 - saveButton->width() / 2, 40);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(SavePathToFile()));


    // Add a grey background for better visibility
    QBrush grayBrush(Qt::gray);
    QPen blackPen(Qt::black);
    blackPen.setWidth(1);
    scene_->addRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, blackPen, grayBrush);

    setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    // No vertical nor horizontal scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

QGraphicsScene* Editor::GetScene() {
    return scene_;
};
    
QGraphicsPixmapItem* Editor::GetCursor() {
    return cursor_;
};

void Editor::TogglePathMode() {
    in_path_mode_ = !in_path_mode_;
    if(in_path_mode_) {
        ++path_index_;
        QList<QPointF> empty_list;
        paths_ << empty_list;
    }
};

void Editor::mouseMoveEvent(QMouseEvent* event) {
    /* if(cursor_) {
        cursor_->setPos(event->pos());
    } */
};

void Editor::SetCursor(QString filename) {
    /* if(cursor_) {
        scene_->removeItem(cursor_);
        delete cursor_;
    }
    cursor_ = new QGraphicsPixmapItem();
    QPixmap p = QPixmap(filename);
    p = p.scaled(200, 100, Qt::KeepAspectRatio);
    cursor_->setPixmap(p);
    cursor_->setOffset(-p.width() / 2, -p.height() / 2); // Centering
    scene_->addItem(cursor_); */
};

void Editor::ResetCursor() {
    /* if(cursor_) {
        scene_->removeItem(cursor_);
        delete cursor_;
    }
    cursor_ = nullptr; */
};

void Editor::mousePressEvent(QMouseEvent* event) {
    QGraphicsView::mousePressEvent(event);
    if(in_path_mode_){
        paths_[path_index_] << event->pos();
        CreatePath();
    }
};

void Editor::CreatePath() {
    QList<QPointF> path_points = paths_[path_index_];
    for(int i = 0; i < path_points.size() - 1; i++){
        QLineF line(path_points[i], path_points[i+1]);
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(line);

        QPen pen;
        pen.setWidth(50); // Width of the drawn path/line
        pen.setColor(QColor(path_index_ * 132 % 255, path_index_ * 549 % 255, path_index_ * 941 % 255)); // "colors determined by path_index_"
        lineItem->setPen(pen);

        scene_->addItem(lineItem);
    }
};

void Editor::SavePathToFile() {

};