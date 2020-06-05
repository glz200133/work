#include "towerparent.h"

towerparent::towerparent()
{

}
int towerparent::GetX() const     //横坐标
{
    return mx;
}

int towerparent::GetY() const     //纵坐标
{
    return my;
}

int towerparent::GetWidth() const //宽
{
    return width;
}

int towerparent::GetHeight() const //高
{
    return height;
}


QString towerparent::GetBaseImg() const  //获取底座图片
{
    return baseimg;
}

QString towerparent::GetDefImg() const   //获取防御塔图片
{
    return towimg;
}
int towerparent::GetRange() const           //射程
{
    return range;
}


void towerparent::SetWidthHeight(int width, int height)  //设置防御塔宽高
{
    this->width = width;
    this->height = height;
}

void towerparent::SetXY(int x, int y)       //设置防御塔坐标
{
    this->mx = x, this->my = y;
}

int& towerparent::SetRange() //设置防御塔的攻击范围
{
    return range;
}



