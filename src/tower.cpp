#include "tower.hpp"
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QDebug>

Tower::Tower(QGraphicsItem* parent){
    // Set the graphics
    QPixmap pix;
    if(!(pix.load(("tower-defense-1/resources/images/tower.png")))){
        qDebug() << "Failed to load the picture";
    }

    setPixmap(pix);//(":/images/tower.png")); // THIS DOESNT WORK

    // Creating (float) points vector for the polygon
    QVector<QPointF> points;
    points << QPoint(1,0) << QPoint(2,0) << QPoint(3,1) << QPoint(3,2) // can add item using the << operator
           << QPoint(2,3) << QPoint(1,3) << QPoint(0,2) << QPoint(0,1);

    // Scaling the polygon to be larger ()
    for(size_t i = 0, n = points.size(); i < n; i++){
        points[i] *= attack_radius_;
    }

    // Creating the QGraphicsPolygon
    attack_area_ = new QGraphicsPolygonItem(QPolygonF(points), this); // where this is the parent and now its added to the scene

    // CENTERING THE POLYGON (original center (1.5, 1.5))
    QPointF poly_center(1.5, 1.5);
    poly_center *= attack_radius_; // The scale factor for the 

    poly_center = mapToScene(poly_center);

    QPointF tower_center(x() + 100, y() + 100); // Randomly chosen intergers in this case :D
    QLineF ln(poly_center, tower_center);
    attack_area_->setPos(x() + ln.dx(), y() + ln.dy()); // Moving the attack area along the line from poly_center to tower_center
}

unsigned int Tower::GetAttackRadius(){
    return attack_radius_;
}

// FIX THIS TO AFFECT THE POLYGON TOO
void Tower::UpdateAttackRadius(unsigned int new_radius){
    attack_radius_ = new_radius;
}