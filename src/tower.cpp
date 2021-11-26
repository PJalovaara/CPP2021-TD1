#include "tower.hpp"

#include <QPixmap>
#include <QLabel>
#include <QString>
#include <QTimer>
#include <QList>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

#include <QDebug>

#include "bullet.hpp"
#include "enemy.hpp"

Tower::Tower(QGraphicsScene* scene, QGraphicsItem* parent) : QObject(), QGraphicsPixmapItem(parent) {
    scene_ = scene;
}

unsigned int Tower::GetAttackRadius(){
    return attack_radius_;
}

void Tower::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    // QPushButton* deleteButton = new QPushButton(QString("DELETE"));
    // scene_->addItem(deleteButton);
    QGraphicsRectItem* redRect = new QGraphicsRectItem(x() - tower_width_ / 2, y() - tower_height_ / 2, tower_width_, tower_height_);
    QPen redPen(Qt::red);
    redPen.setWidth(3);
    redRect->setPen(redPen);
    scene_->addItem(redRect);

};

void Tower::UpdateAttackRadius(unsigned int new_radius){
    // Points for the "unit" polygon around the tower
    points_ = { QPointF(2.500000, 1.500000), QPointF(2.445817, 1.824699), QPointF(2.289141, 2.114213), QPointF(2.046948, 2.337166),
                QPointF(1.745485, 2.469400), QPointF(1.417421, 2.496584), QPointF(1.098305, 2.415773), QPointF(0.822718, 2.235724),
                QPointF(0.620526, 1.975947), QPointF(0.513639, 1.664595), QPointF(0.513639, 1.335405), QPointF(0.620526, 1.024053),
                QPointF(0.822718, 0.764276), QPointF(1.098305, 0.584227), QPointF(1.417421, 0.503416), QPointF(1.745485, 0.530600),
                QPointF(2.046948, 0.662834), QPointF(2.289141, 0.885787), QPointF(2.445817, 1.175301) 
    };
    for(unsigned int i = 0; i < points_.size(); i++){
        points_[i] *= new_radius;
    }
    if(attack_area_) {
        delete attack_area_; // Delete the old polygon
    }
    attack_area_ = new QGraphicsPolygonItem(points_, this);
    
    // Centering the polygon around the tower
    QPointF poly_center(1.5, 1.5);
    poly_center *= new_radius; // The scale factor for the polygon
    poly_center = mapToScene(poly_center);
    QLineF ln(poly_center, tower_center_);
    attack_area_->setPos(x() + ln.dx(), y() + ln.dy()); // Moving the attack area along the line from poly_center to tower_center

    attack_radius_ = new_radius; // Update the radius
}


double Tower::DistanceTo(QGraphicsItem* item) {
    QLineF ln(pos(), item->pos());
    return ln.length();
};

