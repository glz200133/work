#include "towerson1.h"
//一种防御塔，从父防御塔继承而来
//目前防御塔子类里的参数都是随便设的，具体数值等待调试
towerson1::towerson1(int x, int y, int sUpLeftX, int sUpLeftY, int swidth, int sheight)
{
    mx = x, my = y;
    baseimg = QString("//");//这里面写图片的路径
    towimg = QString("");//格式如下:/image/GreenBottle.png
    width = swidth, height = sheight;
    upx = sUpLeftX, upy = sUpLeftY;

    range = 170;

    BullPath = QString("");//子弹的图片格式如下:/image/Shells0.png
    bullwidth = 25, bullheight = 25;           //子弹大小

    attack = 31;

}
