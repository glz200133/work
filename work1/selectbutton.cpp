#include "selectbutton.h"

Selectbutton::Selectbutton(QString Path, int width, int height) : SelecBoxImgPath(Path),mwidth(width), mheight(height)
{

}
int Selectbutton::GetX() const     //获取横坐标
{
    return mx;
}
int Selectbutton::GetY() const     //获取横坐标
{
    return my;
}
int Selectbutton::GetWidth() const //获取宽
{
    return mwidth;
}
int Selectbutton::GetHeight() const //获取高
{
    return mheight;
}

QString Selectbutton::GetImgPath() const    //返回选择框图片路径
{
    return SelecBoxImgPath;
}


bool Selectbutton::GetDisplay() const
{
    return display;
}


void Selectbutton::SetDisplay(const bool SetPlay)
{
    display = SetPlay;
}

//选中防御塔
void Selectbutton::CheckTower(int x, int y)
{
    //确定选择框的位置
    mx = x - 95, my = y - 95;

    //确定子按钮的位置
    SubBut[0].SubX = mx + 106, SubBut[0].SubY = my + 35;
    SubBut[0].SubImgPath = QString(":/tower1.png");

    SubBut[1].SubX = mx + 35, SubBut[1].SubY = my +106;
    SubBut[1].SubImgPath = QString(":/tower2.png");

    SubBut[2].SubX = mx + 180, SubBut[2].SubY = my + 106;
    SubBut[2].SubImgPath = QString(":/tower3.png");

    SubBut[3].SubX = mx + 106, SubBut[3].SubY = my + 190;
    SubBut[3].SubImgPath = QString(":/tower4.png");

    display = true;
}

SubbutStr* Selectbutton::GetSelSubBut()
{
    return SubBut;
}
