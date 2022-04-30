#include "player.h"

Player::Player(Pokemon* starter)
{
    activePokemon_ = starter;
    party_[0] = starter;
    switch (starter->)
}

// set Tile position
QRectF Player::boundingRect() const {
    auto pos = pos_.Convert();
    return QRectF(pos.x_, pos.y_, kWidth, kWidth);
}

// set Tile shape
QPainterPath Player::shape() const {
    QPainterPath path;
    auto pos = pos_.Convert();
    path.addRect(pos.x_, pos.y_, kWidth, kWidth);
    return path;
}

// set Tile visibility traits (color, size)
void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(item);

    auto b = painter->brush();
    // tiles are red or black
    switch (kType) {
        case (Type::kLand):
            painter->setBrush(QBrush(QColor(0,255,0))); // green
            break;
        case (Type::kWater):
            painter->setBrush(QBrush(QColor(0,0,255))); // blue
            break;
        case (Type::kPokeCenter):
            painter->setBrush(QBrush(QColor(255,0,0)));  // red
            break;
        case (Type::kPokeGym):
            painter->setBrush(QBrush(QColor(255,102,0))); // orange
            break;
    }

    auto pos = ConvertPosition();

    painter->drawRect(pos.x_, pos.y_, kWidth, kWidth);
    painter->setBrush(b);
}
