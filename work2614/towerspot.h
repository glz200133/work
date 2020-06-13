#ifndef TOWERSPOT_H
#define TOWERSPOT_H

#include <QVector>
class Towerspot
{
protected:
    const int mx, my;           //位置坐标
    const int mwidth, mheight;  //宽高
public:
    Towerspot(int x, int y, int width = 80, int height = 80);
    int GetX() const;
    int GetY() const;
    int GetWidth() const;
    int GetHeight() const;
};

#endif // TOWERSPOT_H
