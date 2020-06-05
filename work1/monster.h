#ifndef MONSTER_H
#define MONSTER_H

#include <QVector>
#include <QString>
#include"mainstruct.h"
class monster
{


private:
    QVector<CoorStr*> Waypoint;  //存储怪物路径点数组
    int mx, my;                  //怪物坐标
    int mwidth, mheight;         //怪物宽高
    QString ImgPath;             //怪物图片路径
    int id;                      //怪物编号
    int health;                  //怪物生命值
    const int mspeed = 10;       //怪物每次刷新页面移动的像素距离这个值不能改变

public:
    //参数：路径点数组、路径点的个数、怪物初始坐标、怪物宽度、怪物图片路径
    monster(CoorStr **arr, int length, int x, int y, int fid);  //构造

    bool Move();            //怪物移动函数

    int GetX() const;       //获取横坐标
    int GetY() const;       //获取横坐标
    int GetWidth() const;   //获取宽
    int GetHeight() const;  //获取高
    QString GetImgPath() const; //获取图片路径
    int GetId() const;      //获取编号
    int GetHealth() const;  //获取生命值
    void SetHealth(int);    //设置生命值
};

#endif // MONSTER_H
