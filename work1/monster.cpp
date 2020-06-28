#include "monster.h"
#include <QDebug>
#include<Qpoint>
#include<QPainter>
monster::monster(CoorStr **arr, int length, int x, int y, int fid) :
    mx(x), my(y), id(fid)
{
    for(int i = 0; i < length; i++)
        //将传进来的数组插入到Waypoint动态数组
        Waypoint.push_back(arr[i]);


    //确定不同怪物的生命值
    switch (id)
    {
    case 1:
        health = 310;   //生命值
        mwidth = 64, mheight = 64;  //宽高
        ImgPath = ":/monster1.png";//图片的路径，但现在还没有设置
        break;
    case 2:
        health = 310;
        mwidth = 64, mheight = 64;
        ImgPath = ":/monster2.png";
        break;
    case 3:
        health = 310;
        mwidth = 64, mheight = 64;
        ImgPath = ":/monster3.png";
        break;
    case 4:
        health = 310;
        mwidth =64 , mheight = 64;
        ImgPath = ":/monster4.png";
        break;
    case 5:
        health = 310;
        mwidth = 64, mheight = 64;
        ImgPath = ":/monster5.png";
        break;
    default:
        break;
    }
}

//怪物按设定路径点移动
bool monster::Move()
{
    if(Waypoint.empty())
        return true;

    //如果第一个路径点的y小于怪物原本的路径点，则怪物向下走
    if (Waypoint.at(0)->y > my) //下
    {
        my += mspeed;
        return false;
    }

    if (Waypoint.at(0)->x < mx) //左
    {
        mx -= mspeed;
        return false;
    }

    if (Waypoint.at(0)->x > mx) //右
    {
        mx += mspeed;
        return false;
    }

    if (Waypoint.at(0)->y < my) //上
    {
        my -= mspeed;
        return false;
    }

    //如果怪物的坐标
    //路径点坐标几乎重合，则删除这个路径点
    if (Waypoint.at(0)->y == my && Waypoint.at(0)->x == mx)
    {

        Waypoint.erase(Waypoint.begin());       //从数组中删除


    }

    return false;
}


int monster::GetX() const       //获取横坐标
{
    return mx;
}

int monster::GetY() const       //获取横坐标
{
    return my;
}

int monster::GetWidth() const   //获取宽
{
    return mwidth;
}

int monster::GetHeight() const  //获取高
{
    return mheight;
}

QString monster::GetImgPath() const //获取图片路径
{
    return ImgPath;
}

int monster::GetId() const      //获取编号
{
    return id;
}

int monster::GetHealth() const  //获取生命值
{
    return health;
}

void monster::SetHealth(int fhealth)//设置生命值
{
    health = fhealth;
}
int monster::GetSpeed()const
{

    return mspeed;
}

void monster::SetSpeed(int sp)
{
    mspeed=sp;
}
