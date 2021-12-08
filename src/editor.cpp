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
#include <QFileDialog>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 700

Editor::Editor(QWidget* parent) : QGraphicsView(parent) {
    // create and set scene
    scene_ = new QGraphicsScene(this);
    setScene(scene_);  // Visualize this scene
    scene_->setSceneRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

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
    setMouseTracking(true);
}

QGraphicsScene* Editor::GetScene() {
    return scene_;
}

QGraphicsPixmapItem* Editor::GetCursor() {
    return cursor_;
}

void Editor::TogglePathMode() {
    in_path_mode_ = !in_path_mode_;
    if (in_path_mode_) {
        SetCursor(":images/editorcursor.png");
        ++path_index_;
        QList<QPointF> empty_list;
        paths_ << empty_list;
    } else {
        ResetCursor();
    }
}

void Editor::mouseMoveEvent(QMouseEvent* event) {
    if (cursor_) {
        cursor_->setPos(event->pos());
    }
}

void Editor::SetCursor(QString filename) {
    if (cursor_) {
        scene_->removeItem(cursor_);
        delete cursor_;
    }
    cursor_ = new QGraphicsPixmapItem();
    QPixmap p = QPixmap(filename);
    p = p.scaled(50, 50, Qt::KeepAspectRatio);
    cursor_->setPixmap(p);
    cursor_->setOffset(-p.width() / 2, -p.height() / 2);  // Centering
    scene_->addItem(cursor_);
}

void Editor::ResetCursor() {
    if (cursor_) {
        scene_->removeItem(cursor_);
        delete cursor_;
    }
    cursor_ = nullptr;
}

void Editor::mousePressEvent(QMouseEvent* event) {
    QGraphicsView::mousePressEvent(event);
    if (in_path_mode_) {
        paths_[path_index_] << event->pos();
        CreatePath();
    }
}

void Editor::CreatePath() {
    QList<QPointF> path_points = paths_[path_index_];
    for (int i = 0; i < path_points.size() - 1; i++) {
        QLineF line(path_points[i], path_points[i+1]);
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(line);

        QPen pen;
        pen.setWidth(50);  // Width of the drawn path/line
        int color_seed = path_index_+1;  // "colors determined by path_index_+1"
        pen.setColor(QColor(color_seed * 132 % 255, color_seed * 549 % 255, color_seed * 941 % 255));
        lineItem->setPen(pen);

        scene_->addItem(lineItem);
    }
}

void Editor::SavePathToFile() {
    QFile file("custom_level.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);  // we will serialize the data into the file
    qint32 n_paths;
    n_paths = paths_.size();
    out << n_paths;
    for (int i = 0; i < n_paths; i++) {
        qint32 n_points;
        n_points = paths_[i].size();
        out << n_points;
        for (int j = 0; j < n_points; j++) {
            qint32 point_x;
            qint32 point_y;
            point_x = paths_[i][j].x();
            point_y = paths_[i][j].y();
            out << point_x << point_y;
        }
    }
    file.close();
}

void Editor::closeEvent(QCloseEvent *event) {
    scene_->clear();
    QWidget::closeEvent(event);
}
