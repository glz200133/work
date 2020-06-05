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

    setWindowTitle("开始界面");
    //关卡数量
    const int NumLe = 3;

    //按钮数组
    QPushButton* btnarr[NumLe] = {ui->pushButton, ui->pushButton_2, ui->pushButton_3};

    for (int i = 0; i < NumLe; i++)
        connect(btnarr[i], &QPushButton::clicked,this, [=]()
        {
             this->close();
            QMainWindow *gamewindow = new QMainWindow;
            gamewindow->show();     //显示窗口
        });
    //button*btn=new button(":/1.jpg");
    //this->setFixedSize(1080,1440);
   //btn->setParent(this);

    //btn->move(800,100);

    //connect(btn,&button::clicked,this,[=](){
       //

   // });
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.drawPixmap(0,0,QPixmap (":/1.jpg"));

}
