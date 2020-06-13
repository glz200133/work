#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QMouseEvent>
#include<QPushButton>
#include <QWidget>
#include "monster.h"
#include "towerparent.h"


//游戏的初始界面，选择关卡，还未进行美工处理。
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
void paintEvent(QPaintEvent*);//进入主界面就会调用
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
