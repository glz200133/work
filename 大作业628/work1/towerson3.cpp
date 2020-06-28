#include "towerson3.h"

towerson3::towerson3(int x, int y, int sUpLeftX, int sUpLeftY, int swidth, int sheight)
{
    mx = x, my = y;
    baseimg = QString(":/set.png");//这里面写图片的路径
    towimg = QString(":/tower3.png");
    width = swidth, height = sheight;
    upx = sUpLeftX, upy = sUpLeftY;

    range = 150;

    BullPath = QString(":/bullet4.png");
    bullwidth = 30, bullheight = 30;           //子弹大小

    attack = 400;

}
