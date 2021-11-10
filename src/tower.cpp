#include "tower.hpp"
#include <QPixmap>
#include <QDebug>
#include <QLabel>
#include <QString>


Tower::Tower(QGraphicsItem* parent){
    // Set the graphics
    QPixmap pix;
    if(!(pix.load((":/images/SniperGoose.png")))){
        qDebug() << "Failed to load the picture";
    }

    setPixmap(pix);

    // Add more points to make it more round
    points_ = {QPointF(1,0), QPointF(2,0), QPointF(3,1), QPointF(3,2), QPoint(2,3), QPoint(1,3), QPoint(0,2), QPoint(0,1)};


    
    for(unsigned int i = 0; i < points_.size(); i++){
        points_[i] *= attack_radius_;
    }
    // Creating the QGraphicsPolygon, where This is the parent and now its added to the scene
    attack_area_ = new QGraphicsPolygonItem(points_, this);

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


// Does not center the polygon
void Tower::UpdateAttackRadius(unsigned int new_radius){
    points_ = {QPointF(1,0), QPointF(2,0), QPointF(3,1), QPointF(3,2), QPoint(2,3), QPoint(1,3), QPoint(0,2), QPoint(0,1)};
    for(unsigned int i = 0; i < points_.size(); i++){
        points_[i] *= new_radius / attack_radius_;
    }
    if(attack_area_) delete attack_area_;
    attack_area_ = new QGraphicsPolygonItem(points_, this);
    attack_radius_ = new_radius;
}