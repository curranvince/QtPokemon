#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>

#include "pokemon.h"

/* Player sprites from: https://reliccastle.com/resources/531/ */
/* Sprite animations adapted from: https://evileg.com/en/post/92/ */
class Player : public QGraphicsObject
{
    Q_OBJECT

private:
    const QPixmap *spriteImage_;

    int currentFrame_;

    Direction currentDirection_;
    bool moving_;

    Pokemon* activePokemon_;
    Pokemon* party_[6];
    std::vector<Pokemon*> pokedex_;

    Position pos_;
    int pokeballs_;

    // necessary Qt bounding and drawing methods
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

public:
    Player(Pokemon* starter);

    Position GetPosition() { return pos_; }

    void Move(Direction direction);

};

#endif // PLAYER_H
