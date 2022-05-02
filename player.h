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

    std::vector<Pokemon*>  party_;
    std::vector<Pokemon*> pokedex_;

    Position pos_;

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

public:
    int pokeballs_;
    int badges_;

    Player(Pokemon* starter);

    Position GetPosition() { return pos_; }
    std::vector<Pokemon*> GetParty() { return party_; }
    Pokemon* GetActive() { return activePokemon_; }

    bool NextPokemon();

    void AddPokemon(Pokemon* pokemon);
    void SetActive(int index);
    void BeatGym() { badges_++; }

    void Move(Direction dir);
    void Move(Position pos);

    void HealAll();

};

#endif // PLAYER_H
