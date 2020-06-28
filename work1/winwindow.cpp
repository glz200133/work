#include "winwindow.h"
#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QDebug>
winwindow::winwindow()
{
setFixedSize(1040, 640);
}
void winwindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.drawPixmap(50,0,QPixmap (":/victory1.png"));

}
