#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include"mainwindow.h"

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
void BattleWindow::Mission2(){
   Load_Map(":/maps/maps/1_2.txt");
}
void BattleWindow::MissionRougueLike(){
Load_Map(":/RougeLike/RougeLike/1_1_0.txt");
LevelB++;
}
void BattleWindow::MissionRougueLike_Win(){
    if (Win==false)return;
    switch (LevelA) {
    case 1: Map=LevelB;
            switch (LevelB) {
            case 2:{XY t={0,600};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_2_0.txt");LevelB++;break;}
            case 3:{XY t={300,950};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_3_0.txt");LevelB++;break;}
            case 4:{XY t={1450,500};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_4_0.txt");LevelB++;break;}
            case 5:{XY t={200,950};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_5_0.txt");LevelB++;break;}
            case 6:{XY t={0,800};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_6_0.txt");LevelB++;break;}
            case 7:{XY t={200,950};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_7_0.txt");LevelB++;break;}
            case 8:{XY t={750,950};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_8_0.txt");LevelB++;break;}
            case 9:QMessageBox::information(nullptr,tr("恭喜"),tr("您通关了"), tr("好"));
                this->~BattleWindow();backto=new MainWindow;
                backto->setMouseTracking(true);backto->show();break;
            }

    case 2:break;
    }
}
void BattleWindow::MissionRougueLike_Continue(){
    switch (LevelA) {
    case 1:
        switch (Map) {
        case 3:Map++;Load_Map(":/RougeLike/RougeLike/1_3_1.txt");break;
        case 8:Map++;Load_Map(":/RougeLike/RougeLike/1_8_1.txt");break;
        case 9:Map++;Load_Map(":/RougeLike/RougeLike/1_8_2.txt");break;
        }

    }
}
void BattleWindow::Mission1(){
    int i;
   Dialog[0].load(":/Mission1/images/Dialog1_0.jpg");
   Dialog[1].load(":/Mission1/images/Dialog1_1.jpg");
   Dialog[2].load(":/Mission1/images/Dialog1_2.jpg");
   Dialog[3].load(":/Mission1/images/Dialog1_3.jpg");
   Dialog[4].load(":/Mission1/images/Dialog1_4.jpg");
   Load_Map(":/maps/maps/1_1.txt");

   XY dialog{0,0};
       XY dialog_Rect{2000,1000};
   for(i=0;i<Edit_Max;i++){
       if(partical[i].GetAlive()==true)continue;
       new(&partical[i])Partical(dialog,dialog_Rect,Type::Mist);
       break;
   }
}
void BattleWindow::Mission1_J(){
    int i;XY dialog{0,500};
    XY dialog_Rect{1500,500};
    if(Total_Time==7){
        Process++;
        for(i=0;i<Edit_Max;i++){
            if(partical[i].GetAlive()==true)continue;
            new(&partical[i])Partical(dialog,dialog_Rect,Type::Mist);
            break;
        }
    }
    if(P1.GetPos().x<350&&P1.GetPos().y<400&&Process==1){
        Process++;
        for(i=0;i<Edit_Max;i++){
            if(partical[i].GetAlive()==true)continue;
            new(&partical[i])Partical(dialog,dialog_Rect,Type::Mist);
            break;
        }
    }
    if(P1.GetPos().x<350&&P1.GetPos().y>550&&Process==2){
        Process++;
        for(i=0;i<Edit_Max;i++){
            if(partical[i].GetAlive()==true)continue;
            new(&partical[i])Partical(dialog,dialog_Rect,Type::Mist);
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
            new(&partical[i])Partical(dialog,dialog_Rect,Type::Mist);
            break;
        }

    }
}
