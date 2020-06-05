#ifndef TOWERSON1_H
#define TOWERSON1_H

#include "towerparent.h"
#include "bullet.h"
//一种防御塔的模板
//剩下的防御塔格式相当
class towerson1:public towerparent,public Bullet
{
public:
    towerson1(int x, int y, int sUpLeftX, int sUpLeftY, int swidth = 80, int sheight = 80);
};

#endif // TOWERSON1_H
