#ifndef TOWERSON4_H
#define TOWERSON4_H
 #include "towerparent.h"
#include"stilltower.h"
class towerson4: public StillTower
{
public:
    towerson4(int x, int y, int sUpLeftX, int sUpLeftY, int swidth = 80, int sheight = 80);
};

#endif // TOWERSON4_H
