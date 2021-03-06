#ifndef BATTLEWINDOW_H
#define BATTLEWINDOW_H
#include<QPainter>
#include<QMainWindow>
#include<QTimer>
#include<QMediaPlayer>
#include<QTime>
#include<QAction>
#include<QDebug>
#include<QIcon>
#include<QInputDialog>
#include<QEvent>
#include<QKeyEvent>
#include<QMessageBox>
#include<QFile>
#include<QFileDialog>
#include<QRandomGenerator>
#include<cmath>
#include<QList>
#include <QUdpSocket>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QProcessEnvironment>

#include"Player.h"
#include"Object.h"
#include"Enemy.h"
#include"RedZone.h"
#include"All.h"
#include"Partical.h"
#include"Boss1.h"
#include"Bar.h"
#include"Skill.h"
#include"glwidget.h"
#include"Sql.h"
QT_BEGIN_NAMESPACE
namespace Ui { class BattleWindow; }
QT_END_NAMESPACE



class QKeyEvent;
class MainWindow;
class BattleWindow : public QMainWindow
{

    Q_OBJECT

public:

    BattleWindow(QWidget *parent = nullptr,int Mission = 0);

    ~BattleWindow();

    void paint(QPainter *painter, QPaintEvent *event) ;//OpenGl实现



private slots:
void RainFire();//随机生成轰炸区

void Boss_Move();//Boss TImer移动

void Move();//玩家Timer 配合键盘移动

void Bullet_Fly();//所有子弹移动效果(wheel)

void Recive();

void Bullet_HitCheck();//所有子弹碰撞检测

void Flash();//1秒 实现动画

void Flash2();//50毫秒 实现动画

void Enemy_Move();//敌人移动(wheel)

void Enemy_All();//敌人随机转向及发射子弹(wheel)



void Introduce_Flash();//介绍模式

void P1_Weapon();//玩家武器能量槽实现

void Write_Sql();

void on_pushButton_clicked();

private:
    HEAD Key[PLAYER_NUMBER_MAX];//按键

    bool Win=false;//敌人是否清理完毕

    int Mission=0;//模式

    int LevelA=1;//大关

    int LevelB=1;//小关

    int Map=0;//当前地图

    int Total_Time=0;//当前关卡总时间

    int Process=0;//关卡进度

    Ui::BattleWindow *ui;//UI
    MainWindow *backto;//返回主界面

    //玩家
    Player P1[PLAYER_NUMBER_MAX];//玩家
    //玩家

    //敌人
    Enemy *enemy=new Enemy[ENEMY_NUMBER];//敌人
    //敌人

    //方块
    Object *object[OBJECT_NUMBER];//方块
    //方块

    //粒子
    Partical *partical=new Partical[PARTICAL_NUMBER];//粒子
    //粒子

    //轰炸区
    RedZone *redzone=new RedZone[REDZONE_NUMBER];//轰炸区
    //轰炸区

    //Sql

    //Sql

    Bar *bar[8];//槽


    Boss1 *boss1=new Boss1;//1个boss

    QList<QString> AllIP;

    //所有Qtimer
    QTimer move;
    QTimer FinalWeapon;
    QTimer Rain;
    QTimer Timer;
    QTimer One_Sec;
    QTimer EnemyMove;
    QTimer EnemyAll;
    QTimer ParticalTick;
    QTimer UploadData;
    //所有Qtimer


    QPoint Mouse_Point;//鼠标位置



    //bool press=false;

    QMediaPlayer *Bullet_Sound = new QMediaPlayer;
    QMediaPlayer RedZone_Sound[REDZONE_NUMBER];
    QMediaPlayer *BackGroundMusic = new QMediaPlayer;
    QMediaPlayer *MPOut = new QMediaPlayer;
    QMediaPlayer *Bullet_Sound_2= new QMediaPlayer;
    QMediaPlayer RedZone_Pre[REDZONE_NUMBER];

    Sql sql;

    QUdpSocket* udp_socket;
    qint16 port;
    qint64 last_recv;
    QString get_ip();



    void MissionTeach();

    void MissionRougueLike();

    void MissionRougueLike_Win();

    void MissionTeach_Win();

    void MissionRougueLike_Continue();

    void MissionTick();

    void CreatePartical(QRect const Rect,Type const type);

    void CreateEnemy(QRect Rect,int hp,int speed,int bulletspeed,int skin);

    void CreateObject(QRect Rect,int type,int skin,int hp);

    void CreateRedZone(QRect Rect,int R,int type);

    void ClearMap(QRect Rect);

    void Mist_Generate();

    void MissionTechEnd();

    void Load_Introduce();

    void RedZoneBoom(int x);

    void drawIntroduce(QPainter &painter);

    void Play_RedZone(int x);

    void Play_PlayerHit();

    void Play_PlayerHit_2();

    void Play_MPOut();

    void Play_BackMusic();

    void Play_RedZone_Pre(int x);

    void Load_Map(QString Address);

    void Command(QString command);

    void Enemy_Generate();//敌人兵营生成敌人(wheel)

    void Controller(int number,KEYBOARD_CONTROLL key,HEAD head);

    void Player_HitCheck(int x);//玩家碰撞检测

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *a)Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *ev) Q_DECL_OVERRIDE ;

};
#endif // BATTLEWINDOW_H
