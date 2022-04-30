#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>

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
    static QPixmap *kSpriteImage;

    int kSpriteOffset;

    const enum Type kType;

    const Position kPos;

public:
    Tile(enum Type nType, Position nPos);

    /* must init sprite image late or else run time errors occur
     * due to initialzing a 'complex' object before the view is set up
     * https://www.qtcentre.org/threads/34461-Runtime-error-when-initializing-static-const-member-QPixmap */
    static void InitializePixmap() { kSpriteImage = new QPixmap(":/img/tiles.png"); }

    enum Type GetType() { return kType; }

    // necessary Qt bounding and drawing methods
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

};

#endif // TILE_H
