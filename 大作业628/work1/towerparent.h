#ifndef TOWERPARENT_H
#define TOWERPARENT_H

#include <QString>
#include "monster.h"
#include<QPainter>
#include<QVector>
class towerparent
{
public:


    QString GetBulletPath() const;  //返回防御塔子弹图片

    QVector<BulletStr*>& GetBulletVec();//返回子弹数组

    void InterBullet();
    //新建子弹
    void BulletMove();
    //子弹移动函数
    int GetBulletWidth() const;
    //获取子弹的宽度
    int GetBulletHeight() const;
    //获取子弹的宽度
    int GetAttack() const;
    //防御塔攻击力

    void SetAttack(int);
    //设置防御塔攻击力
    void SetBulletWidthHeight(int, int);    //设置子弹宽高
        monster* GetAimsMonster() const;//返回当前防御塔的目标怪物
        void SetAimsMonster(monster*);  //设置当前防御塔的目标怪物
        int GetUpLeftX() const; //获取防御塔左上角原横坐标
        int GetUpLeftY() const; //获取防御塔左上角原纵坐标



protected:


      QString BullPath;       //子弹图片
     int power;              //子弹威力
     int bullwidth, bullheight;      //子弹宽的高
     QVector<BulletStr*> BulletVec;  //子弹结构数组
     int counter = 0;        //用于控制发射子弹的速度
     int attack;             //防御塔攻击力
    int upx,upy;   //防御塔左上坐标
     monster* aimmonster = NULL;  //记录防御塔的目标怪物


        int mx, my;
        int width, height;
        QString baseimg;
        QString towimg;
        int range;

    public:
        towerparent();
        int GetX() const;
        int GetY() const;
        int GetWidth() const;
        int GetHeight() const;

        QString GetBaseImg() const; //fangyutadizuotup

        QString GetDefImg() const;  //获取防御塔图片路径

        int GetRange() const;   //设置防御塔的射程

        void SetWidthHeight(int, int);//防御塔宽和高

        void SetXY(int, int);//防御塔坐标

        int& SetRange();//防御塔的攻击范围




};

#endif // TOWERPARENT_H
