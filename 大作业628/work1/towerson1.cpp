#include "towerson1.h"

//一种防御塔，从父防御塔继承而来
//目前防御塔子类里的参数都是随便设的，具体数值等待调试
towerson1::towerson1(int x, int y, int sUpLeftX, int sUpLeftY, int swidth, int sheight)
{
    mx = x, my = y;
    baseimg = QString(":/set.png");
    towimg = QString(":/tower1.png");
    width = swidth, height = sheight;
    upx = sUpLeftX, upy = sUpLeftY;

    range = 150;

    BullPath = QString(":/bullet2.png");
    bullwidth = 30, bullheight = 30;           //子弹图片大小

    attack = 150;

}
