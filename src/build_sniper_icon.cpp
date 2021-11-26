#include "build_sniper_icon.hpp"

#include <QString>

#include "snipergoose.hpp"

BuildSniperIcon::BuildSniperIcon(Game* game, QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    QPixmap p = QPixmap(":/images/SniperGoose.png"); // TODO: Change to an icon later
    p = p.scaled(200, 100, Qt::KeepAspectRatio);
    setPixmap(p); // Set size for the goose
    setOffset(-p.width() / 2, -p.height() / 2); // Centering
    game_ = game;
    price_ = 200; // Set prize
};

void BuildSniperIcon::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if(!(game_->GetBuild()) && game_->GetMoney() >= price_) {
        // Set the new tower to the build_ pointer
        SniperGoose* newGoose = new SniperGoose(game_->GetScene());
        game_->SetBuild(newGoose);
        game_->SetCursor(QString(":images/SniperGoose.png"));

        // Player buys the tower which takes money
        game_->SetMoney(game_->GetMoney() - price_);
        game_->SetMoneyText(QString(" MONEY: ") + QString::number(game_->GetMoney()));
    }
}