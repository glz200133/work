#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QPainter>
#include <QMouseEvent>
#include <Qtimer>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include<QLabel>
#include<QPixmap>
#include<QPaintEvent>
#include"towerparent.h"
#include"monster.h"
#include"towerspot.h"
#include"selectbutton.h"

class GameWindow:public QMainWindow
{
protected:
    const int LevelNumber;
private:
    QVector<Towerspot*> TowerPitVec;  //防御塔坑数组
    Selectbutton* SelButton = new Selectbutton(":/selectbutton.png"); //选择框类

    QVector<towerparent*> TowerparVec; //重要防御塔父类数组

    QVector<monster*> MonsterVec;           //怪物数组

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);


    void DrawMapArr(QPainter&);             //用于画出地图函数
    void DrawSelectionBox(QPainter&);       //用于画出选择框
    void DrawDefenseTower(QPainter&);       //画出防御塔
    void DrawMonster(QPainter&);            //画出怪物
    void DrawRangeAndUpgrade(QPainter&);    //画出防御塔攻击范围和升级按钮
    //void DrawExplosion(QPainter&);          //画出爆炸效果

    int DisplayRangeX, DisplayRangeY;       //用于记录显示范围的防御塔的坐标
    bool DisplayRange = false;              //用于显示防御塔攻击范围



    int money = 1000;   //记录金钱

    QLabel *moneylable = new QLabel(this);  //显示金钱标签控件

    inline bool DeductionMoney(int);         //判断金钱是否足够并刷新标签

    int life = 10;      //生命数量

    int counter = 0;    //用于产生怪物的计数器

    const int RewardMoney = 28; //每次击败怪物获得的金钱数量

    CoorStr *homecoor = new CoorStr(0, 0);  //记录家的坐标，从地图中自动获取

    void IrodMonsProgDefa(CoorStr**, CoorStr**, CoorStr*, int*, QLabel*); //预设两条路产生怪物方案函数

    bool DisplayAllRange = false;  //标识是否显示所有防御塔的攻击范围

public:
    GameWindow(int);
    ~GameWindow();
};

#endif // GAMEWINDOW_H
