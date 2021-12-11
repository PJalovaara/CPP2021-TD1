#ifndef INCLUDE_BUILDICON_HPP_
#define INCLUDE_BUILDICON_HPP_

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QString>

#include "game.hpp"
#include "tower.hpp"

/**
 * @brief A template class for building Tower objects in a Game
 * 
 * Template classes' implementation and definition cannot simply be separated into header and source files.
 * This is solved using inline definitions for the class methods in this header.
 * 
 * @tparam T is a Tower subclass for which we want to create the BuildIcon
 */
template <class T>
class BuildIcon: public QGraphicsPixmapItem {
 public:
    BuildIcon(QString imagepath, int price, Game* game, QGraphicsItem* parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
 private:
    Game* game_;
    QString imagepath_;
    int price_;
};

/**
 * @brief Construct a new BuildIcon object
 * 
 * @tparam T is a Tower subclass for which we want to create the BuildIcon
 * @param imagepath a QString file path to the wanted image
 * @param price the price that will be associated with the Tower
 * @param game the Game where this BuildIcon is used
 * @param parent optional QGraphicsItem parent
 */
template <class T>
inline BuildIcon<T>::BuildIcon(QString imagepath, int price, Game* game, QGraphicsItem* parent) : QGraphicsPixmapItem(parent) {
    imagepath_ = imagepath;
    QPixmap p = QPixmap(imagepath_);
    p = p.scaled(100, 100, Qt::KeepAspectRatio);
    setPixmap(p);  // Set size for the goose
    setOffset(-p.width() / 2, -p.height() / 2);  // Centering
    game_ = game;
    price_ = price;  // Set price
}

/**
 * @brief Sets the cursor in Game to the Tower image and sets the Game to Build mode
 * 
 * @tparam T is a Tower subclass for which we want to create the BuildIcon
 * @param event a QGraphicsSceneMouseEvent that is passed as a parameter for GUI events
 */
template <class T>
inline void BuildIcon<T>::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (!(game_->GetBuild()) && game_->GetMoney() >= price_ && !(game_->IsGameOver())) {
        // Create a new tower to the build_ pointer
        T* newGoose = new T(game_->GetScene());
        game_->SetBuild(newGoose);
        game_->SetCursor(QString(imagepath_));
        // Player buys the tower which takes money
        game_->SetMoney(game_->GetMoney() - price_);
        game_->UpdateMoneyText();
    }
}

#endif  // INCLUDE_BUILDICON_HPP_
