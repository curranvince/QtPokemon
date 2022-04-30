#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsObject>

#include "pokemon.h"

/* Player sprites from: https://reliccastle.com/resources/531/ */

class Player : public QGraphicsObject
{
    Q_OBJECT

private:
    Pokemon* activePokemon_;
    Pokemon* party_[6];
    std::vector<Pokemon*> pokedex_;

    Position pos_;
    int pokeballs_;

public:
    Player(Pokemon* starter);

    // necessary Qt bounding and drawing methods
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
};

#endif // PLAYER_H
