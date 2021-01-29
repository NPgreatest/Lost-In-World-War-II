#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include <QEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include<QDebug>
#include<QFile>
#include<QFileDialog>
#include<QRandomGenerator>
#include <QIcon>
#include <QInputDialog>
#include<QMediaPlayer>
#include<QSound>
#include"mainwindow.h"
void BattleWindow::Introduce_Flash(){
    IntroduceP++;
    if(IntroduceP==1){
        QMediaPlayer *player1 = new QMediaPlayer;
        QString path="D:/back.mp3";
            player1->setVolume(50);
        player1->setMedia(QUrl::fromLocalFile(path));
        player1->play();
        P1.Strengthen(9999,0,0,0,0,5);
    }
    if(IntroduceP==80){
        QTimer *timer = new QTimer(this);
        QTimer *flash = new QTimer(this);
        QTimer *enemymove = new QTimer(this);
        QTimer *enemyall = new QTimer(this);
        QTimer *generate = new QTimer(this);
        QTimer *boom = new QTimer(this);
        QTimer *redzone=new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(update()));
        connect(timer, SIGNAL(timeout()), this, SLOT(bulletfly()));
        connect(flash, SIGNAL(timeout()), this, SLOT(Flash()));
     //   connect(move, SIGNAL(timeout()), this, SLOT(Move()));
        connect(enemymove, SIGNAL(timeout()), this, SLOT(Enemy_Move()));
        connect(enemyall, SIGNAL(timeout()), this, SLOT(Enemy_All()));
        connect(generate, SIGNAL(timeout()), this, SLOT(Enemy_Generate()));
        connect(boom, SIGNAL(timeout()), this, SLOT(Flash2()));
        connect(redzone, SIGNAL(timeout()), this, SLOT(RedZone_Generate()));
        redzone->start(500);
        timer->start(10);
        flash->start(1000);
        enemymove->start(50);
        enemyall->start(100);
        generate->start(5000);
        boom->start(50);
    }

    if(IntroduceP==120){
        QMediaPlayer *player2 = new QMediaPlayer;
        QString path="D:/introduce.wav";
        player2->setMedia(QUrl::fromLocalFile(path));
        player2->setVolume(50);
        player2->play();
    }
    if(IntroduceP==200){
        QMediaPlayer *player3 = new QMediaPlayer;
        QString path="D:/police.mp3";
        player3->setMedia(QUrl::fromLocalFile(path));
        player3->setVolume(100);
        player3->play();
    }
            if(IntroduceP>=120&&IntroduceP<250){
                P1.Player_ChangeHead(3);
                move.start(10);
                        P1.Player_B1Fire();
            }
            if(IntroduceP>=250&&IntroduceP<300){

                P1.Player_ChangeHead(1);
                move.start(10);
                P1.Player_B1Fire();
            }
            if(IntroduceP>=300&&IntroduceP<400){

                P1.Player_ChangeHead(3);
                move.start(10);
                P1.Player_B1Fire();
            }
            if(IntroduceP>=400){
                backto=new MainWindow;
                backto->show();
                this->~BattleWindow();

            }

}
void BattleWindow::Load_Introduce(){
    Load_Map(":/maps/maps/Introduce.txt");
    Red_Zone=100;
    Red_Zone_Fre=1000;
  //  delete ui->Bar;
  //  delete ui->showhp;
    Introduce_Flash();
//QTimer::singleShot(2000, this, SLOT());
    QTimer *in=new QTimer(this);
        connect(in, SIGNAL(timeout()), this, SLOT(Introduce_Flash()));
        in->start(50);
}


void BattleWindow::drawIntroduce(QPainter &painter){
    QImage school("://images/school.png");
    QImage school2;
    QImage name1("://images/name1.png");
    QImage name12;
    QImage name2("://images/name2.png");
    QImage name22;
    QImage fill("://images/fill.jpg");
    QImage title_image("://images/title.png");
    fill=Image_Transparent(fill,200);
    title_image=Image_Cut(title_image);
    QRect school_rect(500,200,550,113);
    QRect name_rect(500,500,583,332);
    QRect tital(0,400,1600,200);
    QRect title(0,400,1600,200);
    if(IntroduceP>0&&IntroduceP<120)
    painter.fillRect(0,0,1600,1000,QColor(Qt::black));
    if(IntroduceP>20&&IntroduceP<40){
        school2=Image_Transparent(school,(IntroduceP-20)*12);
        name12=Image_Transparent(name1,(IntroduceP-20)*12);
        painter.drawImage(school_rect,school2);
        painter.drawImage(name_rect,name12);
    }
    if(IntroduceP>=40&&IntroduceP<60){
        school2=Image_Transparent(school,255);
        name12=Image_Transparent(name1,255);
        painter.drawImage(school_rect,school2);
        painter.drawImage(name_rect,name12);
    }
    if(IntroduceP>=60&&IntroduceP<80){
        school2=Image_Transparent(school,255);
        name12=Image_Transparent(name1,255-13*(IntroduceP-60));
        painter.drawImage(school_rect,school2);
        painter.drawImage(name_rect,name12);
    }
    if(IntroduceP>=80&&IntroduceP<100){
        school2=Image_Transparent(school,255);
        name22=Image_Transparent(name2,(IntroduceP-80)*12);
        painter.drawImage(school_rect,school2);
        painter.drawImage(name_rect,name22);
    }
    if(IntroduceP>=100&&IntroduceP<120){
        school2=Image_Transparent(school,255-13*(IntroduceP-100));
        name22=Image_Transparent(name2,255-13*(IntroduceP-100));
        painter.drawImage(school_rect,school2);
        painter.drawImage(name_rect,name22);
    }
    if(IntroduceP>=120&&IntroduceP<400){
        title.setRect(title.x()+50,title.y(),title.width(),title.height());
        painter.drawImage(tital,fill);
        painter.drawImage(title,title_image);
    }

}
