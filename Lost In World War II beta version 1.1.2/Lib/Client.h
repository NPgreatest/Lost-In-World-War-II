#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include<QPainter>
#include<QTimer>
#include<QImage>
#include<QRect>
#include<QList>

#include <QUdpSocket>
#include <QHostInfo>
#include <QNetworkInterface>
#include <QProcessEnvironment>

#include"glwidget_2.h"
#include"mainwindow.h"
#include"Sql.h"
#include"Object.h"
#include"Partical.h"
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


    void on_pushButton_clicked();

    void Flash2();

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

    Sql sql;

   //void CreateObject(QRect Rect,int type,int skin,int hp);
    void CreatePartical(QRect const Rect,Type const type);

    //void CreateObject(QRect const Rect,int const type);

};

#endif // CLIENT_H
