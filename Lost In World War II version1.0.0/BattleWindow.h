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
    void paint(QPainter *painter, QPaintEvent *event) ;
private slots:
void RainFire();
void Boss_Move();
void Move();
void bulletfly();//让子弹飞
void Player_HitCheck();//玩家碰撞检测
void Bullet_HitCheck();//所有子弹碰撞检测
void Flash();//实现动画
void Flash2();//实现动画
void Enemy_Move();//敌人移动
void Enemy_All();//敌人随机转向及发射子弹
void Enemy_Generate();
//void RedZone_Generate();
void Introduce_Flash();
void P1_Fix();
private:
    int Key;
    int IntroduceP=0;
    int Fix_Mod;



    bool Win=false;

    int Mission=0;//模式
    int LevelA=1;//大关
    int LevelB=1;//小关
    int Map=0;

    int Total_Time=0;
    int Process=0;

    Ui::BattleWindow *ui;
    MainWindow *backto;
    Player P1;
    Enemy *enemy=new Enemy[Edit_Max];
    Object *object[Edit_Max];
    Partical *partical=new Partical[Edit_Max];
    RedZone *redzone=new RedZone[Edit_Min];
    Bar *bar[5];
    Skill myskill;

    Boss1 *boss1=new Boss1;

    QTimer move;
    QTimer fix;
    QTimer Rain;
    QTimer timer;
    QTimer flash;
    QTimer enemymove;
    QTimer enemyall;
    QTimer generate;
    QTimer boom;


    QImage Shot1_Image;
    QImage Shot2_Image;
    QImage Shot3_Image;
    QImage Shot4_Image;

    bool press=false;

    QMediaPlayer *Bullet_Sound = new QMediaPlayer;
    QMediaPlayer RedZone_Sound[Edit_Min];
    QMediaPlayer *BackGroundMusic = new QMediaPlayer;
    QMediaPlayer *MPOut = new QMediaPlayer;
    QMediaPlayer *Bullet_Sound_2= new QMediaPlayer;
    QMediaPlayer RedZone_Pre[Edit_Min];



    HEAD AI1(XY player,XY enemy);


    void MissionTeach();
    void MissionRougueLike();
    void MissionRougueLike_Win();
    void MissionTeach_Win();
    void MissionRougueLike_Continue();
    void MissionTick(int Mission);
    void CreatePartical(XY pos,XY area,Type type);
    void CreateEnemy(XY pos,XY area,int hp,int speed,int bulletspeed,int skin);
    void CreateObject(XY pos,XY area,int type,int skin,int hp);
    void CreateRedZone(XY pos,int R,int type);
    void ClearMap(XY pos);
    void Mist_Generate();
    void MissionTechEnd();
    void Load_Introduce();
    QImage Image_Cut(QImage image);
    QImage Image_Transparent(QImage image,int x);
    void RedZoneBoom(int x);
    void drawIntroduce(QPainter &painter);
    void Play_RedZone(int x);
    void Play_PlayerHit();
    void Play_PlayerHit_2();
    void Play_MPOut();
    void Play_BackMusic();
    void Play_RedZone_Pre(int x);
    void Load_Map(QString Address);


    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *a)Q_DECL_OVERRIDE{CreateRedZone(XY(a->x(),a->y()),200,1);}
};
#endif // BATTLEWINDOW_H
//XY t={a->x(),a->y()};CreateRedZone(t,500,1);qDebug()<<a->pos().x()<<","<<a->pos().y();CreateRedZone(XY(a->x(),a->y()),500,1);
//、、CreateRedZone(XY(a->x(),a->y()),200,1);
