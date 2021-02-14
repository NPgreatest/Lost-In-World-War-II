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
   Red_Zone_Fre=0;
   Red_Zone=0;
   Load_Map(":/maps/maps/1_2.txt");
}
void BattleWindow::MissionRougueLike(){
Red_Zone_Fre=0;
Red_Zone=0;
Load_Map(":/RougeLike/RougeLike/1_0.txt");

}
void BattleWindow::MissionRougueLike_Win(){
    if (Win==false)return;
    switch (LevelA) {
    case 1:
            switch (LevelB) {
            case 1:{XY t={0,500};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_1.txt");LevelB++;break;}
            case 2:{XY t={0,600};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_2.txt");LevelB++;break;}
            case 3:{XY t={300,950};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_3.txt");LevelB++;break;}
            case 4:{XY t={0,100};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_4.txt");LevelB++;break;}
            case 5:{XY t={0,850};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_5.txt");LevelB++;break;}
            case 6:{XY t={50,500};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_100.txt");LevelB++;Map=100;break;}
            case 7:{XY t={600,0};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_6.txt");LevelB++;break;}
            case 8:{XY t={0,50};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_7.txt");LevelB++;break;}
            case 9:{XY t={800,50};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_8.txt");LevelB++;break;}
            case 10:{XY t={50,50};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_9.txt");LevelB++;break;}
            case 11:{XY t={1400,950};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_10.txt");LevelB++;break;}
            case 12:{XY t={0,350};ClearMap(t);Load_Map(":/RougeLike/RougeLike/1_200.txt");Map=200;LevelB++;break;}
            case 13:QMessageBox::information(nullptr,tr("恭喜"),tr("您通关了"), tr("好"));
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
        case 100:Map++;Load_Map(":/RougeLike/RougeLike/1_101.txt");break;
        case 101:Map++;Load_Map(":/RougeLike/RougeLike/1_102.txt");break;
        case 200:Map++;Load_Map(":/RougeLike/RougeLike/1_201.txt");break;
        case 201:Map++;Load_Map(":/RougeLike/RougeLike/1_202.txt");break;
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

   XY dialog{0,0};
       XY dialog_Rect{2000,1000};
   for(i=0;i<Edit_Max;i++){
       if(partical[i].GetAlive()==true)continue;
       new(&partical[i])Partical(dialog,dialog_Rect,100,100);
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
