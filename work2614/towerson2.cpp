#include "towerson2.h"

towerson2::towerson2(int x, int y, int sUpLeftX, int sUpLeftY, int swidth, int sheight)
{

        mx = x, my = y;
        baseimg = QString(":/set.png");//这里面写图片的路径
        towimg = QString(":/tower2.png");
        width = swidth, height = sheight;
        upx = sUpLeftX, upy = sUpLeftY;

        range = 140;

        BullPath = QString(":/bullet1.png");
        bullwidth = 50, bullheight = 50;           //子弹大小

        attack = 310;



}
