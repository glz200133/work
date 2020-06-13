#include "gamewindow.h"
#include <QDebug>
#include <QPushButton>
#include<QPixmap>
#include<QPoint>
#include<QPainter>
#include<QPaintEvent>
#include<towerson1.h>
#include<mainstruct.h>
#include<towerson3.h>
#include<towerson2.h>
#include<towerparent.h>
#include<towerson4.h>
#include<monster.h>
//鼠标点击区域宏
#define MouClickRegion(X, Width, Y, Height)     \
(ev->x() >= (X) && ev->x() <= (X) + (Width) &&  \
ev->y() >= (Y) && ev->y() <= (Y) + (Height))

//计算两点之间距离宏
#define DistBetPoints(X1, Y1, X2, Y2)           \
abs(sqrt((((X1) - (X2)) * ((X1) - (X2))) + (((Y1) - (Y2)) * ((Y1) - (Y2)))))

//用于方便通过格子确定路径点坐标
#define X40(X, Y) ((X) - 1) * 40 + 10, ((Y) - 1) * 40 + 10

//插入怪物  路径点数组名、怪物初始坐标、怪物编号
#define InsterMonster(PathNum, StaCoorNum, MonsterId)     \
MonsterVec.push_back (new monster(pointarr[PathNum], PathLength[PathNum], X40(staco[StaCoorNum].x, staco[StaCoorNum].y), MonsterId));


//判断金钱是否足够并刷新标签
inline bool GameWindow::DeductionMoney(int money)
{
    if (this->money - money < 0) return true; //判断金钱是否足够
    this->money -= money; //扣除金钱
    moneylable->setText(QString("金钱：%1").arg(this->money));
    return false;
}


GameWindow::GameWindow(int lv): LevelNumber(lv)
{


setFixedSize(1040, 640);


setWindowTitle("游戏界面");

//显示的按钮
QPushButton* disranpush = new QPushButton(this);
disranpush->setStyleSheet("color:white");
disranpush->setGeometry(900,30, 150, 45);
disranpush->setFont(QFont("微软雅黑", 12));
disranpush->setText("显示全部范围");

connect(disranpush,&QPushButton::clicked,[=]()
{//通过改变标识令防御塔攻击范围显示或关闭
    if (DisplayAllRange)
    {
        DisplayAllRange = false;
        disranpush->setText("显示攻击范围");
    }
    else
    {
        DisplayAllRange = true;
        disranpush->setText("隐藏攻击范围");
    };
    update();
});

//胜利标签
QLabel *victorylable = new QLabel(this);
victorylable->move(176, 180);
victorylable->setFont(QFont("楷体", 110));
victorylable->setText(QString("游戏胜利"));
victorylable->hide();

QTimer* timer2 = new QTimer(this);      //用于插入怪物定时器，开始时间
timer2->start(2000);


connect(timer2,&QTimer::timeout,[=]()
{
    //根据关卡编号确定执行怪物的路径方案
    switch (LevelNumber)
    {
    case 0:
    {
        //设置路径点
        CoorStr* Waypointarr1[] = {new CoorStr(X40(1, 15)), new CoorStr(homecoor->x, homecoor->y)};
        CoorStr* Waypointarr2[] = {new CoorStr(X40(25, 15)),  new CoorStr(homecoor->x, homecoor->y)};
        //怪物的四个起始点
        CoorStr staco[] = {CoorStr(1, 0), CoorStr(25, 0), CoorStr(1, -1), CoorStr(25, -1)};

        //每条路径的结点个数
        int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

        IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路产生怪物方案

        break;
    }
    case 1:
    {
        //设置路径点,即怪物在路径点处转向
        CoorStr* Waypointarr1[] = {new CoorStr(X40(10, 5)), new CoorStr(X40(8, 5)), new CoorStr(X40(8, 12)), new CoorStr(X40(13, 12)), new CoorStr(homecoor->x, homecoor->y)};
        CoorStr* Waypointarr2[] = {new CoorStr(X40(16, 5)), new CoorStr(X40(18, 5)), new CoorStr(X40(18, 12)), new CoorStr(X40(13, 12)), new CoorStr(homecoor->x, homecoor->y)};

                                  //怪物的四个起始点
        CoorStr staco[] = {CoorStr(10, 0), CoorStr(16, 0), CoorStr(10, -1), CoorStr(16, -1)};

        //每条路径的结点个数
        int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

        IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路产生怪物方案
        break;
    }

    case 2:
    {
        //设置路径点
        CoorStr* Waypointarr1[] = {new CoorStr(X40(1, 5)), new CoorStr(X40(5, 5)), new CoorStr(X40(5, 11)),new CoorStr(X40(3, 11)), new CoorStr(X40(3, 15)),new CoorStr(homecoor->x, homecoor->y)};
        CoorStr* Waypointarr2[] = {new CoorStr(X40(21, 3)), new CoorStr(X40(15, 3)), new CoorStr(X40(15, 9)), new CoorStr(X40(19, 9)), new CoorStr(X40(19, 15)), new CoorStr(homecoor->x, homecoor->y)};

        //怪物的四个起始点
        CoorStr staco[] = {CoorStr(1, 0), CoorStr(21, 0), CoorStr(1, -1), CoorStr(21, -1)};


        int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

        IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength, victorylable);   //使用预设的两条路的产生怪物方案
        break;
    }
    }
});


//显示金钱

moneylable->setGeometry(600,100,400, 120);       //位置

moneylable->setFont(QFont("Microsoft YaHei", 24));             //设置字体
moneylable->setText(QString("money：%1").arg(money));    //显示金钱信息

//生命值标签
QLabel *lifelable = new QLabel(this);
lifelable->setGeometry(600, 100, 220, 40);   //设置控件位置和大小
lifelable->setFont(QFont("Microsoft YaHei", 24));
lifelable->setText(QString("life：%1").arg(life));

//定时器每时每刻执行防御塔父类数组的活动函数
    QTimer* timer = new QTimer(this);
    timer->start(120);

    connect(timer,&QTimer::timeout,[=]()
    {
        //防御塔寻找目标怪物的规律：找到最后一个怪物作为目标，目标丢失后找再继续找最后一个目标
        for (auto defei :TowerparVec)      //遍历防御塔
        {
            if (!defei-> GetAimsMonster())   //目标怪物为空时从后往前遍历怪物数组寻找目标怪物
            {
                for(int i = MonsterVec.size() - 1; i >= 0; i--)
                    //这里以防御塔中心点和怪物中心点判断
                    if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                        MonsterVec.at(i)->GetX() + (MonsterVec.at(i)->GetWidth() >> 1),
                        MonsterVec.at(i)->GetY() + (MonsterVec.at(i)->GetHeight() >> 1)) <= defei->GetRange())
                    {
                        defei->SetAimsMonster(MonsterVec.at(i));    //设置防御塔的目标怪物
                        break;
                    }
            }
            else                //当前防御塔拥有目标且怪物在防御塔范围之内时时攻击怪物
                if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                    defei-> GetAimsMonster()->GetX() + (defei->GetAimsMonster()->GetWidth() >> 1),
                    defei-> GetAimsMonster()->GetY() + (defei->GetAimsMonster()->GetHeight() >> 1)) <= defei->GetRange())
                {

                     defei->InterBullet();           //拥有目标时一直创建子弹
                }

            //每次循环都判断目标怪物距离防御塔的距离，写在上面可能会不太好
            if (defei->GetAimsMonster())    //目标怪物不为空
                if (DistBetPoints(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40,
                    defei -> GetAimsMonster() -> GetX() + (defei -> GetAimsMonster() -> GetWidth() >> 1),
                    defei ->GetAimsMonster()->GetY() + (defei->GetAimsMonster()->GetHeight() >> 1)) > defei->GetRange())
                        defei->SetAimsMonster(NULL);     //超过距离将目标怪物设为空
        }
        //防御塔子弹移动
        for (auto defei : TowerparVec)
            defei->BulletMove();

        //怪物移动
        for (auto Moni = MonsterVec.begin(); Moni != MonsterVec.end(); Moni++)
            if((*Moni)->Move()) //怪物走到终点
            {
                delete *Moni;
                MonsterVec.erase(Moni);         //怪物走到终点则删除这个怪物

                life--;                         //我们的生命数量-1
                lifelable->setText(QString("生命：%1").arg(life));

                if (life <= 0) this->close();   //生命值为0时关闭该窗口

                break;
            }

        //判断子弹击中怪物
        for (auto defei : TowerparVec)
        {
            auto &tbullvec = defei->GetBulletVec();
            for (auto bullit = tbullvec.begin(); bullit != tbullvec.end(); bullit++)
                for (auto monit = MonsterVec.begin(); monit != MonsterVec.end(); monit++)
                    if ((*bullit)->GetX() + (defei->GetBulletWidth() >> 1) >= (*monit)->GetX() && (*bullit)->GetX() <= (*monit)->GetX() + (*monit)->GetWidth() &&
                       (*bullit)->GetY() + (defei->GetBulletHeight() >> 1) >= (*monit)->GetY() && (*bullit)->GetY() <= (*monit)->GetY() + (*monit)->GetHeight())
                    {
                        tbullvec.erase(bullit);     //删除子弹

                        (*monit)->SetHealth((*monit)->GetHealth() - defei->GetAttack());      //敌人血量 = 本身血量减去 当前炮塔攻击力



                        if ((*monit)->GetHealth() <= 0) //生命值为空时
                        {
                            //判断一下其他防御塔的目标怪物是否和当前防御塔消灭的怪物重复，如果重复，则将那一个防御塔的目标怪物也设为空
                            for (auto defei2 : TowerparVec)
                                if (defei2->GetAimsMonster() == *monit)
                                    defei2->SetAimsMonster(NULL);

                            MonsterVec.erase(monit);
                            money += RewardMoney;       //增加金钱
                            moneylable->setText(QString("金钱：%1").arg(money));
                        }


                        goto L1;
                    }
            L1:;
        }



        update();   //绘图
    });
}


//预设的两条路产生怪物方案
void GameWindow::IrodMonsProgDefa(CoorStr** Waypointarr1, CoorStr** Waypointarr2, CoorStr* staco, int* PathLength, QLabel* victorylable)
{
    /*两条路径*/
    CoorStr** pointarr[] = {Waypointarr1, Waypointarr2};

    //插入怪物
    if(counter >= 1 && counter <= 12)
    {
        InsterMonster(0, 0, 1); //第几条路径、第几个起始点、怪物编号
    }
    else if(counter > 12 && counter <= 34)
    {
        InsterMonster(0, 0, 1);
        InsterMonster(1, 1, 2);
    }
    else if (counter > 34 && counter <= 35)
    {
        InsterMonster(0, 0, 3);
        InsterMonster(1, 1, 3);
    }
    else if (counter > 35 && counter <= 52)
    {
        InsterMonster(0, 2, 4);
        InsterMonster(0, 0, 4);
        InsterMonster(1, 1, 1);
    }
    if(counter > 52 && counter <= 56)
    {
        InsterMonster(0, 0, 3);
        InsterMonster(1, 1, 3);
    }
    if (counter > 52 && counter <= 71)
    {
        InsterMonster(0, 2, 2);
        InsterMonster(0, 0, 5);
        InsterMonster(1, 3, 1);
        InsterMonster(1, 1, 4);
    }

    if (counter > 71 && MonsterVec.empty())   //时间大于71且怪物数组为空时游戏胜利
        victorylable->show();

    counter++;          //计数器+1
    update();
}

//根据数组画出地图函数

void GameWindow::DrawMapArr(QPainter& painter)
{
    //地图数组  第一关
    int Map_1[16][26] =
    {
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 1, 1,
        1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 1, 1,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 1, 1,
        1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 1, 1,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1,
        1, 1, 3, 6, 0, 0, 0, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 0, 0, 0, 3, 6, 1, 1,
        1, 1, 6, 6, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 6, 6, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    };
    //第二关
    int Map_2[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 3, 6, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 6, 6, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 3, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 6, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 5, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    int Map_3[16][26] =
    {
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 3, 6, 0, 0,
        1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 6, 6, 0, 0,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 3, 6, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 6, 6, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
        3, 6, 1, 1, 0, 0, 3, 6, 0, 0, 3, 6, 0, 0, 0, 0, 3, 6, 1, 1, 0, 0, 0, 0, 0, 0,
        6, 6, 1, 1, 0, 0, 6, 6, 0, 0, 6, 6, 0, 0, 0, 0, 6, 6, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    };

    int Map[16][26];

    switch (LevelNumber)
    {
    case 0:
        memcpy(Map, Map_1, sizeof(Map));
        break;
    case 1:
        memcpy(Map, Map_2, sizeof(Map));
        break;
    case 2:
        memcpy(Map, Map_3, sizeof(Map));
        break;
    default:
        break;
    }

    for (int j = 0; j < 16; j++)
        for (int i = 0; i < 26; i++)
        {
            switch (Map[j][i])
            {
            case 0:
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/floor1.jpg"));
                break;
            case 1:
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/floor3.jpg"));
                break;
            case 3:
                painter.drawPixmap(i * 40, j * 40, 80, 80,
                    QPixmap(":/floor6.png"));

                TowerPitVec.push_back(new Towerspot(i * 40, j * 40));
                break;
            case 5:
                painter.drawPixmap(i * 40, j * 40, 40, 40,
                    QPixmap(":/floor3.jpg"));
                homecoor->x = i * 40, homecoor->y = j * 40;
                break;
            }
        }

    painter.drawPixmap(homecoor->x, homecoor->y, 80, 80,
        QPixmap(":/treasure.png"));//家

}

//画出选择框
void GameWindow::DrawSelectionBox(QPainter& painter)
{
   // 显示选择框
   if (!SelButton->GetDisplay())
        return;

  // 画出选择框
    painter.drawPixmap(SelButton->GetX(),SelButton->GetY(), SelButton->GetWidth(), SelButton->GetHeight(),
        QPixmap(SelButton->GetImgPath()));

    //画出子按钮
   SubbutStr *ASubBut = SelButton->GetSelSubBut();
    for (int i = 0; i < 4; i++)
        painter.drawPixmap(ASubBut[i].SubX, ASubBut[i].SubY, ASubBut[i].SubWidth, ASubBut[i].SubHeight,
            QPixmap(ASubBut[i].SubImgPath));

    painter.setPen(QPen(Qt::yellow, 6, Qt::SolidLine));
    painter.drawRect(QRect(SelButton->GetX() + 95, SelButton->GetY() + 95, 80, 80));
}

//画出防御塔

void GameWindow::DrawDefenseTower(QPainter& painter)
{
    //画出防御塔
    for (auto defei : TowerparVec)  //遍历防御塔数组
    {
        //画出底座
        painter.drawPixmap(defei->GetUpLeftX(), defei->GetUpLeftY(), 80, 80, QPixmap(defei->GetBaseImg()));

        //画出所有防御塔的攻击范围
        if(DisplayAllRange)
            painter.drawEllipse(QPoint(defei->GetUpLeftX() + 40, defei->GetUpLeftY() + 40), defei->GetRange(), defei->GetRange());

        //画出所有防御塔子弹
        for (auto bulli : defei->GetBulletVec())
            painter.drawPixmap(bulli->coor.x, bulli->coor.y, defei->GetBulletWidth(), defei->GetBulletHeight(),QPixmap(defei->GetBulletPath()));


        painter.drawPixmap(defei->GetX(), defei->GetY(), defei->GetWidth(), defei->GetHeight(), QPixmap(defei->GetDefImg()));

        painter.resetTransform();   //重置调整
    }
}

//画出怪物
void GameWindow::DrawMonster(QPainter& painter)
{
    for (auto moni : MonsterVec)//画出怪物
       { painter.drawPixmap(moni->GetX(), moni->GetY(), moni->GetWidth(), moni->GetHeight(), QPixmap(moni->GetImgPath()));
    QPoint healthBarPoint = QPoint(moni->GetX(), moni->GetY()) + QPoint(1, 0);
    // 绘制血条
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::green);
    QRect healthBarBackRect(healthBarPoint, QSize(60, 2));
    painter.drawRect(healthBarBackRect);

    painter.setBrush(Qt::red);
    QRect healthBarRect(healthBarPoint, QSize( moni->GetHealth()/310, 2));
    painter.drawRect(healthBarRect);
}
}

//防御塔
void GameWindow::DrawRangeAndUpgrade(QPainter& painter)
{
    //画防御塔攻击范围
    for (auto defei : TowerparVec)
        if(defei->GetUpLeftX() == DisplayRangeX && defei->GetUpLeftY() == DisplayRangeY && DisplayRange)
        {   //画出防御塔攻击范围
            painter.setPen(QPen(Qt::white));
            painter.drawEllipse(QPoint(DisplayRangeX + 40, DisplayRangeY + 40), defei->GetRange(), defei->GetRange());
            painter.drawPixmap(DisplayRangeX + 10, DisplayRangeY - 80, 60, 60, QPixmap(":/rankup.png"));
        }
}


//绘图事件
void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);     //创建画家类

    painter.setRenderHint(QPainter::Antialiasing);    //设置抗锯齿

    DrawMapArr(painter);        //画出地图

    DrawDefenseTower(painter);  //画出防御塔和子弹

    DrawMonster(painter);       //画出怪物

    DrawRangeAndUpgrade(painter);//画出攻击范围和升级按钮

    DrawSelectionBox(painter);  //画出选择框
}

//鼠标点击事件
void GameWindow::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() != Qt::LeftButton)
        return;

    //判断升级按钮的点击
    if (DisplayRange)
    {
        if (MouClickRegion(DisplayRangeX + 10, 60 , DisplayRangeY - 80, 60))
        {
            //设置防御塔宽高，攻击力，微调坐标
            for (auto defei : TowerparVec)
                if (defei->GetUpLeftX() == DisplayRangeX && defei->GetUpLeftY() == DisplayRangeY && DisplayRange)
                {
                    if (DeductionMoney(200)) return;        //升级防御塔需要花费200

                    defei->SetAttack(defei->GetAttack() + 20);          //每次升级防御塔攻击力+20
                    defei->SetWidthHeight(defei->GetWidth() + 12, defei->GetHeight() + 6);   //防御塔宽高增加
                    defei->SetXY(defei->GetX() - 6, defei->GetY() - 3); //调整防御塔坐标
                    defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                    defei->SetRange() += 14;                            //设置防御塔的攻击范围

                    defei->SetBulletWidthHeight(defei->GetBulletWidth() + 5, defei->GetBulletHeight() + 5);          //设置子弹宽高
                    break;
                }

            SelButton->SetDisplay(false);      //取消显示新建防御塔框
            DisplayRange = false;           //取消显示自己
            update();
            return;
        }
    }

    //建造塔
    SubbutStr *ASubBut = SelButton->GetSelSubBut();

    for (int i = 0; i < 4; i++)
        if (MouClickRegion(ASubBut[i].SubX, ASubBut[i].SubWidth, ASubBut[i].SubY, ASubBut[i].SubHeight) && SelButton->GetDisplay())
        {
            SelButton->SetDisplay(false);      //取消显示选择框

            //不同防御塔设计暂时还未完全
            switch (i)
            {
            case 0:
                if (DeductionMoney(100)) return;
                TowerparVec.push_back(new towerson1(SelButton->GetX() + 110, SelButton->GetY() + 112, SelButton->GetX() + 95, SelButton->GetY() + 95, 72, 46));
                break;
            case 1:
                if (DeductionMoney(100)) return;
                TowerparVec.push_back(new towerson2(SelButton->GetX() + 110, SelButton->GetY() + 112, SelButton->GetX() + 95, SelButton->GetY() + 95, 72, 46));
                break;
            case 2:
                if (DeductionMoney(100)) return;
                TowerparVec.push_back(new towerson3(SelButton->GetX() + 110, SelButton->GetY() + 112, SelButton->GetX() + 95, SelButton->GetY() + 95, 76, 50));
                break;
            case 3:
                if (DeductionMoney(100)) return;
                TowerparVec.push_back(new towerson4(SelButton->GetX() + 110, SelButton->GetY() + 104, SelButton->GetX() + 95, SelButton->GetY() + 95, 80, 70));
                break;
            default:
                break;
            }

            update();
            return;
        }

    //遍历所有塔坑
    for (auto APit : TowerPitVec)
        //判断点击塔坑
        if (MouClickRegion(APit->GetX(), APit->GetWidth(), APit->GetY(), APit->GetHeight()))
        {
            DisplayRange = false;               //升级选择显示关闭
            for (auto defei : TowerparVec)      //遍历数组判断防御塔坐标和点击坑坐标重合则返回
                if(defei->GetUpLeftX() == APit->GetX() && defei->GetUpLeftY() == APit->GetY())
                {
                    DisplayRangeX = defei->GetUpLeftX(), DisplayRangeY = defei->GetUpLeftY();   //记录要显示攻击范围的防御塔的坐标
                    DisplayRange = true;        //显示防御塔攻击范围
                    return;
                }

            SelButton->CheckTower(APit->GetX(), APit->GetY());  //选中防御塔，选择框显示
            update();

            return;
        }

    DisplayRange = false;           //取消显示防御塔攻击范围
   SelButton->SetDisplay(false);      //取消显示选择框

    update();


}


//析构释放内存
GameWindow::~GameWindow()
{

    for (auto it = TowerPitVec.begin(); it != TowerPitVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }


   delete SelButton;
    SelButton = NULL;


    for (auto it = TowerparVec.begin(); it != TowerparVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }


    for (auto it = MonsterVec.begin(); it != MonsterVec.end(); it++)
    {
        delete *it;
        *it = NULL;
    }

    delete homecoor;
}
