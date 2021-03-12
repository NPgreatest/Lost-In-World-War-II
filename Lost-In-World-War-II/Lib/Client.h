#ifndef CLIENT_H
#define CLIENT_H
#include <QIcon>
#include <QWidget>
#include<QPainter>
#include<QTimer>
#include<QImage>
#include<QRect>
#include<QList>
#include<QEvent>
#include<QKeyEvent>
#include <QUdpSocket>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QProcessEnvironment>
#include <QVector>
#include"glwidget_2.h"
#include"mainwindow.h"
#include"Object.h"
#include"Partical.h"
#include"Enemy.h"
#include"PlayerBullet1.h"
#include"PlayerBullet2.h"
#include"Bar.h"
#include"Player.h"
#include"Button.h"
#include<QTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class Client;
}
QT_END_NAMESPACE
class MainWindow;
class Client : public QMainWindow
{
    Q_OBJECT

public:

    Client(QWidget *parent = nullptr);
    ~Client();
    void paint(QPainter *painter, QPaintEvent *event) ;//OpenGl实现

private slots:

    void Recive();

    void Flash2();

    void on_pushButton_clicked();

    void Bullet_Fly();

    void on_pushButton_2_clicked();

private:
    Ui::Client *ui;
    MainWindow *mainwindow;
    QUdpSocket* udp_socket;
    qint16 port;
    qint64 last_recv;
    QString get_ip();


    QTimer Timer;
    QTimer Checker;
    QTimer ParticalTick;

    QPoint Mouse_Point;

    Bar *bar[3];//槽

    //粒子
    Partical *partical=new Partical[PARTICAL_NUMBER];//粒子
    //粒子
    //方块
    Object *object[200];//方块
    //方块

    //敌人
    Enemy *enemy=new Enemy[Edit_Min];;//敌人
    //敌人

    //子弹
    PlayerBullet1 bullet1[PLAYER_B1_NUMBER];//子弹
    //子弹
    QRect bulletr[PLAYER_B1_NUMBER];//子弹坐标临时数据

    //子弹
    PlayerBullet2 bullet2[PLAYER_B1_NUMBER];//子弹
    //子弹
    QRect bulletr2[PLAYER_B1_NUMBER];//子弹坐标临时数据


    HEAD head;

    Player P1[Edit_Min];//玩家

    QVector<Object_Sql> Object_S;
    QVector<Enemy_Sql> Enemy_S;
    QVector<Player_Sql> Player_S;

    void Request(int mode);

   //void CreateObject(QRect Rect,int type,int skin,int hp);
    void CreatePartical(QRect const Rect,Type const type);

    int GetEnemyImage(int type,HEAD head);

    void CreateBullet(QRect const MeRect,HEAD const h,int const type,int const Damage,Target target,int master,int Speed);

    void CorrectBullet(int number,QRect Rect,bool Alive=true);

    void CreateBullet2(QRect const MeRect,
                       double const Drection,
                       int const type,
                       int const Damage,
                       Target const target,
                       int const master,
                       int const speed,
                       int const HP);

    int GetPlayerImage(int type,HEAD head,bool slow);

    int MeNumber=-1;

        QImage exit;

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

    int GetObjectImage(int const type,int const Status) {return ((type-1)*10)+Status+1;}
    void mousePressEvent(QMouseEvent *a) Q_DECL_OVERRIDE ;
    void mouseMoveEvent(QMouseEvent *ev) Q_DECL_OVERRIDE ;
};

#endif // CLIENT_H
