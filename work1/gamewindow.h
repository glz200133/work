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

#include<QVector>
#include<QMediaPlayer>
#include"towerparent.h"
#include"monster.h"
#include"towerspot.h"
#include"selectbutton.h"
#include"stilltower.h"
class GameWindow:public QMainWindow
{
protected:
    const int LevelNumber;
private:
    int life = 10;      //生命数量
    QVector<Towerspot*> TowerspotVec;  //防御塔坑数组
    QVector<StillTower*> StillVec;
    Selectbutton* SelButton = new Selectbutton(":/selectbutton.png"); //选择框类
         inline bool DeductionMoney(int);         //判断金钱是否足够并刷新标签
    QVector<towerparent*> TowerparVec;

    QVector<monster*> MonsterVec;           //怪物数组

    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);


    void DrawMapArr(QPainter&);             //用于画出地图函数
    void DrawSelectionBox(QPainter&);
    void DrawDefenseTower(QPainter&);
    void DrawMonster(QPainter&);
    void DrawRangeAndUpgrade(QPainter&);


    int DisplayRangeX, DisplayRangeY;
    bool DisplayRange = false;
     QMediaPlayer player;
     QLabel *moneylable = new QLabel(this);

    int money = 1000;   //记录金钱
    int counter = 0;    //用于产生怪物的计数器

  int mhealth;

    CoorStr *homecoor = new CoorStr(0, 0);

    void IrodMonsProgDefa(CoorStr**, CoorStr**, CoorStr*, int*); //预设两条路产生怪物方案函数

    bool DisplayAllRange = false;  //标识是否显示所有防御塔的攻击范围

public:

    GameWindow(int);
    ~GameWindow();

};

#endif // GAMEWINDOW_H
