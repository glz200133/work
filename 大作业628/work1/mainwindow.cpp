#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include<QPainter>
#include<QPixmap>
#include<QPaintEvent>
#include<QPushButton>
#include<QDebug>
#include"button.h"
#include"gamewindow.h"

//开始界面
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
setFixedSize(1080, 608);
    setWindowTitle("开始界面");
    //关卡数量
    const int Num = 3;

    //按钮数组
    QPushButton* btn[Num] = {ui->pushButton, ui->pushButton_2, ui->pushButton_3};

    for (int i = 0; i < Num; i++)
        connect(btn[i], &QPushButton::clicked,this, [=]()
        {
             this->close();

            GameWindow *gamewindow = new GameWindow(i);

            gamewindow->show();     //显示窗口
        });

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.drawPixmap(0,0,QPixmap (":/anime5.jpg"));

}
