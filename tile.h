#ifndef TILE_H
#define TILE_H

#include <QGraphicsObject>

#include "utility.h"

enum class Type {
    kLand,
    kWater,
    kPokeGym,
    kPokeCenter
};

class Tile : public QGraphicsObject
{
    Q_OBJECT

private:
    const enum Type kType;

    const Position kPos;

public:
    Tile(enum Type nType, Position nPos) : kType(nType), kPos(nPos) {}

    enum Type GetType() { return kType; }

    // necessary Qt bounding and drawing methods
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

};

#endif // TILE_H
