#ifndef SELECTBUTTON_H
#define SELECTBUTTON_H

#include <QString>
#include "mainstruct.h"
#include<QPainter>
#include<QPoint>
#include<QPainter>

class Selectbutton
{

protected:
    bool display = false;   //是否显示
    int mx = 0, my = 0;
    const int mwidth, mheight; //整体宽高
    QString SelecBoxImgPath;

    SubbutStr SubBut[4];    //四个塔

public:
    Selectbutton(QString Path, int width = 270, int height = 270);

    int GetX() const;     //获取横坐标
    int GetY() const;     //获取横坐标
    int GetWidth() const; //获取宽
    int GetHeight() const;//获取高
    QString GetImgPath() const; //获取选择框图片路径
    bool GetDisplay() const;
    void SetDisplay(const bool SetPlay); //设置显示状态
    void CheckTower(int x, int y); //选中防御塔
    SubbutStr* GetSelSubBut();
};

#endif // SELECTBUTTON_H
