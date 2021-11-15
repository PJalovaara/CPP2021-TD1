#include "build_tower_icon.hpp"
#include "mamagoose.hpp"
#include <QString>

BuildTowerIcon::BuildTowerIcon(Game* game, QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    QPixmap p = QPixmap(":/images/MamaGoose.png"); // TODO: Change to an icon later
    p = p.scaled(200, 100, Qt::KeepAspectRatio);
    setPixmap(p); // Set size for the goose
    game_ = game;
};

void BuildTowerIcon::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if(!(game_->GetBuild())) {
        game_->SetBuild(new MamaGoose(game_->GetScene()));
        game_->SetCursor(QString(":images/MamaGoose.png"));
    }
}
