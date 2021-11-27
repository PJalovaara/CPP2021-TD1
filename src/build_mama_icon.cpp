#include "build_mama_icon.hpp"

#include <QString>

#include "mamagoose.hpp"

BuildMamaIcon::BuildMamaIcon(Game* game, QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    QPixmap p = QPixmap(":/images/MamaGoose.png");
    p = p.scaled(200, 100, Qt::KeepAspectRatio);
    setPixmap(p); // Set size for the goose
    setOffset(-p.width() / 2, -p.height() / 2); // Centering
    game_ = game;
    price_ = 100; // Set price
};

void BuildMamaIcon::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if(!(game_->GetBuild()) && game_->GetMoney() >= price_) {
        // Create a new tower to the build_ pointer
        MamaGoose* newGoose = new MamaGoose(game_->GetScene());
        game_->SetBuild(newGoose);
        game_->SetCursor(QString(":images/MamaGoose.png"));
        // Player buys the tower which takes money
        game_->SetMoney(game_->GetMoney() - price_);
        game_->UpdateMoneyText();
    }
}
