#ifndef CLIENT_H
#define CLIENT_H

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

#include"glwidget_2.h"
#include"mainwindow.h"
#include"Sql.h"
#include"Object.h"
#include"Partical.h"
#include"Enemy.h"
#include"PlayerBullet1.h"
#include"PlayerBullet2.h"
#include"Player.h"
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

private:
    Ui::Client *ui;
    QTimer Timer;

    QUdpSocket* udp_socket;
    qint16 port;
    qint64 last_recv;
    QString get_ip();

    QTimer ParticalTick;

    //粒子
    Partical *partical=new Partical[PARTICAL_NUMBER];//粒子
    //粒子
    //方块
    Object *object[Edit_Min];//方块
    //方块

    //敌人
    Enemy *enemy=new Enemy[Edit_Min];;//敌人
    //敌人

    //子弹
    PlayerBullet1 bullet[Edit_Min];//子弹
    //子弹

    HEAD head;

    Player P1[Edit_Min];//玩家

    Sql sql;

    void Request(int mode);

   //void CreateObject(QRect Rect,int type,int skin,int hp);
    void CreatePartical(QRect const Rect,Type const type);

    int GetEnemyImage(int type,HEAD head);

    int GetPlayerImage(int type,HEAD head,bool slow);

    int MeNumber;

    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void keyReleaseEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

};

#endif // CLIENT_H
