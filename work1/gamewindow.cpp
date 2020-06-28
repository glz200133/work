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
#include"failwindow.h"
#include"winwindow.h"
#include <QSound>
#include<QMediaPlayer>
#include<QVector>
#include<vector>
#include<QMultimedia>
//鼠标点击区域宏
#define mouclick(X, Width, Y, Height)     \
(ev->x() >= (X) && ev->x() <= (X) + (Width) &&  \
ev->y() >= (Y) && ev->y() <= (Y) + (Height))
//MouClickRegion

#define Len(X1, Y1, X2, Y2)           \
abs(sqrt((((X1) - (X2)) * ((X1) - (X2))) + (((Y1) - (Y2)) * ((Y1) - (Y2)))))

//用于方便通过格子确定路径点坐标
#define X40(X, Y) ((X) - 1) * 40 + 10, ((Y) - 1) * 40 + 10

//插入怪物  路径点数组名、怪物初始坐标、怪物编号
#define InsterMonster(PathNum, StaCoorNum, MonsterId)     \
MonsterVec.push_back (new monster(pointarr[PathNum], PathLength[PathNum], X40(staco[StaCoorNum].x, staco[StaCoorNum].y), MonsterId));




using namespace std;



GameWindow::GameWindow(int lv): LevelNumber(lv)
{


     if(LevelNumber==0)
     {
      player.setMedia(QUrl("qrc:/music1.mp3"));
      player.setVolume(100);
      player.play();
     }
    else if(LevelNumber==1)
         {
          player.setMedia(QUrl("qrc:/music2.mp3"));
          player.setVolume(100);
          player.play();
         }
     else if(LevelNumber==2)
     {
      player.setMedia(QUrl("qrc:/music3.mp3"));
      player.setVolume(100);
      player.play();
     }


setFixedSize(1040, 640);


setWindowTitle("游戏界面");

//显示的按钮
QPushButton* disranpush = new QPushButton(this);
disranpush->setStyleSheet("color:white");
disranpush->setGeometry(900, 0, 150, 45);
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





QTimer* timer2 = new QTimer(this);      //用于插入怪物定时器，开始时间
timer2->start(2000);
timer2->setInterval(2000);

connect(timer2,&QTimer::timeout,[=]()
{
    //根据关卡编号确定执行怪物的路径方案
    switch (LevelNumber)
    {
    case 0:
    {
        //设置路径点
        CoorStr* Waypointarr1[] = {new CoorStr(X40(20, 5)),new CoorStr(X40(20, 3)),new CoorStr(X40(15, 3)),
                                   new CoorStr(X40(15, 5)),  new CoorStr(X40(11, 5)),new CoorStr(X40(11, 6)),
                                   new CoorStr(X40(9, 6)),new CoorStr(X40(9, 10)),new CoorStr(X40(4, 10)),
                                   new CoorStr(X40(4, 8)),
                                     new CoorStr(homecoor->x, homecoor->y)};
        CoorStr* Waypointarr2[] = {new CoorStr(X40(24, 9)),new CoorStr(X40(24, 10)), new CoorStr(X40(22, 10)),
                                   new CoorStr(X40(20, 13)),new CoorStr(X40(20, 12)),new CoorStr(X40(18, 12)),
                                   new CoorStr(X40(18, 10)),new CoorStr(X40(14, 10)),new CoorStr(X40(14, 6)),
                                   new CoorStr(X40(9, 6)), new CoorStr(X40(9, 10)), new CoorStr(X40(4, 10)),
                                   new CoorStr(X40(4, 8)),new CoorStr(X40(0, 8)),
                                   new CoorStr(homecoor->x, homecoor->y)};
        //怪物的四个起始点
        CoorStr staco[] = {CoorStr(26, 5), CoorStr(26, 9), CoorStr(26, 4), CoorStr(26, 9)};//26.5

        //每条路径的结点个数
        int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

        IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength);   //使用预设的两条路产生怪物方案

        break;
    }
    case 1:
    {
        //设置路径点,即怪物在路径点处转向
        CoorStr* Waypointarr1[] = {new CoorStr(X40(3, 6)), new CoorStr(X40(3, 8)), new CoorStr(X40(5, 8)),
                                   new CoorStr(X40(5, 9)), new CoorStr(X40(9, 9)), new CoorStr(X40(9, 8)),
                                   new CoorStr(X40(17, 8)), new CoorStr(X40(17, 11)),new CoorStr(X40(21, 11)),
                                   new CoorStr(X40(21, 3)),new CoorStr(X40(19, 3)),

                                   new CoorStr(homecoor->x, homecoor->y)};
        CoorStr* Waypointarr2[] = {new CoorStr(X40(7, 13)), new CoorStr(X40(12, 13)), new CoorStr(X40(12,12)),
                                   new CoorStr(X40(14, 12)), new CoorStr(X40(14, 11)),
                                   new CoorStr(X40(21, 3)),new CoorStr(X40(19, 3)),

                                   new CoorStr(homecoor->x, homecoor->y)};

                                  //怪物的四个起始点
        CoorStr staco[] = {CoorStr(0, 6), CoorStr(7, 16), CoorStr(0, 5), CoorStr(7, 15)};

        //每条路径的结点个数
        int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

        IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength);   //使用预设的两条路产生怪物方案
        break;
    }

    case 2:
    {
        //设置路径点
        CoorStr* Waypointarr1[] = {new CoorStr(X40(23, 8)), new CoorStr(X40(23, 5)), new CoorStr(X40(18, 5)),
                                   new CoorStr(X40(18, 6)),
                                   new CoorStr(X40(9, 6)),new CoorStr(X40(9, 10)),


                                   new CoorStr(homecoor->x, homecoor->y)};
        CoorStr* Waypointarr2[] = {new CoorStr(X40(23, 12)), new CoorStr(X40(9, 12)),new CoorStr(X40(9, 10)),
                                   new CoorStr(X40(0, 10)), new CoorStr(homecoor->x, homecoor->y)};

        //怪物的四个起始点
        CoorStr staco[] = {CoorStr(26, 8), CoorStr(26, 13), CoorStr(26, 7), CoorStr(26, 13)};


        int PathLength[] = {sizeof(Waypointarr1)/sizeof(CoorStr*), sizeof(Waypointarr1)/sizeof(CoorStr*)};

        IrodMonsProgDefa(Waypointarr1, Waypointarr2, staco, PathLength);   //使用预设的两条路的产生怪物方案
        break;
    }
    }
});


//显示金钱

moneylable->setGeometry(0,0,400, 120);       //位置
moneylable->setFont(QFont("Microsoft YaHei", 24));             //设置字体
moneylable->setText(QString("money：%1").arg(money));    //显示金钱信息

//生命值标签
QLabel *lifelable = new QLabel(this);
lifelable->setGeometry(0, 0, 220, 40);   //设置控件位置和大小
lifelable->setFont(QFont("Microsoft YaHei", 24));
lifelable->setText(QString("life：%1").arg(life));


    QTimer* timer = new QTimer(this);
    timer->start(120);
    timer->setInterval(100);//刷新时间
    connect(timer,&QTimer::timeout,[=]()
    {

        //防御塔寻找目标怪物的规律：找到最后一个怪物作为目标，目标丢失后找再继续找最后一个目标
        for (auto tower :TowerparVec)      //遍历防御塔
        {
            if (!tower-> GetAimsMonster())   //寻找目标怪物
            {
                for(int i = MonsterVec.size() - 1; i >= 0; i--)

                    if (Len(tower->GetUpLeftX() + 40, tower->GetUpLeftY() + 40,
                        MonsterVec.at(i)->GetX() + (MonsterVec.at(i)->GetWidth() >> 1),
                        MonsterVec.at(i)->GetY() + (MonsterVec.at(i)->GetHeight() >> 1)) <= tower->GetRange())
                    {
                        tower->SetAimsMonster(MonsterVec.at(i));    //设置防御塔的目标怪物
                        break;
                    }
            }
            else                //当前防御塔拥有目标且怪物在防御塔范围之内时时攻击怪物
                if (Len(tower->GetUpLeftX() + 40, tower->GetUpLeftY() + 40,
                    tower-> GetAimsMonster()->GetX() + (tower->GetAimsMonster()->GetWidth() >> 1),
                    tower-> GetAimsMonster()->GetY() + (tower->GetAimsMonster()->GetHeight() >> 1)) <= tower->GetRange())
                {

                     tower->InterBullet();           //拥有目标时一直创建子弹
                }


            if (tower->GetAimsMonster())    //目标怪物不为空
                if (Len(tower->GetUpLeftX() + 40, tower->GetUpLeftY() + 40,
                    tower -> GetAimsMonster() -> GetX() + (tower -> GetAimsMonster() -> GetWidth() >> 1),
                    tower ->GetAimsMonster() -> GetY() + (tower->GetAimsMonster()->GetHeight() >> 1)) > tower->GetRange())
                        tower->SetAimsMonster(NULL);     //超过距离将目标怪物设为空
        }
        //子弹移动
        for (auto tower1 : TowerparVec)
            tower1->BulletMove();


        for (auto Mons = MonsterVec.begin(); Mons != MonsterVec.end(); Mons++)
            if((*Mons)->Move()) //怪物走到终点
            {
                delete *Mons;
                MonsterVec.erase(Mons);

                life--;
                lifelable->setText(QString("生命：%1").arg(life));

                if (life == 0)
                {
                    this->close();
                    failwindow*fail=new failwindow;//打开失败界面
                    fail->show();
                    player.stop();

                }
               else if(life<0)
                   { this->close();
                player.stop();}
                //生命值为0时关闭该窗口，弹出一个新窗口

                break;
            }

        //判断子弹击中怪物
        for (auto tower2 : TowerparVec)
        {
            auto &tbullvec = tower2->GetBulletVec();//遍历子弹
            for (auto bullit = tbullvec.begin(); bullit != tbullvec.end(); bullit++)
                for (auto monst = MonsterVec.begin(); monst != MonsterVec.end(); monst++)

                    if ((*bullit)->GetX() + (tower2->GetBulletWidth() >> 1) >= (*monst)->GetX() && (*bullit)->GetX() <= (*monst)->GetX() + (*monst)->GetWidth() &&
                        (*bullit)->GetY() + (tower2->GetBulletHeight() >> 1) >= (*monst)->GetY() && (*bullit)->GetY() <= (*monst)->GetY() + (*monst)->GetHeight())
                    {
                        tbullvec.erase(bullit);

                        (*monst)->SetHealth((*monst)->GetHealth() - tower2->GetAttack());      //敌人血量 = 本身血量减去 当前炮塔攻击力



                        if ((*monst)->GetHealth() <= 0) //生命值为空时
                        {
                            //判断一下其他防御塔的目标怪物是否和当前防御塔消灭的怪物重复，如果重复，则将那一个防御塔的目标怪物也设为空
                            for (auto tower3 : TowerparVec)
                                if (tower3->GetAimsMonster() == *monst)
                                    tower3->SetAimsMonster(NULL);
                            for (auto tower3 : StillVec)
                                if (tower3->GetAimsMonster() == *monst)
                                    tower3->SetAimsMonster(NULL);
                            MonsterVec.erase(monst);
                            money += 30;
                            moneylable->setText(QString("money：%1").arg(money));
                        }


                        goto L1;
                    }
            L1:;
        }



        update();   //绘图


//重制版

        for (auto tower :StillVec)      //遍历防御塔
        {
            if (!tower-> GetAimsMonster())   //寻找目标怪物
            {
                for(int i = MonsterVec.size() - 1; i >= 0; i--)

                    if (Len(tower->GetUpLeftX() + 40, tower->GetUpLeftY() + 40,
                        MonsterVec.at(i)->GetX() + (MonsterVec.at(i)->GetWidth() >> 1),
                        MonsterVec.at(i)->GetY() + (MonsterVec.at(i)->GetHeight() >> 1)) <= tower->GetRange())
                    {
                        tower->SetAimsMonster(MonsterVec.at(i));    //设置防御塔的目标怪物
                        break;
                    }
            }
            else                //当前防御塔拥有目标且怪物在防御塔范围之内时时攻击怪物
                if (Len(tower->GetUpLeftX() + 40, tower->GetUpLeftY() + 40,
                    tower-> GetAimsMonster()->GetX() + (tower->GetAimsMonster()->GetWidth() >> 1),
                    tower-> GetAimsMonster()->GetY() + (tower->GetAimsMonster()->GetHeight() >> 1)) <= tower->GetRange())
                {

                     tower->InterBullet();           //拥有目标时一直创建子弹
                }


            if (tower->GetAimsMonster())    //目标怪物不为空
                if (Len(tower->GetUpLeftX() + 40, tower->GetUpLeftY() + 40,
                    tower -> GetAimsMonster() -> GetX() + (tower -> GetAimsMonster() -> GetWidth() >> 1),
                    tower ->GetAimsMonster() -> GetY() + (tower->GetAimsMonster()->GetHeight() >> 1)) > tower->GetRange())
                        tower->SetAimsMonster(NULL);     //超过距离将目标怪物设为空
        }
        //子弹移动
        for (auto tower1 : StillVec)
            tower1->BulletMove();


        for (auto Mons = MonsterVec.begin(); Mons != MonsterVec.end(); Mons++)
            if((*Mons)->Move()) //怪物走到终点
            {
                delete *Mons;
                MonsterVec.erase(Mons);

                life--;
                lifelable->setText(QString("生命：%1").arg(life));

                if (life == 0)
                {
                    this->close();
                    failwindow*fail=new failwindow;//打开失败界面
                    fail->show();
                    player.stop();

                }
               else if(life<0)
                   { this->close();
                player.stop();}
                //生命值为0时关闭该窗口，弹出一个新窗口

                break;
            }

        //判断子弹击中怪物
        for (auto tower2 : StillVec)
        {
            auto &tbullvec = tower2->GetBulletVec();//遍历子弹
            for (auto bullet = tbullvec.begin(); bullet != tbullvec.end(); bullet++)
                for (auto monst = MonsterVec.begin(); monst != MonsterVec.end(); monst++)

                    if ((*bullet)->GetX() + (tower2->GetBulletWidth() >> 1) >= (*monst)->GetX() && (*bullet)->GetX() <= (*monst)->GetX() + (*monst)->GetWidth() &&
                        (*bullet)->GetY() + (tower2->GetBulletHeight() >> 1) >= (*monst)->GetY() && (*bullet)->GetY() <= (*monst)->GetY() + (*monst)->GetHeight())
                    {
                        tbullvec.erase(bullet);

                        (*monst)->SetHealth((*monst)->GetHealth() - tower2->GetAttack());      //敌人血量 = 本身血量减去 当前炮塔攻击力
                         (*monst)->SetSpeed( (*monst)->GetSpeed()-5);


                        if ((*monst)->GetHealth() <= 0) //生命值为空时
                        {
                            //判断一下其他防御塔的目标怪物是否和当前防御塔消灭的怪物重复，如果重复，则将那一个防御塔的目标怪物也设为空
                            for (auto tower3 : StillVec)
                                if (tower3->GetAimsMonster() == *monst)
                                    tower3->SetAimsMonster(NULL);
                            for (auto tower3 : TowerparVec)
                                if (tower3->GetAimsMonster() == *monst)
                                    tower3->SetAimsMonster(NULL);

                            MonsterVec.erase(monst);
                            money += 30;
                            moneylable->setText(QString("money：%1").arg(money));
                        }


                        goto L2;

                    }

            L2:;
            //删除越界子弹

        }



        update();   //绘图


    });//zhongzhi
}
inline bool GameWindow::DeductionMoney(int money)
{
    if (this->money - money < 0) return true;
    this->money -= money; //扣除金钱
    moneylable->setText(QString("money：%1").arg(this->money));
    return false;
}

//预设的两条路产生怪物方案
void GameWindow::IrodMonsProgDefa(CoorStr** Waypointarr1, CoorStr** Waypointarr2, CoorStr* staco, int* PathLength)
{
    /*两条路径*/
   CoorStr** pointarr[] = {Waypointarr1, Waypointarr2};

    //插入怪物
    if(counter >= 1 && counter <= 10)
    {
        InsterMonster(0, 0, 1);

        //第几条路径、第几个起始点、怪物编号
    }
    else if(counter > 10 && counter <= 23)
    {
        InsterMonster(0, 2, 2);
    }
    else if(counter > 23 && counter <= 35)
    {

        InsterMonster(0, 2, 3);
        InsterMonster(1, 1, 2);
    }
    else if (counter > 35 && counter <= 47)
    {
        InsterMonster(0, 0, 3);
        InsterMonster(1, 1, 3);

    }
    else if (counter > 47 && counter <= 58)
    {
        InsterMonster(0, 2, 4);

        InsterMonster(1, 1, 1);
    }
    if(counter > 58 && counter <= 65)
    {

        InsterMonster(0, 2, 4);
        InsterMonster(1, 1, 3);
    }
    if (counter > 65 && counter <= 76)
    {

        InsterMonster(0, 0, 5);
        InsterMonster(1, 1, 4);
    }

    if (counter > 76 && MonsterVec.empty())

    {
        this->close();
        winwindow*win=new winwindow;
        win->show();
            player.stop();
    }
     else if(counter> 85)
    {
        this->close();
        winwindow*win=new winwindow;
        win->show();
            player.stop();
    }

    counter++;
    update();
}

//根据数组画出地图函数

void GameWindow::DrawMapArr(QPainter& painter)
{
    //diyiguan1
    int Map_1[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 0, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 0, 3, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        5, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 3, 0, 0, 1, 1, 1, 1,
        0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
        0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 1, 1, 1, 1, 1, 0, 3, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    //第二关
    int Map_2[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 5, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 3, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        1, 1, 1, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0,
        0, 0, 0, 0, 3, 0, 1, 1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    int Map_3[16][26] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 3, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 0, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        5, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
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


            case 3:
                painter.drawPixmap(i * 40, j * 40, 80, 80,
                   QPixmap(":/floor9.png"));

                TowerspotVec.push_back(new Towerspot(i * 40, j * 40));
                break;
            case 5:

                homecoor->x = i * 40, homecoor->y = j * 40;
                break;
            }
        }

    painter.drawPixmap(homecoor->x, homecoor->y, 80, 80,
        QPixmap(":/treasure.png"));//家


}
void GameWindow::DrawDefenseTower(QPainter& painter)
{
    //画出防御塔
    for (auto tower4 : TowerparVec)  //遍历防御塔数组
    {
        //画出底座
        painter.drawPixmap(tower4->GetUpLeftX(), tower4->GetUpLeftY(), 80, 80, QPixmap(tower4->GetBaseImg()));

        //画出所有防御塔的攻击范围
        if(DisplayAllRange)
            painter.drawEllipse(QPoint(tower4->GetUpLeftX() + 40, tower4->GetUpLeftY() + 40), tower4->GetRange(),tower4->GetRange());

        //画出所有防御塔子弹
        for (auto bulli : tower4->GetBulletVec())
            painter.drawPixmap(bulli->coor.x, bulli->coor.y, tower4->GetBulletWidth(), tower4->GetBulletHeight(),QPixmap(tower4->GetBulletPath()));


        painter.drawPixmap(tower4->GetX(), tower4->GetY(), tower4->GetWidth(), tower4->GetHeight(), QPixmap(tower4->GetDefImg()));

        painter.resetTransform();   //重置调整
    }

    for (auto tower4 : StillVec)  //遍历防御塔数组
    {
        //画出底座
        painter.drawPixmap(tower4->GetUpLeftX(), tower4->GetUpLeftY(), 80, 80, QPixmap(tower4->GetBaseImg()));

        //画出所有防御塔的攻击范围
        if(DisplayAllRange)
            painter.drawEllipse(QPoint(tower4->GetUpLeftX() + 40, tower4->GetUpLeftY() + 40), tower4->GetRange(),tower4->GetRange());

        //画出所有防御塔子弹
        for (auto bulli : tower4->GetBulletVec())
            painter.drawPixmap(bulli->coor.x, bulli->coor.y, tower4->GetBulletWidth(), tower4->GetBulletHeight(),QPixmap(tower4->GetBulletPath()));


        painter.drawPixmap(tower4->GetX(), tower4->GetY(), tower4->GetWidth(), tower4->GetHeight(), QPixmap(tower4->GetDefImg()));

        painter.resetTransform();   //重置调整
    }


}
//画出选择框
void GameWindow::DrawSelectionBox(QPainter& painter)
{

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




//画出怪物
void GameWindow::DrawMonster(QPainter& painter)
{
    for (auto moni : MonsterVec)//画出怪物
       { painter.drawPixmap(moni->GetX(), moni->GetY(), moni->GetWidth(), moni->GetHeight(), QPixmap(moni->GetImgPath()));
    QPoint healthBarPoint = QPoint(moni->GetX(), moni->GetY()) + QPoint(1, 0);
    // 绘制血条
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(60, 2));
    painter.drawRect(healthBarBackRect);

    painter.setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize(6* moni->GetHealth()/31, 2));
    painter.drawRect(healthBarRect);
}
}

//画防御塔攻击范围
void GameWindow::DrawRangeAndUpgrade(QPainter& painter)
{

    for (auto tower5 : TowerparVec)
        if(tower5->GetUpLeftX() == DisplayRangeX && tower5->GetUpLeftY() == DisplayRangeY && DisplayRange)
        {
            painter.setPen(QPen(Qt::white));
            painter.drawEllipse(QPoint(DisplayRangeX + 40, DisplayRangeY + 40), tower5->GetRange(), tower5->GetRange());
            painter.drawPixmap(DisplayRangeX + 10, DisplayRangeY - 80, 60, 60, QPixmap(":/rankup.png"));
            painter.drawPixmap(DisplayRangeX +10, DisplayRangeY + 120, 60, 60, QPixmap(":/delete1.png"));
        }
    //重制版
    for (auto tower5 : StillVec)
        if(tower5->GetUpLeftX() == DisplayRangeX && tower5->GetUpLeftY() == DisplayRangeY && DisplayRange)
        {
            painter.setPen(QPen(Qt::white));
            painter.drawEllipse(QPoint(DisplayRangeX + 40, DisplayRangeY + 40), tower5->GetRange(), tower5->GetRange());
            painter.drawPixmap(DisplayRangeX + 10, DisplayRangeY - 80, 60, 60, QPixmap(":/rankup.png"));
            painter.drawPixmap(DisplayRangeX +10, DisplayRangeY + 120, 60, 60, QPixmap(":/delete1.png"));
        }


}


//绘图事件
void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);     //创建画家类
    if(LevelNumber==0)    //画每一关地图
        painter.drawPixmap(0,0,QPixmap (":/map1.jpg"));
    else if(LevelNumber==1)
        painter.drawPixmap(0,0,QPixmap (":/map2.jpg"));
    else if(LevelNumber==2)
        painter.drawPixmap(0,0,QPixmap (":/map3.jpg"));

    painter.setRenderHint(QPainter::Antialiasing);    //设置抗锯齿

    DrawMapArr(painter);        //画出地图

    DrawDefenseTower(painter);  //画出防御塔和子弹

    DrawMonster(painter);       //画出怪物

    DrawRangeAndUpgrade(painter);//画出攻击范围和升级按钮

    DrawSelectionBox(painter);  //画出选择框


}

//鼠标点击事件,重点项目
void GameWindow::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() != Qt::LeftButton)
        return;


//升级

    if (DisplayRange)
    {
        if (mouclick(DisplayRangeX + 10, 60 , DisplayRangeY - 80, 60))
        {
            //设置防御塔宽高，攻击力，微调坐标
            for (auto tower6 : TowerparVec)
                if (tower6->GetUpLeftX() == DisplayRangeX && tower6->GetUpLeftY() == DisplayRangeY && DisplayRange)
                {
                    if (DeductionMoney(200)) return;

                    tower6->SetAttack(tower6->GetAttack() + 20);
                    tower6->SetWidthHeight(tower6->GetWidth() + 12, tower6->GetHeight() + 6);
                   tower6->SetXY(tower6->GetX() - 6, tower6->GetY() - 3); //调整防御塔坐标
                    //defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                   tower6->SetRange() += 14;                            //设置防御塔的攻击范围


                    break;
                }
            //重制版
            for (auto tower6 : StillVec)
                if (tower6->GetUpLeftX() == DisplayRangeX && tower6->GetUpLeftY() == DisplayRangeY && DisplayRange)
                {
                    if (DeductionMoney(200)) return;

                    tower6->SetAttack(tower6->GetAttack() + 20);
                    tower6->SetWidthHeight(tower6->GetWidth() + 12, tower6->GetHeight() + 6);
                   tower6->SetXY(tower6->GetX() - 6, tower6->GetY() - 3); //调整防御塔坐标
                    //defei->SetAimsMonster(NULL);                        //将防御塔目标设为空
                   tower6->SetRange() += 14;                            //设置防御塔的攻击范围


                    break;
                }
            SelButton->SetDisplay(false);
            DisplayRange = false;           //取消显示自己
            update();
            return;
        }
    }





    //建造塔
    SubbutStr *ASubBut = SelButton->GetSelSubBut();

    for (int i = 0; i < 4; i++)
        if (mouclick(ASubBut[i].SubX, ASubBut[i].SubWidth, ASubBut[i].SubY, ASubBut[i].SubHeight) && SelButton->GetDisplay())
        {
            SelButton->SetDisplay(false);      //取消显示选择框


            switch (i)
            {
            case 0:
                if (DeductionMoney(100)) return;
                TowerparVec.push_back(new towerson1(SelButton->GetX() + 100, SelButton->GetY() + 112, SelButton->GetX() + 95, SelButton->GetY() + 95, 72, 46));
                break;
            case 1:
                if (DeductionMoney(150)) return;
                TowerparVec.push_back(new towerson2(SelButton->GetX() + 100, SelButton->GetY() + 112, SelButton->GetX() + 95, SelButton->GetY() + 95, 72, 46));
                break;
            case 2:
                if (DeductionMoney(300)) return;
               TowerparVec.push_back(new towerson3(SelButton->GetX() + 100, SelButton->GetY() + 112, SelButton->GetX() + 95, SelButton->GetY() + 95, 76, 50));
                break;
            case 3:
                if (DeductionMoney(350)) return;
                //修改版
               StillVec.push_back(new towerson4(SelButton->GetX() + 100, SelButton->GetY() + 104, SelButton->GetX() + 95, SelButton->GetY() + 95, 80, 70));
                break;
            default:
                break;
            }

            update();
            return;
        }

    //遍历所有塔坑
    for (auto APit : TowerspotVec)
        //判断点击塔坑
        if (mouclick(APit->GetX(), APit->GetWidth(), APit->GetY(), APit->GetHeight()))
        {
            DisplayRange = false;               //升级选择显示关闭
            for (auto tower7 : TowerparVec)      //遍历数组判断防御塔坐标和点击坑坐标重合则返回
                if(tower7->GetUpLeftX() == APit->GetX() && tower7->GetUpLeftY() == APit->GetY())
                {
                    DisplayRangeX = tower7->GetUpLeftX(), DisplayRangeY = tower7->GetUpLeftY();   //记录要显示攻击范围的防御塔的坐标
                    DisplayRange = true;        //显示防御塔攻击范围
                    return;
                }
//复制版
            for (auto tower7 : StillVec)      //遍历数组判断防御塔坐标和点击坑坐标重合则返回
                if(tower7->GetUpLeftX() == APit->GetX() && tower7->GetUpLeftY() == APit->GetY())
                {
                    DisplayRangeX = tower7->GetUpLeftX(), DisplayRangeY = tower7->GetUpLeftY();   //记录要显示攻击范围的防御塔的坐标
                    DisplayRange = true;        //显示防御塔攻击范围
                    return;
                }
            SelButton->CheckTower(APit->GetX(), APit->GetY());  //选中防御塔，选择框显示
            update();

            return;
        }




    //拆塔
    if (DisplayRange)
    {
        if (mouclick(DisplayRangeX + 10, 60 , DisplayRangeY +120, 60))
        {


         for( auto tower8 = TowerparVec.begin(); tower8 != TowerparVec.end(); tower8++)
                if ((*tower8)->GetUpLeftX() == DisplayRangeX && (*tower8)->GetUpLeftY() == DisplayRangeY && DisplayRange)
                {
                    delete (*tower8);
                    TowerparVec.erase(tower8);
                    break;
                }
         //重制版
         for( auto tower8 = StillVec.begin(); tower8 != StillVec.end(); tower8++)
                if ((*tower8)->GetUpLeftX() == DisplayRangeX && (*tower8)->GetUpLeftY() == DisplayRangeY && DisplayRange)
                {
                    delete (*tower8);
                    StillVec.erase(tower8);
                    break;
                }

            SelButton->SetDisplay(false);
            DisplayRange = false;           //取消显示自己
            update();
            return;
        }
    }
    DisplayRange = false;
   SelButton->SetDisplay(false);
    update();


}


//析构释放内存
GameWindow::~GameWindow()
{

    for (auto it = TowerspotVec.begin(); it != TowerspotVec.end(); it++)
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
    for (auto it = StillVec.begin(); it != StillVec.end(); it++)
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
