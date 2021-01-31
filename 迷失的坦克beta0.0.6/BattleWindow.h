#ifndef BATTLEWINDOW_H
#define BATTLEWINDOW_H
#include <QPainter>
#include <QMainWindow>
#include <QTimer>
#include<QMediaPlayer>
#include<QTime>
#include<QAction>
#include"Player.h"
#include"Object.h"
#include"Enemy.h"
#include"RedZone.h"
#include"All.h"
#include"Partical.h"
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
void Load_Map(QString Address);
void Load_Status(bool intro,int x);
void Load_Introduce();
QImage Image_Cut(QImage image/*QPixmap qPixmap*/);
QImage Image_Transparent(QImage image,int x);
void RedZoneBoom(int x);
void drawIntroduce(QPainter &painter);
void drawBar(QPainter &painter);
void drawMission1(QPainter &painter);
void Play_RedZone();
void Play_PlayerHit();

private slots:
void Move();
void bulletfly();//让子弹飞
void Player_HitCheck();//玩家碰撞检测
void Bullet_HitCheck();//所有子弹碰撞检测
void Flash();//实现动画
void Flash2();//实现动画
void Enemy_Move();//敌人移动
void Enemy_All();//敌人随机转向及发射子弹
void Enemy_Generate();
void RedZone_Generate();
void Introduce_Flash();
void P1_Fix();
protected:
       void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private:
    int Key;

    int IntroduceP=0;
    int Fix_Mod;
    bool Introduce_Music1=false;
    bool mist=false;//迷雾模式
    bool Win=false;
    int Red_Zone=0;
    int Red_Zone_Fre=5000;
    int Mission=0;
    int Total_Time=0;
    int Process=0;
    QImage Object_Number[20][10];
    QImage RedZone_Image[6];
    QImage Boom_Image[10];
    QImage Enemy_Image[10][4];
    QImage Bar[5];
    QImage BarC[10];
    QImage Dialog[10];
    QRect BarR[10];
    Ui::BattleWindow *ui;
    MainWindow *backto;
    Player P1;
    Enemy *enemy=new Enemy[Edit_Max];
    Object *object=new Object[Edit_Max];
    Partical *partical=new Partical[Edit_Max];
    RedZone *redzone=new RedZone[Edit_Min];
    XY boom[Edit_Max];
    QTimer move;
    QTimer fix;
    bool press=false;
    QMediaPlayer *Bullet_Sound = new QMediaPlayer;
    QMediaPlayer *RedZone_Sound=new QMediaPlayer;
    QMediaPlayer *BackGroundMusic = new QMediaPlayer;
    //QImage

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void Mission1();
    void Mission1_J();
};
#endif // BATTLEWINDOW_H
