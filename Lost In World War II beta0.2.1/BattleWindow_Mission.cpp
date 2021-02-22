#include "BattleWindow.h"
#include "ui_BattleWindow.h"
#include"mainwindow.h"



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
        case 9:{Map++;Load_Map(":/RougeLike/RougeLike/1_8_2.txt");XY temp={100,300};
            new(boss1)Boss1(temp,100,1);
            break;}
        }

    }
}
void BattleWindow::MissionTeach(){
    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
   Load_Map(":/maps/maps/1_1.txt");
   XY dialog{0,0};
   XY dialog_Rect{2000,1000};
   CreatePartical(dialog,dialog_Rect,Type::Dialog1);
}
void BattleWindow::MissionTeach_Win(){
    if(LevelB==3||LevelB==4)return;
        LevelB++;
    switch (LevelB) {
    case 2:{XY temp={100,950};ClearMap(temp);Load_Map(":/maps/maps/1_2.txt");
        Total_Time=0;Process=0; break;}
    case 3:{XY temp={300,450};ClearMap(temp);Load_Map(":/maps/maps/1_3.txt");
      Total_Time=0;Process=0;break;}
    }
}
void BattleWindow::MissionTick(int Mission){
    if(Mission!=1)return;
    XY t1={0,500},t2={1500,500};
    switch (LevelB) {
    case 1:
    {
        if(Total_Time==5){
            Process++;
            CreatePartical(t1,t2,Type::Dialog2);
        }
        if(P1.GetPos().x<350&&P1.GetPos().y<400&&Process==1){
            Process++;
            CreatePartical(t1,t2,Type::Dialog3);
        }
        if(P1.GetPos().x<350&&P1.GetPos().y>550&&Process==2){
            Process++;
            CreatePartical(t1,t2,Type::Dialog4);
        }
        if(P1.GetPos().x>950&&Process==3){
            Process++;
            XY t={1300,500};
            CreateRedZone(t,100,1);
            CreatePartical(t1,t2,Type::Dialog5);
        }break;}
        break;
    case 2:
        if(Process==0){
            Process++;
            CreatePartical(t1,t2,Type::Dialog6);
        }
        if(P1.GetPos().x>550&&Process==1){
            Process++;
            CreatePartical(t1,t2,Type::Dialog7);
        }
        break;
    case 3:
        if(Process==0){
            Process++;
            CreatePartical(t1,t2,Type::Dialog8);
        }
        if(Total_Time==5){
            Rain.start(100);
        }
        if(Total_Time==22){
            LevelB++;
            XY temp={0,450};
            ClearMap(temp);
            Load_Map(":/maps/maps/1_4.txt");
            Total_Time=0;
            Process=0;
        }
        break;
    case 4:
        if(Process==0&&Total_Time==5){
            Load_Map(":/maps/maps/1_5.txt");
            Load_Map(":/maps/maps/1_5.txt");
        }
        if(Process==0&&Total_Time==10){
            Load_Map(":/maps/maps/1_6.txt");
        }
        if(Process==0&&Total_Time==15){
            P1.Strengthen(-P1.GetHP()+100,0,0,0,0,0);
        }
        if(Process==0&&Total_Time==20){
            P1.Strengthen(-P1.GetHP()-100,0,0,0,0,0);
        }
        if(Process==1&&Total_Time>=10){
            QMessageBox::information(nullptr,tr("提示"),tr("新手任务结束"), tr("好"));
            this->~BattleWindow();backto=new MainWindow;
            backto->setMouseTracking(true);backto->show();
        }
        break;
    }


}
void BattleWindow::MissionTechEnd(){
    LevelB=4;
    Total_Time=0;
    Process=1;
    XY t={0,0},t2={2000,1000};
    P1.Strengthen(100000,0,0,0,0,0);
    ClearMap(t);
    CreatePartical(t,t2,Type::DialogEnd);
}
