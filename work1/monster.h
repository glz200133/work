#ifndef MONSTER_H
#define MONSTER_H

#include <QVector>
#include <QString>
#include"mainstruct.h"
#include<QPainter>
class monster
{


private:
    QVector<CoorStr*> Waypoint;  //存储怪物路径点数组
    int mx, my;
    int mwidth, mheight;
    QString ImgPath;
    int id;
    int health;
      int mhealth;
     int mspeed = 5;       //怪物每次刷新页面移动的像素距离这个值不能改变
    const int speed=10;

public:

    monster(CoorStr **arr, int length, int x, int y, int fid);  //构造

    bool Move();            //怪物移动函数
    void Drawhealthbar(QPainter*painter);
    int GetX() const;
    int GetY() const;
    int GetWidth() const;
    int GetHeight() const;
    QString GetImgPath() const; //获取图片路径
    int GetId() const;
    int GetHealth() const;
    void SetHealth(int);
    int GetSpeed()const;
    void SetSpeed(int);

};

#endif // MONSTER_H
