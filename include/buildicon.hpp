#ifndef INCLUDE_BUILDICON_HPP_
#define INCLUDE_BUILDICON_HPP_

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QString>

#include "game.hpp"
#include "tower.hpp"

/**
 * @brief 
 * 
 * @tparam T 
 */
template <typename T>
class BuildIcon: public QGraphicsPixmapItem {
 public:
    BuildIcon(QString imagepath, int price, Game* game, QGraphicsItem* parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
 private:
    Game* game_;
    QString imagepath_;
    int price_;
};

// Template classes' implementation and definition cannot be separated into .hpp and .cpp files.
// This is solved using inline definitions for the class methods in the header.
/**
 * @brief Construct a new Build Icon< T>:: Build Icon object
 * 
 * @tparam T 
 * @param imagepath 
 * @param price 
 * @param game 
 * @param parent 
 */
template <typename T>
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
 * @brief 
 * 
 * @tparam T 
 * @param event 
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
