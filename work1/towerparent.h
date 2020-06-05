#ifndef TOWERPARENT_H
#define TOWERPARENT_H

#include <QString>
#include "monster.h"
//本版本无爆炸效果，以及旋转等
class towerparent
{
public:
    towerparent();

    protected:
        int mx, my;
        int width, height;
        QString baseimg;
        QString towimg;


        int range;

    public:
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
