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
#include"Partical.h"
#include"RedZone.h"

void BattleWindow::drawMission1(QPainter &painter){
    int i;
        for(i=0;i<Edit_Max;i++){
            if(partical[i].GetAlive()==false)continue;
            QRect Partical_Rect(partical[i].GetPos().x,partical[i].GetPos().y,partical[i].GetArea().x,partical[i].GetArea().y);
            switch (partical[i].GetType()) {
            case 100:painter.drawImage(Partical_Rect,Image_Transparent(Dialog[0],partical[i].GetFlash()>50?(255-(partical[i].GetFlash()-50)*5):255));break;
            case 101:painter.drawImage(Partical_Rect,Image_Transparent(Dialog[1],partical[i].GetFlash()*5));break;
            case 102:painter.drawImage(Partical_Rect,Image_Transparent(Dialog[2],partical[i].GetFlash()*5));break;
            case 103:painter.drawImage(Partical_Rect,Image_Transparent(Dialog[3],partical[i].GetFlash()*5));break;
            case 104:painter.drawImage(Partical_Rect,Image_Transparent(Dialog[4],partical[i].GetFlash()*5));break;
            }
        }
}
void BattleWindow::Mission1(){
    Red_Zone_Fre=0;
   Red_Zone=0;int i;
   Dialog[0].load(":/Mission1/images/Dialog1_0.jpg");
   Dialog[1].load(":/Mission1/images/Dialog1_1.jpg");
   Dialog[2].load(":/Mission1/images/Dialog1_2.jpg");
   Dialog[3].load(":/Mission1/images/Dialog1_3.jpg");
   Dialog[4].load(":/Mission1/images/Dialog1_4.jpg");
   Load_Map(":/maps/maps/1_1.txt");
   QTimer *timer = new QTimer(this);
   QTimer *flash = new QTimer(this);
   QTimer *enemymove = new QTimer(this);
   QTimer *enemyall = new QTimer(this);
   QTimer *generate = new QTimer(this);
   QTimer *boom = new QTimer(this);
   XY dialog{0,0};
       XY dialog_Rect{2000,1000};
   for(i=0;i<Edit_Max;i++){
       if(partical[i].GetAlive()==true)continue;
       new(&partical[i])Partical(dialog,dialog_Rect,100,100);
       break;
   }
   connect(timer, SIGNAL(timeout()), this, SLOT(update()));
   connect(timer, SIGNAL(timeout()), this, SLOT(bulletfly()));
   connect(flash, SIGNAL(timeout()), this, SLOT(Flash()));
   connect(&move, SIGNAL(timeout()), this, SLOT(Move()));
   connect(&fix,  SIGNAL(timeout()), this, SLOT(P1_Fix()));
   connect(enemymove, SIGNAL(timeout()), this, SLOT(Enemy_Move()));
   connect(enemyall, SIGNAL(timeout()), this, SLOT(Enemy_All()));
   connect(generate, SIGNAL(timeout()), this, SLOT(Enemy_Generate()));
   connect(boom, SIGNAL(timeout()), this, SLOT(Flash2()));

     timer->start(10);
     flash->start(1000);
     enemymove->start(50);
     enemyall->start(100);
     generate->start(5000);
     boom->start(50);
}
void BattleWindow::Mission1_J(){
    int i;XY dialog{0,500};
    XY dialog_Rect{1500,500};
    if(Total_Time==7){
        Process++;
        for(i=0;i<Edit_Max;i++){
            if(partical[i].GetAlive()==true)continue;
            new(&partical[i])Partical(dialog,dialog_Rect,100,101);
            break;
        }
    }
    if(P1.GetPos().x<350&&P1.GetPos().y<400&&Process==1){
        Process++;
        for(i=0;i<Edit_Max;i++){
            if(partical[i].GetAlive()==true)continue;
            new(&partical[i])Partical(dialog,dialog_Rect,100,102);
            break;
        }
    }
    if(P1.GetPos().x<350&&P1.GetPos().y>550&&Process==2){
        Process++;
        for(i=0;i<Edit_Max;i++){
            if(partical[i].GetAlive()==true)continue;
            new(&partical[i])Partical(dialog,dialog_Rect,100,103);
            break;
        }
    }
    if(P1.GetPos().x>950&&Process==3){
        Process++;
        XY t={1300,500};
        new(&redzone[0])RedZone(t,100,1);
        redzone[0].Flash_Begin();
        for(i=0;i<Edit_Max;i++){
            if(partical[i].GetAlive()==true)continue;
            new(&partical[i])Partical(dialog,dialog_Rect,100,104);
            break;
        }

    }
}
