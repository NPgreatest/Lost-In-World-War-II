#include "Client.h"
#include "ui_Client.h"
extern Sql sql;
//BattleWindow::BattleWindow(QWidget  *parent,int Mission) : QMainWindow(parent),ui(new Ui::BattleWindow),Mission(Mission){
Client::Client(QWidget *parent)
 : QMainWindow(parent),ui(new Ui::Client)
{
    ui->setupUi(this);
    GLWidGet_2 *openGL = new GLWidGet_2(this, this);

    openGL->setGeometry(0, 0, 2000, 1000);
    openGL->lower();

    connect(&Timer, &QTimer::timeout, openGL, &GLWidGet_2::animate);
    Timer.start(10);
}

Client::~Client()
{
    delete ui;
}
void Client::paint(QPainter *painter, QPaintEvent *event) {
    int i,k;

    QImage temp(":/Images/Images/BattleGround.png");

    painter->drawImage(QRect(0,0,2000,1000),temp);

    for(i=0;i<sql.GetObject_Num();i++){
        painter->drawImage(sql.GetObjectW(i).MeRect,sql.GetObjectW(i).MeImage);
    }

    for(i=0;i<sql.GetPartical_Num();i++){
        painter->drawImage(sql.GetPartical(i).MeRect,sql.GetPartical(i).MeImage);
    }

    for(i=0;i<sql.GetEnemy_Num();i++){
        painter->drawImage(sql.GetEnemey(i).MeRect,sql.GetEnemey(i).MeImage);
        for(k=0;k<ENEMY_BULLET_NEMBER;k++){
             painter->drawImage(sql.GetEnemey(i).B1Rect[k],sql.GetEnemey(i).B1Image[k]);
        }
    }


}//OpenGl实现
