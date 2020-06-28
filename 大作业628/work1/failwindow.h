#ifndef FAILWINDOW_H
#define FAILWINDOW_H

#include <QMainWindow>

#include <QWidget>


class failwindow:public QMainWindow
{
public:
    failwindow();
    void paintEvent(QPaintEvent*);
};

#endif // FAILWINDOW_H
