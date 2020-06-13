#ifndef BULLET_H
#define BULLET_H
#include <QPoint>
#include<QPainter>
#include<QWidget>
#include"monster.h"
#include <QSize>
#include <QPixmap>
#include <QObject>
#include"gamewindow.h"

class Bullet:public QWidget
{
public:

    Bullet(QPoint startPos, QPoint targetPoint, int damage, monster*target,
           GameWindow *game);

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;
    void hitTarget();
protected:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    const QPixmap	m_sprite;
    QPoint			m_currentPos;
    monster *			m_target;
    GameWindow *	m_game;
    int				m_damage;
};


#endif // BULLET_H
