#include "battlesprite.h"

#include <QEventLoop>

QPixmap *BattleSprite::kSpriteImage = nullptr;
const int BattleSprite::kSpriteSize = 100;

BattleSprite::BattleSprite(int id, bool player) : kPlayer(player), id_(id)
{
    timer_ = new QTimer();
    ConvertID();
}

void BattleSprite::ConvertID() {
    offsetX_ = ((id_ - 1) % 16) * kSpriteSize; // 16 cols in the spritesheet
    offsetY_ = std::ceil(id_ / 16) * kSpriteSize;
}

void BattleSprite::ChangeImage(int id) {
    id_ = id;
    ConvertID();
    update();
}

QRectF BattleSprite::boundingRect() const {
    if (kPlayer) {
        return QRectF(140, 180, kSpriteSize, kSpriteSize);
    } else {
        return QRectF(420, 15, kSpriteSize, kSpriteSize);
    }
}

void BattleSprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    if (kPlayer) {
        painter->drawPixmap(140, 180, *kSpriteImage, offsetX_, offsetY_, kSpriteSize, kSpriteSize);
    } else {
        painter->drawPixmap(420, 15, *kSpriteImage, offsetX_, offsetY_, kSpriteSize, kSpriteSize);
    }

    Q_UNUSED(widget);
    Q_UNUSED(item);
}

void BattleSprite::DoAttackAnimation() {
    QEventLoop blocker;
    connect(timer_, SIGNAL(timeout()), &blocker, SLOT(quit()));
    int moveAmount = kPlayer ? -30 : 30;
    moveBy(-moveAmount, moveAmount);
    timer_->start(100);
    blocker.exec();
    moveBy(moveAmount, -moveAmount);
}
