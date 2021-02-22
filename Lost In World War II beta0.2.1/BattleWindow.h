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

QT_BEGIN_NAMESPACE
namespace Ui { class BattleWindow; }
QT_END_NAMESPACE
class QKeyEvent;
class MainWindow;
//class RedZone;
class BattleWindow : public QMainWindow
{
    Q_OBJECT
public:
    BattleWindow(QWidget *parent = nullptr);
    ~BattleWindow();
void Load_Status(int Mission);
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
protected:
       void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private:
    int Key;

    int IntroduceP=0;
    int Fix_Mod;
  //  bool Introduce_Music1=false;


    bool Win=false;

    int Mission=0;//模式
    int LevelA=1;//大关
    int LevelB=1;//小关
    int Map=0;

    int Total_Time=0;
    int Process=0;
    int Skill=1;
    QImage RedZone_Image[6];
    QImage Enemy_Image[10][4];
    QImage Bar[5];
    QImage BarC[10];
    QImage Skill_Select[10];

    QRect BarR[10];
    Ui::BattleWindow *ui;
    MainWindow *backto;
    Player P1;
    Enemy *enemy=new Enemy[Edit_Max];
    Object *object[Edit_Max];
    Partical *partical=new Partical[Edit_Max];
    RedZone *redzone=new RedZone[Edit_Min];
    Boss1 *boss1=new Boss1;
    XY boom[Edit_Max];
    QTimer move;
    QTimer fix;
    QTimer Rain;
    bool press=false;

    QMediaPlayer *Bullet_Sound = new QMediaPlayer;
    QMediaPlayer *RedZone_Sound=new QMediaPlayer;
    QMediaPlayer *BackGroundMusic = new QMediaPlayer;
    QMediaPlayer *MPOut = new QMediaPlayer;
    QMediaPlayer *Bullet_Sound_2= new QMediaPlayer;



    HEAD AI1(XY player,XY enemy);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *a){XY t={a->x(),a->y()};CreateRedZone(t,500,1);}
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
    void drawBar(QPainter &painter);
    void Play_RedZone();
    void Play_PlayerHit();
    void Play_PlayerHit_2();
    void Play_MPOut();
    void Play_BackMusic();
    void Load_Map(QString Address);
};
#endif // BATTLEWINDOW_H
