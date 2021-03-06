#include "towerparent.h"

towerparent::towerparent()
{

}
int towerparent::GetX() const     //横坐标
{
    return mx;
}

int towerparent::GetY() const     //纵坐标
{
    return my;
}

int towerparent::GetWidth() const //宽
{
    return width;
}

int towerparent::GetHeight() const //高
{
    return height;
}


QString towerparent::GetBaseImg() const  //获取底座图片
{
    return baseimg;
}

QString towerparent::GetDefImg() const   //获取防御塔图片
{
    return towimg;
}
int towerparent::GetRange() const           //射程
{
    return range;
}


void towerparent::SetWidthHeight(int width, int height)  //设置防御塔宽高
{
    this->width = width;
    this->height = height;
}

void towerparent::SetXY(int x, int y)       //设置防御塔坐标
{
    this->mx = x, this->my = y;
}

int& towerparent::SetRange() //设置防御塔的攻击范围
{
    return range;
}
monster* towerparent::GetAimsMonster() const //返回当前防御塔的目标怪物
{
    return aimmonster;
}

void towerparent::SetAimsMonster(monster* mon)  //设置当前防御塔的目标怪物
{
    aimmonster = mon;
}
int towerparent::GetUpLeftX() const
{
    return upx;
}

int towerparent::GetUpLeftY() const
{
    return upy;
}
QString towerparent::GetBulletPath() const      //返回防御塔子弹图片路径，在防御塔子类中实现
{
    return BullPath;
}

QVector<BulletStr*>& towerparent::GetBulletVec()//返回子弹数组
{
    return BulletVec;
}

void towerparent::InterBullet()     //新建子弹函数
{
    counter++;

    if(counter < 7 || !aimmonster)      //计数器到达一定数值且目标怪物不为空时
        return;

    //向子弹数组中插入子弹
    BulletStr *bull = new BulletStr(CoorStr(upx + 40, upy + 40));

    bull->coor.x = upx + 40, bull->coor.y = upy + 40;

    //计算每一个子弹的路径
    if((!(aimmonster->GetX() - bull->coor.x)))   //除数为0或时不创建子弹
    {
        delete bull;
        bull = NULL;
        goto L1;
    }

    bull->k = (aimmonster->GetY() - bull->coor.y) / (aimmonster->GetX() - bull->coor.x);
    bull->b = aimmonster->GetY() - aimmonster->GetX() * bull->k;

    bull->coor.x = upx + 40, bull->coor.y = upy + 40;

    BulletVec.push_back(bull);              //将子弹插入到子弹数组当中

    if(aimmonster->GetX() <= upx + 40)     //确定子弹的移动方向
        bull->dirflag = true;
    L1:

    counter = 0;    //计数器重置为0

}

void towerparent::BulletMove()         //子弹移动函数
{
    //子弹移动,重点项目，虽然编译能通过，但好像有bug
    for(auto bulli : BulletVec)  //遍历子弹组
    {
        const int speed = 24;              //子弹移动速度，每一次刷新画面移动的像素距离，这个值可以随意

        //子弹的移动方向
        //左则子弹x坐标每次-=，反之+=
        bulli->dirflag ? bulli->coor.x -= speed : bulli->coor.x += speed;

        bulli->coor.y = bulli->k * bulli->coor.x + bulli->b;    //子弹纵坐标改变
    }

    for(auto bullit = BulletVec.begin(); bullit != BulletVec.end(); bullit++)         //删除越界子弹
        if((*bullit)->coor.x > 1040 || (*bullit)->coor.x < 0 || (*bullit)->coor.y > 640 || (*bullit)->coor.y < 0)
        {
            delete bullit;
            BulletVec.erase(bullit);
            break;
        }
}

int towerparent::GetBulletWidth() const //设计子弹的大小，即长与宽
{
    return bullwidth;
}

int towerparent::GetBulletHeight() const
{
    return bullheight;
}

int towerparent::GetAttack() const      //获取并设置防御塔攻击力
{
    return attack;
}

void towerparent::SetAttack(int attack)
{
    this->attack = attack;
}
void towerparent::SetBulletWidthHeight(int width, int height)         //设置子弹宽高
{
    bullwidth = width, bullheight = height;
}


