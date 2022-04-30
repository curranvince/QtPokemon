#include "player.h"

#include <iostream>

#include <QDebug>

Player::Player(Pokemon* starter) :
    QGraphicsObject(), pos_(Position(0,0))
{
    setFlag(ItemSendsGeometryChanges);

    activePokemon_ = starter;
    party_[0] = starter;
    switch (starter->GetID()) {
        case 1:
            pos_ = Position(6, 12);
            break;
        case 4:
            pos_ = Position(7, 12);
            break;
        case 7:
            pos_ = Position(8, 12);
            break;
        case 25:
            pos_ = Position(9, 12);
            break;
        default:
            std::cerr << "Got bad ID for starting pokemon, exiting";
            exit(-1);
    }
    currentFrame_ = 0;
    spriteImage_ = new QPixmap(":/img/player_35.png");

    currentDirection_ = Direction::kSouth;
    moving_ = false;

}

// set Tile position
QRectF Player::boundingRect() const {
    auto pos = pos_.Convert();
    return QRectF(pos.x_, pos.y_, TILE_WIDTH, TILE_WIDTH);
}

// set Tile visibility traits (color, size)
void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    auto pos = pos_.Convert();

    painter->drawPixmap(pos.x_, pos.y_, *spriteImage_, currentFrame_, 0, TILE_WIDTH, TILE_WIDTH);

    Q_UNUSED(widget);
    Q_UNUSED(item);
}

void Player::Move(Direction direction) {
    switch (direction) {
        case Direction::kSouth:
            pos_.y_ += 1;
            this->moveBy(0, -0.01);
            break;
        case Direction::kNorth:
            pos_.y_ -= 1;
            this->moveBy(0, 0.01);
            break;
        case Direction::kEast:
            pos_.x_ += 1;
            this->moveBy(0.01, 0);
            break;
        case Direction::kWest:
            pos_.x_ -= 1;
            this->moveBy(-0.01, 0);
            break;
    }
}
