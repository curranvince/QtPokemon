#include "tile.h"

#include <QtWidgets>

QPixmap *Tile::kSpriteImage = nullptr;

Tile::Tile(enum Type nType, Position nPos) : kType(nType), kPos(nPos) {
    switch (nType) {
        case Type::kLand:
            kSpriteOffset = 0;
            break;
        case Type::kWater:
            kSpriteOffset = TILE_WIDTH;
            break;
        case Type::kPokeCenter:
            kSpriteOffset = TILE_WIDTH*2;
            break;
        case Type::kPokeGym:
            kSpriteOffset = TILE_WIDTH*3;
            break;
    }
}

// set Tile position
QRectF Tile::boundingRect() const {
    auto pos = kPos.Convert();
    return QRectF(pos.x_, pos.y_, TILE_WIDTH, TILE_WIDTH);
}

// set Tile shape
QPainterPath Tile::shape() const {
    QPainterPath path;
    auto pos = kPos.Convert();
    path.addRect(pos.x_, pos.y_, TILE_WIDTH, TILE_WIDTH);
    return path;
}

// set Tile visibility traits (color, size)
void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(widget);
    Q_UNUSED(item);

    auto b = painter->brush();

    auto pos = kPos.Convert();

    painter->drawPixmap(pos.x_, pos.y_, *kSpriteImage, kSpriteOffset, 0, TILE_WIDTH, TILE_WIDTH);

    painter->setBrush(b);
}
