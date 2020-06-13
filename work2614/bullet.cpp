#include "bullet.h"
#include <QPainter>
#include <QPropertyAnimation>
#include"monster.h"
#include"gamewindow.h"
#include<QDebug>
#include<QObject>
Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, monster *target,GameWindow *game)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)

    , m_currentPos(startPos)
    , m_target(target)
    , m_game(game)
    , m_damage(damage)
{
}
void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos, m_sprite);
}
void Bullet::move()
{
    // 100毫秒内击中敌人
   int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    animation->start();
}

void Bullet::setCurrentPos(QPoint pos)
{
    m_currentPos = pos;
}

QPoint Bullet::currentPos() const
{
    return m_currentPos;
}
