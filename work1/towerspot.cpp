#include "towerspot.h"

Towerspot::Towerspot(int x, int y, int width, int height): mx(x), my(y), mwidth(width), mheight(height)
{

}
int Towerspot::GetX() const
{
    return mx;
}

int Towerspot::GetY() const
{
    return my;
}

int Towerspot::GetWidth() const
{
    return mwidth;
}

int Towerspot::GetHeight() const
{
    return mheight;
}

