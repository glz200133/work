#include "failwindow.h"
#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QDebug>
failwindow::failwindow()
{
setFixedSize(1040, 640);
}
void failwindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.drawPixmap(220,0,QPixmap (":/fail2.png"));

}
