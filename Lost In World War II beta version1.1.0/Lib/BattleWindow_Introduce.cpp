#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include"mainwindow.h"

void BattleWindow::Introduce_Flash(){
    IntroduceP++;
    if(IntroduceP==1){
        QMediaPlayer *player1 = new QMediaPlayer;
            player1->setVolume(50);
        player1->setMedia(QUrl("qrc:/sounds/sounds/Introduce_1.mp3"));
        player1->play();
        P1.Strengthen(9999,0,0,0,0,5);
    }
    if(IntroduceP==80){
        boom.start(50);
        timer.start(10);
        flash.start(1000);
        enemymove.start(50);
        enemyall.start(100);
        generate.start(5000);//QTimer
    }

    if(IntroduceP==120){
        QMediaPlayer *player2 = new QMediaPlayer;
        player2->setMedia(QUrl("qrc:/sounds/sounds/Introduce_2.mp3"));
        player2->setVolume(50);
        player2->play();
    }
    if(IntroduceP==200){
        QMediaPlayer *player3 = new QMediaPlayer;
        player3->setMedia(QUrl("qrc:/sounds/sounds/Introduce_3.mp3"));
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
                RainFire();
            }
            if(IntroduceP>=300&&IntroduceP<400){

                P1.Player_ChangeHead(3);
                move.start(10);
                P1.Player_B1Fire();
            }
            if(IntroduceP>=400){
                backto=new MainWindow;
                backto->setMouseTracking(true);
                backto->show();
                this->~BattleWindow();
            }
}
void BattleWindow::Load_Introduce(){
    ui->label->setGeometry(-100,-100,10,10);
    ui->label_2->setGeometry(-100,-100,10,10);
    ui->label_3->setGeometry(-100,-100,10,10);
    ui->label_4->setGeometry(-100,-100,10,10);
    ui->label_5->setGeometry(-100,-100,10,10);

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
    fill=Image_Transparent(fill,200);
    QRect school_rect(700,200,550,113);
    QRect name_rect(700,500,583,332);
    QRect tital(0,400,2000,200);
    QRect title(0,400,1800,200);
    if(IntroduceP>0&&IntroduceP<120)
    painter.fillRect(0,0,2000,1000,QColor(Qt::black));
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
        title.setRect(title.x(),title.y(),title.width(),title.height());
        painter.drawImage(tital,fill);
        painter.drawImage(title,title_image);
    }

}
