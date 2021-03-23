#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include"mainwindow.h"

void BattleWindow::Introduce_Flash(){
    Total_Time++;
    if(Total_Time==1){
        QMediaPlayer *player1 = new QMediaPlayer;
            player1->setVolume(50);
        player1->setMedia(QUrl("qrc:/sounds/sounds/Introduce_1.mp3"));
        player1->play();
        P1[0].Strengthen(9999,9999,4,0);
    }
    if(Total_Time==80){
        ParticalTick.start(50);
        EnemyMove.start(50);
        EnemyAll.start(100);
        move.start(10);
    }

    if(Total_Time==120){
        QMediaPlayer *player2 = new QMediaPlayer;
        player2->setMedia(QUrl("qrc:/sounds/sounds/Introduce_2.mp3"));
        player2->setVolume(50);
        player2->play();
    }
    if(Total_Time==200){
        QMediaPlayer *player3 = new QMediaPlayer;
        player3->setMedia(QUrl("qrc:/sounds/sounds/Introduce_3.mp3"));
        player3->setVolume(100);
        player3->play();
    }
    /*        if(Total_Time>=120&&Total_Time<250){
                P1[0].Player_ChangeHead(3);
                move.start(10);
                P1[0].Player_B1Fire();
            }*/
            if(Total_Time>=250&&Total_Time<280){
               // P1[0].Player_ChangeHead(1);
               // move.start(10);
               // P1[0].Player_B1Fire();
                RainFire();
            }
            /*if(Total_Time>=300&&Total_Time<400){

                P1[0].Player_ChangeHead(3);
                move.start(10);
                P1[0].Player_B1Fire();
            }*/
            if(Total_Time==400){
                backto=new MainWindow();
                backto->show();
                this->~BattleWindow();
                return;
            }
}
void BattleWindow::Load_Introduce(){

    Load_Map(":/maps/maps/Introduce.txt");

    Introduce_Flash();
    QTimer *in=new QTimer(this);
        connect(in, SIGNAL(timeout()), this, SLOT(Introduce_Flash()));
        in->start(50);
}


void BattleWindow::drawIntroduce(QPainter &painter){
    QImage school(":/Images/Images/school.png");
    QImage school2;
    QImage name1(":/Images/Images/name1.png");
    QImage name12;
    QImage name2(":/Images/Images/name2.png");
    QImage name22;
    QImage fill(":/Images/Images/fill.jpg");
    QImage title_image(":/Images/Images/title.png");

    QRect school_rect(700,200,550,113);
    QRect name_rect(700,500,583,332);
    QRect tital(0,400,2000,200);
    QRect title(0,400,1800,200);
    if(Total_Time>0&&Total_Time<120)
    painter.fillRect(0,0,2000,1080,QColor(Qt::black));
    if(Total_Time>20&&Total_Time<40){
        school2=Image_Transparent(school,(Total_Time-20)*12);
        name12=Image_Transparent(name1,(Total_Time-20)*12);
        painter.drawImage(school_rect,school2);
        painter.drawImage(name_rect,name12);
    }
    if(Total_Time>=40&&Total_Time<60){
        school2=Image_Transparent(school,255);
        name12=Image_Transparent(name1,255);
        painter.drawImage(school_rect,school2);
        painter.drawImage(name_rect,name12);
    }
    if(Total_Time>=60&&Total_Time<80){
        school2=Image_Transparent(school,255);
        name12=Image_Transparent(name1,255-13*(Total_Time-60));
        painter.drawImage(school_rect,school2);
        painter.drawImage(name_rect,name12);
    }
    if(Total_Time>=80&&Total_Time<100){
        school2=Image_Transparent(school,255);
        name22=Image_Transparent(name2,(Total_Time-80)*12);
        painter.drawImage(school_rect,school2);
        painter.drawImage(name_rect,name22);
    }
    if(Total_Time>=100&&Total_Time<120){
        school2=Image_Transparent(school,255-13*(Total_Time-100));
        name22=Image_Transparent(name2,255-13*(Total_Time-100));
        painter.drawImage(school_rect,school2);
        painter.drawImage(name_rect,name22);
    }
    if(Total_Time>=120&&Total_Time<400){
        title.setRect(title.x(),title.y(),title.width(),title.height());
        painter.drawImage(tital,fill);
        painter.drawImage(title,title_image);
    }

}
