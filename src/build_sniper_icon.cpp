#include "build_sniper_icon.hpp"

#include <QString>

#include "snipergoose.hpp"

BuildSniperIcon::BuildSniperIcon(Game* game, QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    QPixmap p = QPixmap(":/images/SniperGoose.png"); // TODO: Change to an icon later
    p = p.scaled(200, 100, Qt::KeepAspectRatio);
    setPixmap(p); // Set size for the goose
    game_ = game;
};

void BuildSniperIcon::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if(!(game_->GetBuild())) {
        SniperGoose* newGoose = new SniperGoose(game_->GetScene());
        game_->SetBuild(newGoose);
        game_->SetCursor(QString(":images/SniperGoose.png"));
    }
}