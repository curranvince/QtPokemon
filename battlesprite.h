#ifndef BATTLESPRITE_H
#define BATTLESPRITE_H

#include <QObject>
#include <QGraphicsObject>
#include <QPixmap>
#include <QObject>
#include <QGraphicsObject>
#include <QPainter>
#include <QTimer>
#include <QPixmap>
#include <QPropertyAnimation>

class BattleSprite : public QGraphicsObject
{
    Q_OBJECT
private:
    static const int kSpriteSize;
    static QPixmap* kSpriteImage;

    const bool kPlayer;

    QTimer* timer_;

    int id_;

    int offsetX_;
    int offsetY_;

    void ConvertID();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

public:
    BattleSprite(int id, bool player);

    void DoAttackAnimation();
    void ChangeImage(int id);

    static void InitializePixmap() { kSpriteImage = new QPixmap(":/img/pokesprites100.png"); }

};

#endif // BATTLESPRITE_H
