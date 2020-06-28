#ifndef WINWINDOW_H
#define WINWINDOW_H

#include <QMainWindow>
#include <QWidget>

class winwindow:public QMainWindow
{
public:
    winwindow();
    void paintEvent(QPaintEvent*);
};

#endif // WINWINDOW_H
