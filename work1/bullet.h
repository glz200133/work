#ifndef BULLET_H
#define BULLET_H
#include "monster.h"
#include "towerparent.h"
class Bullet
{
public:
    monster* GetAimsMonster() const;//返回当前防御塔的目标怪物
    void SetAimsMonster(monster*);  //设置当前防御塔的目标怪物
    QString GetBulletPath() const;  //返回防御塔子弹图片

    QVector<BulletStr*>& GetBulletVec();//返回子弹数组
    int GetUpLeftX() const; //获取防御塔左上角原横坐标
    int GetUpLeftY() const; //获取防御塔左上角原纵坐标
    void InterBullet();
    //新建子弹
    void BulletMove();
    //子弹移动函数
    int GetBulletWidth() const;
    //获取子弹的宽度
    int GetBulletHeight() const;
    //获取子弹的宽度
    int GetAttack() const;
    //防御塔攻击力

    void SetAttack(int);
    //设置防御塔攻击力
    void SetBulletWidthHeight(int, int);    //设置子弹宽高

protected:
    int upx,upy;   //防御塔左上坐标
     monster* aimmonster = NULL;  //记录防御塔的目标怪物
    QString BullPath;       //子弹图片
    int power;              //子弹威力
    int bullwidth, bullheight;      //子弹宽的高
    QVector<BulletStr*> BulletVec;  //子弹结构数组
    int counter = 0;        //用于控制发射子弹的速度
    int attack;             //防御塔攻击力

};

#endif // BULLET_H
